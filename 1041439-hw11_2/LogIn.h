#ifndef LOGIN_H
#define LOGIN_H

#include "MakingOrder.h"
#include "OrderHistory.h"
#include "AccountDatabase.h"
// AccountDatabase class definition

class LogIn
{
public:
	LogIn(AccountDatabase &); // constructor initializes data members
	void run(); // start the Registration
private:
	//   Account newAccount; // a new account
	AccountDatabase &accountDatabase; // account database
	int enterChoice();
}; // end class Registration




LogIn::LogIn(AccountDatabase & _accountDatabase)
:accountDatabase(_accountDatabase)
{

}

void LogIn::run()
{
	string add;
	string pas;


	while (true){
		cout << "Email (Account number) (0 to end): ";
		cin >> add;
		if (add[0] - '0' == 0 && add.size() == 1)
			break;
		if (!(accountDatabase.authenticateUser(add, pas)))
			cout << "No account exists with the e-mail!\n";
		else{
			cout << "Password: ";
			cin >> pas;
			if (!(*accountDatabase.getAccount(add)).validatePassword(pas))
				cout << "Invalid password. Please try again.\n";
			else
				break;
		}	
	};
	
	if (add[0] - '0' != 0 || add.size() != 1){

		OrderDatabase oderDatabase;
		MakingOrder makingOrder(accountDatabase, oderDatabase);
		OrderHistory orderHistory(accountDatabase, oderDatabase);

		int choice;

		while ((choice = enterChoice()) != 3)
		{
			switch (choice)
			{
			case 1:
				makingOrder.run(add);
				break;
			case 2:
				orderHistory.run(add);
				break;
			default:
				cerr << "\nIncorrect choice" << endl;
				break;
			}
		}
	}
}

int LogIn::enterChoice()
{
	cout << "\nEnter your choice\n"
		<< "1. Making order\n"
		<< "2. Order history\n"
		<< "3. Back to top\n? ";

	int menuChoice;
	cin >> menuChoice;
	return menuChoice;

}




#endif