#include "Database_Access.hpp"

class Apply_Rules {
public:
	static void apply_flag_rules(map<int, Account>& accounts, vector<Transaction_Account>& flagged_transactions_rule_1, vector<Transaction_Account>& flagged_transactions_rule_2)
	{
		//Iterate over each of the accounts
		auto iter = accounts.begin();
		while (iter != accounts.end()) {
			//Call rule 1
			iter->second.filter_transactions_rule_1(flagged_transactions_rule_1);

			//Call rule 2
			iter->second.filter_transactions_rule_2(flagged_transactions_rule_2);

			++iter;
		}


	}
};
