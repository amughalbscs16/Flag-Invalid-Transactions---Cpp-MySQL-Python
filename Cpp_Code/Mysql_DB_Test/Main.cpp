// Main.cpp
//
#include "Generate_Output.hpp"

int main()
{
	MYSQL* conn = Database_Access::make_mysql_conn();
	if (conn) {
		map<int, Account> accounts;
		map<int, Transaction> transactions;
		vector<Transaction_Account> flagged_transactions_rule_1;
		vector<Transaction_Account> flagged_transactions_rule_2;

		Database_Access::read_accounts(conn, accounts);
		Database_Access::read_transactions(conn, transactions, accounts);


		//Apply flag rules
		Apply_Rules::apply_flag_rules(accounts, flagged_transactions_rule_1, flagged_transactions_rule_2);

		Generate_Output::print_flagged_transactions(accounts, flagged_transactions_rule_1, flagged_transactions_rule_2);
		Generate_Output::write_flagged_transactions(accounts, flagged_transactions_rule_1, flagged_transactions_rule_2);
	}
	else{
		cout << "Program ended without working. Database connection was not established." << endl;
	}
	return 0;
}
