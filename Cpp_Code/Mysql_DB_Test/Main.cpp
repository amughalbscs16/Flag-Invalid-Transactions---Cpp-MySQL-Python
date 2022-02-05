// MySqlTest.cpp : Defines the entry point for the console application.
//
#include "Imports.hpp";
#include "Account.hpp";
#include "Transaction.hpp";

MYSQL* make_mysql_conn()
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

void read_transactions(MYSQL* conn, vector<Transaction>& transactions)
{
	int qstate;
	MYSQL_ROW row;
	MYSQL_RES* res;
	string query = "SELECT * FROM transactions";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			printf("ID: %s, Name: %s, Value: %s\n", row[0], row[1], row[2]);
		}
	}
	else
	{
		cout << "Query failed: " << mysql_error(conn) << endl;
	}

}
void read_accounts(MYSQL* conn, vector<Account>& accounts)
{
	int qstate;
	MYSQL_ROW row;
	MYSQL_RES* res;
	string query = "SELECT * FROM accounts";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			printf("ID: %s, Name: %s, Value: %s\n", row[0], row[1], row[2]);
		}
	}
	else
	{
		cout << "Query failed: " << mysql_error(conn) << endl;
	}
}


int main()
{
	
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL* conn = make_mysql_conn();
	vector<Transaction> transactions;
	vector<Account> accounts;
	if (conn) {
		read_transactions(conn, transactions);
		read_accounts(conn, accounts);
	}
	

	return 0;
}
