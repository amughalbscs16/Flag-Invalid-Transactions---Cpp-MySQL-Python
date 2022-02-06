#include "Apply_Rules.hpp"
#include <cstdio>
#include <fstream>
#define _CRT_SECURE_NO_DEPRECATE
class Generate_Output {
public:
	static void print_flagged_transactions(map<int, Account> accounts, vector<Transaction_Account>& flagged_transactions_rule_1, vector<Transaction_Account>& transactions_rule_2)
	{
		cout << "Fraud Rule 1: (Transactions > 5 times the average of other transactions with same merchant)" << endl;
		cout << fixed;
		cout << setw(25) << left << "Name" << setw(25) << left << "Account Number" << setw(25) << left << "Transaction Number" << setw(35) << left << "Merchant" << setw(25) << left << "Transaction Amount" << endl;
		for (int i = 0; i < flagged_transactions_rule_1.size(); i++)
		{
			Transaction_Account trans_acc = flagged_transactions_rule_1[i];
			cout << setw(25) << left << trans_acc.get_first_name() + " " + trans_acc.get_last_name() << setw(25) << left << trans_acc.get_account_number() << setw(25) << left << trans_acc.get_transaction_number() << setw(35) << left << trans_acc.get_merchant_description() << "$" << setw(25) << left << setprecision(2) << abs(trans_acc.get_transaction_amount()) << endl;
		}

		cout << endl << "Fraud Rule 2:" << endl;
		cout << fixed;
		cout << setw(25) << left << "Name" << setw(25) << left << "Account Number" << setw(25) << left << "Transaction Number" << setw(35) << left << "Expected Transaction Location" << setw(35) << left << "Actual Transaction Location" << endl;
		for (int i = 0; i < flagged_transactions_rule_1.size(); i++)
		{
			Transaction_Account trans_acc = flagged_transactions_rule_1[i];
			cout << setw(25) << left << trans_acc.get_first_name() + " " + trans_acc.get_last_name() << setw(25) << left << trans_acc.get_account_number() << setw(25) << left << trans_acc.get_transaction_number() << setw(35) << left << trans_acc.get_actual_state() << setw(25) << left << trans_acc.get_shopped_state() << endl;
		}

	}

	static void write_flagged_transactions(map<int, Account> accounts, vector<Transaction_Account>& flagged_transactions_rule_1, vector<Transaction_Account>& transactions_rule_2)
	{
		ofstream File_1("fraud rule 1.txt");
		File_1 << "Fraud Rule 1: (Transactions > 5 times the average of other transactions with same merchant)" << endl;
		File_1 << fixed;
		File_1 << setw(25) << left << "Name" << setw(25) << left << "Account Number" << setw(25) << left << "Transaction Number" << setw(35) << left << "Merchant" << setw(25) << left << "Transaction Amount" << endl;
		for (int i = 0; i < flagged_transactions_rule_1.size(); i++)
		{
			Transaction_Account trans_acc = flagged_transactions_rule_1[i];
			File_1 << setw(25) << left << trans_acc.get_first_name() + " " + trans_acc.get_last_name() << setw(25) << left << trans_acc.get_account_number() << setw(25) << left << trans_acc.get_transaction_number() << setw(35) << left << trans_acc.get_merchant_description() << "$" << setw(25) << left << setprecision(2) << abs(trans_acc.get_transaction_amount()) << endl;
		}
		File_1.close();

		ofstream File_2("fraud rule 2.txt");
		File_2 << endl << "Fraud Rule 2:" << endl;
		File_2 << fixed;
		File_2 << setw(25) << left << "Name" << setw(25) << left << "Account Number" << setw(25) << left << "Transaction Number" << setw(35) << left << "Expected Transaction Location" << setw(35) << left << "Actual Transaction Location" << endl;
		for (int i = 0; i < flagged_transactions_rule_1.size(); i++)
		{
			Transaction_Account trans_acc = flagged_transactions_rule_1[i];
			File_2 << setw(25) << left << trans_acc.get_first_name() + " " + trans_acc.get_last_name() << setw(25) << left << trans_acc.get_account_number() << setw(25) << left << trans_acc.get_transaction_number() << setw(35) << left << trans_acc.get_actual_state() << setw(25) << left << trans_acc.get_shopped_state() << endl;
		}
		File_2.close();
	}
}; 