// AccountDatabase.h
// AccountDatabase class definition.
#ifndef ACCOUNT_DATABASE_H
#define ACCOUNT_DATABASE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Account.h" // Account class definition
using namespace std;

class AccountDatabase
{
public:
	AccountDatabase(); // constructor loads accounts from Accounts.dat
	~AccountDatabase(); // destructor saves accounts into Accounts.dat

	// called in LogIn::run() to determine whether email address and password match those of an Account
	bool authenticateUser(string, string);

	void pushBack(Account &newAccount); // add newAccount at the end of accounts

	// return a pointer to the first Account object in accounts, containing specified email address
	Account * getAccount(string);
private:
	vector< Account > accounts; // vector of the customer's accounts

	void loadAccountDetails();
	void saveAccountDetails();
}; // end class AccountDatabase



AccountDatabase::AccountDatabase()
{
	loadAccountDetails();
}

AccountDatabase::~AccountDatabase()
{
	saveAccountDetails();
}

void AccountDatabase::loadAccountDetails()
{
	ifstream inFile("Accounts.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	Account temp;//宣告一個新的Account,用來暫存讀取到的資料

	accounts.resize(0);

	while (inFile.read(reinterpret_cast<char *>(&temp), sizeof(Account)))
		pushBack(temp);
	
	inFile.close();
	
}

void AccountDatabase::saveAccountDetails()
{
	ofstream outFile("Accounts.dat", ios::binary);

	if (!outFile) {
		cout << "The file couldn't be stored.";
		exit(1);
	}

	for (unsigned int i = 0; i < accounts.size(); i++)
		outFile.write(reinterpret_cast<const char *>(&accounts[i]), sizeof(Account));
	

	outFile.close();
}


void AccountDatabase::pushBack(Account &newAccount)
{
	//accounts.push_back(Account(newAccount.getEmail(), newAccount.getPassword(), newAccount.getName(), newAccount.getAddress(), newAccount.getPhone()));
	accounts.push_back(newAccount);
}

bool AccountDatabase::authenticateUser(string add, string pas)
{

	for (unsigned int i = 0; i < accounts.size(); i++){
		if (accounts[i].getEmail() == add)
		return true;
	}
	return false;
}

Account *AccountDatabase::getAccount(string _userAccount)
{
	for (unsigned int i = 0; i < accounts.size(); i++)
	if (accounts[i].getEmail() == _userAccount)
		return &accounts[i];

		return NULL;
}


#endif // ACCOUNT_DATABASE_H