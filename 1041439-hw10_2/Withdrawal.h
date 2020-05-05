// Withdrawal.h
// Withdrawal class definition. Represents a withdrawal transaction.
#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition

class Withdrawal
{
public:
	Withdrawal(int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills);
	void execute(); // perform the withdrawal transaction
private:
	int accountNumber; // indicates account involved
	vector< Account > &accounts; // reference to the vector of the bank's Accounts
	int amount; // amount to withdraw
	int &remainingBills;

	// get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
	Account * getAccount(int accountNumber, vector< Account > &accounts);

	// display a menu of withdrawal amounts and the option to cancel;
	// return the chosen amount or 0 if the user chooses to cancel
	int displayMenuOfAmounts() const;
}; // end class Withdrawal


Withdrawal::Withdrawal(int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills)
:accounts(atmAccounts),remainingBills(atmRemainingBills)
{
	accountNumber = userAccountNumber;
}

Account *Withdrawal::getAccount(int accountNumber, vector< Account > &accounts)
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

void Withdrawal::execute()
{

	switch (displayMenuOfAmounts())
	{
	case 1:
		amount = 20;
		if (remainingBills >= amount)
			getAccount(accountNumber,accounts)->debit(amount);
		break;
	case 2:
		amount = 40;
		if (remainingBills >= amount)
			getAccount(accountNumber, accounts)->debit(amount);
		break;
	case 3:
		amount = 60;
		if (remainingBills >= amount)
			getAccount(accountNumber, accounts)->debit(amount);
		break;
	case 4:
		amount = 100;
		if (remainingBills >= amount)
			getAccount(accountNumber, accounts)->debit(amount);
		break;
	case 5:
		amount = 200;
		if (remainingBills >= amount)
			getAccount(accountNumber, accounts)->debit(amount);
		break;
	case 6:
		break;
	}

	remainingBills = getAccount(accountNumber, accounts)->getAvailableBalance();

	cout << "Please take your cash from the cash dispenser." << endl;
}

int Withdrawal::displayMenuOfAmounts() const
{
	cout << "Withdrawal options:" << endl
		<< "1 - $20" << endl
		<< "2 - $40" << endl
		<< "3 - $60" << endl
		<< "4 - $100" << endl
		<< "5 - $200" << endl
		<< "6 - Cancel transaction" << endl << endl
		<< "Choose a withdrawal option (1-6): ";

	int withdrawChoice;

	do{
		cin >> withdrawChoice;
	} while ((withdrawChoice < 0) || (withdrawChoice > 6));

	return withdrawChoice;
	
}



#endif // WITHDRAWAL_H