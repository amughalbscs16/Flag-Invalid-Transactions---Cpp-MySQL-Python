#include "Account.hpp"

class Database_Access {
public:
	static MYSQL* make_mysql_conn()
	{
		int port = 3306;
		const char* hostname = "localhost";
		const char* username = "root";
		const char* password = "admin";
		const char* database = "save";
		MYSQL* conn;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, hostname, username, password, database, port, NULL, 0);
		if (conn) {
			cout << "Successful connection to database!" << endl;
			return conn;
		}
		else
		{
			cout << "Connection to database unsuccessful!" << endl;
			return NULL;
		}
	}

	static void read_transactions(MYSQL* conn, map<int, Transaction>& transactions, map<int, Account>& accounts)
	{
		int count = 0;
		int qstate;
		MYSQL_ROW row;
		MYSQL_RES* res;
		string query =
			"SELECT transaction_id, account_number, transaction_datetime, transaction_amount, post_date, merchant_number, merchant_description, merchant_state, merchant_category_code, transaction_number FROM transactions";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			//Add and process transactions
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				int transaction_id = stoi(row[0]);
				int account_number = stoi(row[1]);
				string transaction_datetime = row[2];

				double transaction_amount = stod(string(row[3]));
				string post_date = row[4];
				string merchant_number = row[5];
				string merchant_description = row[6];
				string merchant_state = row[7];
				int merchant_category_code = stoi(row[8]);
				int transaction_number = stoi(row[9]);


				Transaction new_transaction = Transaction(transaction_id, account_number, transaction_datetime, transaction_amount, post_date, merchant_number, merchant_description, merchant_state, merchant_category_code, transaction_number);
				transactions.insert(pair<int, Transaction>(account_number, new_transaction));

				//Update merchant transactions in each account
				//cout << account_number;
				accounts[account_number].add_transaction_merchant(new_transaction);
				count++;
			}


		}
		else
		{
			cout << "Transactions Query failed: " << mysql_error(conn) << endl;
		}
	}

	static void read_accounts(MYSQL* conn, map<int, Account>& accounts)
	{
		int qstate;
		MYSQL_ROW row;
		MYSQL_RES* res;
		string query = "SELECT first_name, last_name, street_address, unit, city, state, zip, dob, ssn, email_address, mobile_number, account_number FROM accounts";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				int unit_x = -1;
				string first_name = row[0];
				string last_name = row[1];
				string street_address = row[2];
				if (row[3] != NULL)
					unit_x = stoi(row[3]);
				string city = row[4];
				string state = row[5];
				string zip = row[6];
				string dob = row[7];
				string ssn = row[8];
				string email_address = row[9];
				long long mobile_number = stoll(row[10]);
				int account_number = stoi(row[11]);

				Account new_account = Account(first_name, last_name, street_address, unit_x, city, state, zip, dob, ssn, email_address, mobile_number, account_number);

				accounts.insert(pair<int, Account>(account_number, new_account));
			}
		}
		else
		{
			cout << "Accounts Query failed: " << mysql_error(conn) << endl;
		}
	}
};