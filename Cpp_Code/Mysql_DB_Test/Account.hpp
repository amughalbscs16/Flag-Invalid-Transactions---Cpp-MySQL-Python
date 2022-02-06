#include "Transaction.hpp"
#include "Transaction_Account.hpp"

class Account {
private:
	string first_name;
	string last_name;
	string street_address;
	int unit;
	string city;
	string state;
	string zip;
	string dob;
	string ssn;
	string email_address;
	long long mobile_number;
	int account_number;
	// string string: 
	// merchant_num -> count_transactions
	map <string, int> negative_count_merchant;
	// merchant_num -> sum_transactions;
	map <string, double> negative_sum_transaction;
	// merchant_num -> count_transactions
	map <string, int> positive_count_merchant;
	// merchant_num -> sum_transactions;
	map <string, double> positive_sum_transaction;
	//merchant_num -> transaction_id -> Transaction 
	map < string, map<int, Transaction> > merchant_transactions;
	

public:
	Account()
	{

	}

	Account(string fname, string lname, string st_ad, int unit, string city, string state, string zip, string dob, string ssn, string email, long long mob_num, int acc_num)
	{
		this->set_first_name(fname);
		this->set_last_name(lname);
		this->set_street_address(st_ad);
		this->set_unit(unit);
		this->set_city(city);
		this->set_state(state);
		this->set_zip(zip);
		this->set_dob(dob);
		this->set_ssn(ssn);
		this->set_email_address(email);
		this->set_mobile_number(mob_num);
		this->set_account_number(acc_num);
	}

	//If transaction happened in another state
	void make_transaction_account(Transaction_Account& trans_account, Transaction trans)
	{
		string actual_state = this->get_state();
		string shopped_state = trans.get_merchant_state();
		string fname = this->get_first_name();
		string lname = this->get_last_name();
		string merchant_description = trans.get_merchant_description();
		double transaction_amount = trans.get_transaction_amount();
		int transaction_number = trans.get_transaction_number();
		int account_number = this->get_account_number();
		trans_account = Transaction_Account(actual_state, shopped_state, fname, lname, merchant_description, transaction_amount, transaction_number, account_number);

	}

	//Apply transaction filter rule 1 (high value anamoly) 
	void filter_transactions_rule_1(vector<Transaction_Account>& flagged_transactions)
	{
		int count = 0;
		int positive_rule_times = 3;
		int negative_rule_times = 5;
		//Iterate over all merchants with transactions
		auto merchant_iter = this->merchant_transactions.begin();
		while (merchant_iter != merchant_transactions.end()) {
			//Iterate over all transactions with a merchant
			string merchant_number = merchant_iter->first;
			auto transaction_iter = merchant_iter->second.begin();
			while (transaction_iter != merchant_iter->second.end())
			{
				if (this->negative_count_merchant[merchant_number] >= 2)
				{
					Transaction trans = transaction_iter->second;
					if (trans.get_transaction_amount() < 0)
					{
						double other_average = (this->negative_sum_transaction[merchant_number] + abs(trans.get_transaction_amount())) / (this->negative_count_merchant[merchant_number] - 1);
						if (trans.get_transaction_amount() < negative_rule_times* other_average)
						{
							Transaction_Account trans_account;
							this->make_transaction_account(trans_account, trans);
							flagged_transactions.push_back(trans_account);
						}
					}
					else if (trans.get_transaction_amount() > 0)
					{
						
						double other_average = (this->positive_sum_transaction[merchant_number] - trans.get_transaction_amount()) / (this->negative_count_merchant[merchant_number] - 1);
						if (trans.get_transaction_amount() > positive_rule_times * other_average)
						{
							Transaction_Account trans_account;
							this->make_transaction_account(trans_account, trans);
							flagged_transactions.push_back(trans_account);
						}
					}
				}

				++transaction_iter;
			}
			++merchant_iter;
		}

	}

	//Apply transaction filter rule 2 (Transaction happened in another state)
	void filter_transactions_rule_2(vector<Transaction_Account>& flagged_transactions) {
		//Iterate over all merchant_transactions
		auto merchant_iter = this->merchant_transactions.begin();
		while (merchant_iter != merchant_transactions.end()) {
			//Iterate over all the transactions in a merchant
			auto transaction_iter = merchant_iter->second.begin();
			while (transaction_iter != merchant_iter->second.end())
			{
				// If this state != trans insert (info to the flagged transactions)
				if (this->get_state().compare(transaction_iter->second.get_merchant_state()) != 0)
				{
					Transaction trans = transaction_iter->second;
					Transaction_Account trans_account;
					this->make_transaction_account(trans_account, trans);
					flagged_transactions.push_back(trans_account);
				}
				++transaction_iter;
			}
			++merchant_iter;
		}

		
		//cout << "Filter transaction rule 2 for " << this->get_account_number() << endl;

	}

	void add_transaction_merchant(Transaction& trans)
	{
		
		
		// Taking positives into account just in case (+ives are very low in number, and I was not sure if it is credit or debit) 
		if (trans.get_transaction_amount() > 0)
		{
			//cout << "positive: " << trans.get_transaction_amount() << endl;
			//If merchant in positive_count_merchant
			if (this->positive_count_merchant.find(trans.get_merchant_number()) != this->positive_count_merchant.end() && this->positive_sum_transaction.find(trans.get_merchant_number()) != this->positive_sum_transaction.end())
			{
				this->positive_count_merchant[trans.get_merchant_number()] += 1;
				this->positive_sum_transaction[trans.get_merchant_number()] += trans.get_transaction_amount();
			}
			else
			{
				this->positive_count_merchant.insert(pair<string, int>(trans.get_merchant_number(), 1));
				this->positive_sum_transaction.insert(pair<string, double>(trans.get_merchant_number(), trans.get_transaction_amount()));
			}
			//cout << "positive value" << this->positive_count_merchant[trans.get_merchant_number()] << " " << this->positive_sum_transaction[trans.get_merchant_number()] << endl;

		}
		// If Negatives (Majority of the given cases)
		
		else if (trans.get_transaction_amount() < 0)
		{


			//cout << "negative: " << trans.get_transaction_amount() << endl;
			// If merchant in negative_count_merchant
			if (this->negative_count_merchant.find(trans.get_merchant_number()) != this->negative_count_merchant.end())
			{
				this->negative_count_merchant[trans.get_merchant_number()] += 1;
				this->negative_sum_transaction[trans.get_merchant_number()] += trans.get_transaction_amount();
			}
			else
			{
				this->negative_count_merchant.insert(pair<string, int>(trans.get_merchant_number(), 1));
				this->negative_sum_transaction.insert(pair<string, double>(trans.get_merchant_number(), trans.get_transaction_amount()));
			}
			//cout << "negative value" << this->negative_count_merchant[trans.get_merchant_number()] << " " << this->negative_sum_transaction[trans.get_merchant_number()] << endl;

		}
		/* Make a map of merchant->transaction_number->Transaction for an account holder */
		
		//If merchant already added to the account
		


		/*This part has an error */
		if (this->merchant_transactions.find(trans.get_merchant_number()) != this->merchant_transactions.end())
		{
			string merchant_number = trans.get_merchant_number();
			if (trans.get_transaction_amount() == -10000)
			{
				this->merchant_transactions[merchant_number].insert(pair<int, Transaction>(trans.get_transaction_id(), trans));
			}	
		}
		else
		{
			//Make a map with first transaction with this merchant 
			string merchant_number = trans.get_merchant_number();
			map <int, Transaction> new_merchant;
			new_merchant.insert(pair<int, Transaction>(trans.get_transaction_id(), trans));
			this->merchant_transactions.insert(pair <string, map<int, Transaction>> (merchant_number, new_merchant));
		}
			



		return;
	}
	double get_average_transaction(string merchant)
	{
		//return average transaction of a merchant.
		return 0.0;
	}
	void set_first_name(string first_name)
	{
		this->first_name = first_name;
	}
	void set_last_name(string last_name)
	{
		this->last_name = last_name;
	}
	void set_street_address(string address)
	{
		this->street_address = address;
	}
	void set_unit(int unit)
	{
		this->unit = unit;
	}
	void set_city(string city)
	{
		this->city = city;
	}
	void set_state(string state)
	{
		this->state = state;
	}
	void set_zip(string zip)
	{
		this->zip = zip;
	}
	void set_dob(string dob) {
		this->dob = dob;
	}
	void set_ssn(string ssn) {
		this->ssn = ssn;
	}
	void set_email_address(string email)
	{
		this->email_address = email;
	}
	void set_mobile_number(long long mobile_number) {
		this->mobile_number = mobile_number;
	}
	void set_account_number(int account_number)
	{
		this->account_number = account_number;
	}

	string get_first_name()
	{
		return this->first_name;
	}
	string get_last_name()
	{
		return this->last_name;
	}
	string get_street_address()
	{
		return this->street_address;
	}
	int get_unit()
	{
		return this->unit;
	}
	string get_city()
	{
		return this->city;
	}
	string get_state()
	{
		return this->state;
	}
	string get_zip()
	{
		return this->zip;
	}
	string get_dob() {
		return this->dob;
	}
	string get_ssn() {
		return this->ssn;
	}
	string get_email_address()
	{
		return this->email_address;
	}
	long long get_mobile_number() {
		return this->mobile_number;
	}
	int get_account_number()
	{
		return this->account_number;
	}

};