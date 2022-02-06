class Transaction_Account {
private:
	string actual_state;
	string shopped_state;
	string first_name;
	string last_name;
	string merchant_description;
	double transaction_amount;
	int transaction_number;
	int account_number;
	public:
	Transaction_Account() {

	}
	Transaction_Account(string act_state, string shop_state,
		string fname, string lname, string merc_desc,
		double trans_amo, int trans_num, int acc_num)
	{
		this->set_actual_state(act_state);
		this->set_shopped_state(shop_state);
		this->set_first_name(fname);
		this->set_last_name(lname);
		this->set_merchant_description(merc_desc);
		this->set_transaction_amount(trans_amo);
		this->set_transaction_number(trans_num);
		this->set_account_number(acc_num);
	}
	void set_actual_state(string actual_state) {
		this->actual_state = actual_state;
	}
	void set_shopped_state(string shopped_state) {
		this->shopped_state = shopped_state;
	}
	void set_first_name(string fname) {
		this->first_name = fname;
	}
	void set_last_name(string lname) {
		this->last_name = lname;
	}
	void set_merchant_description(string merc_desc) {
		this->merchant_description = merc_desc;
	}
	void set_transaction_amount(double trans_amo) {
		this->transaction_amount = trans_amo;
	}
	void set_transaction_number(int trans_num) {
		this->transaction_number = trans_num;
	}
	void set_account_number(int acc_num) {
		this->account_number = acc_num;
	}

	string get_actual_state() {
		return this->actual_state;
	}
	string get_shopped_state() {
		return this->shopped_state = shopped_state;
	}
	string get_first_name() {
		return this->first_name;
	}
	string get_last_name() {
		return this->last_name;
	}
	string get_merchant_description() {
		return this->merchant_description;
	}
	double get_transaction_amount() {
		return this->transaction_amount;
	}
	int get_transaction_number() {
		return this->transaction_number;
	}
	int get_account_number() {
		return this->account_number;
	}

};
