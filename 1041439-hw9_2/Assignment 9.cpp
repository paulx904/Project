#include<iostream>
#include<iomanip>
#include"ATM.h"


using namespace std;

int mainMenu();
int withdrawOptions();

int main()
{
	User1 u1;
	User2 u2;

	int acn;
	int pin;


	int menuChoice;

	do{
		cout << "Welcome!\n\n"
			<< "Please enter your account number: ";
		cin >> acn;
		cout << "Enter your PIN : ";
		cin >> pin;

		if (u1.checkID(acn, pin)){
			do{
				switch (menuChoice = mainMenu())
				{
				case 1:
					cout << "Balance Information :" << endl
						<< "-Available balance : " << fixed <<setprecision(2) << u1.get_availableBalance() << endl
						<< "-Total balance : " << fixed << setprecision(2) << u1.get_totalBalance() << endl;
					break;
				case 2:
					u1.withdraw(withdrawOptions());
					cout << "Please take your cash from the cash dispenser." << endl;
					break;
				case 3:
					float ammount;
					cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
					cin >> ammount;
					cout << "Please insert a deposit envelope containing $10.00 in the deposit slot.";
					u1.deposit(ammount);
					cout << "Your envelope has been received." << endl
						<< "The money deposited will not be available until we verify"
						<< "the amount of any enclosed cash, and any enclosed checks clear." << endl;
					break;
				case 4:
					cout << "\nExiting the system..." << endl
						<< "Thank you!Goodbye!\n\n";
					break;

				}
			} while (menuChoice != 4);

		}

		else if (u2.checkID(acn, pin)){
			do{
				switch (menuChoice=mainMenu())
				{
				case 1:
					cout << "\nBalance Information :" << endl
						<< "-Available balance : " << u2.get_availableBalance() << endl
						<< "-Total balance : " << u2.get_totalBalance() << endl;
					break;
				case 2:
					u2.withdraw(withdrawOptions());
					cout << "Please take your cash from the cash dispenser." << endl;
					break;
				case 3:
					float ammount;
					cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
					cin >> ammount;
					cout << "Please insert a deposit envelope containing $10.00 in the deposit slot.";
					u2.deposit(ammount);
					cout << "Your envelope has been received." << endl
						<< "The money deposited will not be available until we verify"
						<< "the amount of any enclosed cash, and any enclosed checks clear." << endl;
					break;
				case 4:
					cout << "\nExiting the system..." << endl
						<< "Thank you!Goodbye!\n" << endl;
					break;

				}
			} while (menuChoice != 4);
		}

	} while (true);


	system("pause");
	return 0;
}

int mainMenu()
{
	
	cout << "\nMain menu : "<<endl
		<< "1 - View my balance" << endl
		<< "2 - Withdraw cash" << endl
		<< "3 - Deposit funds" << endl
		<< "4 - Exit" << endl
		<< "\nEnter a choice: ";

	int menuChoice;
	do {
		cin >> menuChoice;
	} while ((menuChoice < 0) || (menuChoice > 4));

	return menuChoice;
		
}

int withdrawOptions()
{
	cout << "Withdrawal options:" << endl
		<< "1 - $20" << endl
		<< "2 - $40" << endl
		<< "3 - $60" << endl
		<< "4 - $100" << endl
		<< "5 - $200" << endl
		<< "6 - Cancel transaction" << endl<<endl
		<< "Choose a withdrawal option (1-6): ";

	int withdrawChoice;

	do{
		cin >>withdrawChoice;
	} while ((withdrawChoice < 0) || (withdrawChoice > 6));

	return withdrawChoice;

}