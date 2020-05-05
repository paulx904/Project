#include <iostream>
#include "LogIn.h" // Registration class definition
#include "Registration.h" // Registration class definition

int enterChoice();

int main()
{
	cout << "Welcome to DintaiFung Shopping Mall!\n";

	AccountDatabase accountDatabase;

	Registration registration(accountDatabase);
	LogIn logIn(accountDatabase);

	int choice;

	while ((choice = enterChoice()) != 3)
	{
		switch (choice)
		{
		case 1:
			logIn.run();
			break;
		case 2:
			registration.run();
			break;
		default:
			cerr << "\nIncorrect choice" << endl;
			break;
		}
	}

	cout << endl;
	system("pause");
}

int enterChoice()
{
	cout << "\nEnter your choice\n"
		<< "1. Log in\n"
		<< "2. Registration\n"
		<< "3. End Program\n? ";

	int menuChoice;
	cin >> menuChoice;
	return menuChoice;
}