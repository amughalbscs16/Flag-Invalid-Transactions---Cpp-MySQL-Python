#include "imports.hpp"

class Transaction {
private:
	int transaction_id;
	int account_number;
	string transaction_datetime;
	double transaction_amount;
	string post_date;
	string merchant_number;
	string merchant_description;
	string merchant_state;
	int merchant_category_code;
	int transaction_number;
public:
	Transaction() {
		
	}
	Transaction(int trans_id, int acc_num, string trans_datetime, double trans_amount, string post_date, string merc_num, string merc_desc, string merc_state, int merc_cate_code, int trans_num)
	{
		this->set_transaction_id(trans_id);
		this->set_account_number(acc_num);
		this->set_transaction_datetime(trans_datetime);
		this->set_transaction_amount(trans_amount);
		this->set_post_date(post_date);
		this->set_merchant_number(merc_num);
		this->set_merchant_description(merc_desc);
		this->set_merchant_state(merc_state);
		this->set_merchant_category_code(merc_cate_code);
		this->set_transaction_number(trans_num);
	}

	void set_transaction_id(int trans_id) {
		this->transaction_id = trans_id;
	}

	void set_account_number(int acc_num) {
		this->account_number = acc_num;
	}

	void set_transaction_datetime(string trans_dt) {
		this->transaction_datetime = trans_dt;
	}

	void set_transaction_amount(double amount) {
		this->transaction_amount = amount;
	}

	void set_post_date(string post_date) {
		this->post_date = post_date;
	}

	void set_merchant_number(string merc_num) {
		this->merchant_number = merc_num;
	}

	void set_merchant_description(string merc_desc) {
		this->merchant_description = merc_desc;
	}
	void set_merchant_state(string merc_state)
	{
		this->merchant_state = merc_state;
	}

	void set_merchant_category_code(int merc_cat_code) {
		this->merchant_category_code = merc_cat_code;
	}

	void set_transaction_number(int trans_num) {
		this->transaction_number = trans_num;
	}

	int get_transaction_id() {
		return this->transaction_id;
	}

	int get_account_number() {
		return this->account_number;
	}

	string get_transaction_datetime() {
		return this->transaction_datetime;
	}

	double get_transaction_amount() {
		return this->transaction_amount;
	}

	string get_post_date() {
		return this->post_date;
	}

	string get_merchant_number() {
		return this->merchant_number;
	}

	string get_merchant_description() {
		return this->merchant_description;
	}

	string get_merchant_state()
	{
		return this->merchant_state;
	}

	int get_merchant_category_code() {
		return this->merchant_category_code;
	}

	int get_transaction_number() {
		return this->transaction_number;
	}


};
