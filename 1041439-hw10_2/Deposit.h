// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Deposit
{
public:
	Deposit(int userAccountNumber, vector< Account > &atmAccounts);
	void execute(); // perform the deposit transaction
private:
	int accountNumber; // indicates account involved
	vector< Account > &accounts; // reference to the vector of the bank's Accounts
	double amount; // amount to deposit

	// get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
	Account * getAccount(int accountNumber, vector< Account > &accounts);
	double promptForDepositAmount() const; // prompt user to enter a deposit amount in cents 
}; // end class Deposit



Deposit::Deposit(int userAccountNumber, vector< Account > &atmAccounts)
:accounts(atmAccounts)
{
	accountNumber = userAccountNumber;
}

Account *Deposit::getAccount(int accountNumber, vector< Account > &accounts)
{
	// loop through accounts searching for matching account number
	for (size_t i = 0; i < accounts.size(); i++)
	{
		// return current account if match found
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];
	} // end for

	return NULL; // if no matching account was found, return NULL
}

void Deposit::execute()
{

	amount = promptForDepositAmount();

	if (amount > 0){

		(*getAccount(accountNumber, accounts)).credit(amount);

		cout << "Your envelope has been received." << endl
			<< "The money deposited will not be available until we verify"
			<< "the amount of any enclosed cash, and any enclosed checks clear." << endl;
	}
}

double Deposit::promptForDepositAmount() const
{
	double insertAmount;
	cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
	cin >> insertAmount;
	cout << "Please insert a deposit envelope containing $10.00 in the deposit slot.";

	return insertAmount;
}








#endif // DEPOSIT_H