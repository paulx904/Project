#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "AccountDatabase.h" // AccountDatabase class definition

class Registration
{
public:
	Registration(AccountDatabase &); // constructor initializes data members
	void run(); // start the Registration
private:
	Account newAccount; // a new account
	AccountDatabase &accountDatabase; // account database
}; // end class Registration



Registration::Registration(AccountDatabase &_accountDatabase)
:accountDatabase(_accountDatabase)
{

}

void Registration::run()
{
	string email; 
	string password;
	string name;
	string address;
	string phone;
	
	cout << "Enter your e - mail address(account number) (0 to end) : ";
	
	while (true){
		cin >> email;
		if (accountDatabase.authenticateUser(email, password))
			cout << "An account already exists with the e - mail!\n";
		else
			break;
	}
	if (email[0] - '0' != 0 || email.size() != 1){

		newAccount.setEmail(email);
		


		cout << "Enter your password¡]8¡ã20 English letters or digits¡^ : ";

		while (password.size() < 8 || password.size() > 20){
			cin >> password;
			if (password.size() >= 8 && password.size() <= 20)
				break;
		}
		newAccount.setPassword(password);

		cout << "Enter your name : ";
		cin >> name;
		newAccount.setName(name);

		cout << "Enter your physical address : ";
		cin >> address;
		newAccount.setAddress(address);

		cout << "Enter your phone number : ";
		cin >> phone;
		newAccount.setPhone(phone);

		
		accountDatabase.pushBack(newAccount);

		cout << "Registration Successfully!\n\n";
	}

}

#endif