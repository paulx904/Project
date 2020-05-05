// MakingOrder.h
// MakingOrder class definition.
#ifndef MAKING_ORDER_H
#define MAKING_ORDER_H

#include <stdlib.h>
#include <time.h>
#include "AccountDatabase.h"// AccountDatabase class definition
#include "OrderDatabase.h" // OrderDatabase class definition

class MakingOrder
{
public:
	MakingOrder(AccountDatabase &, OrderDatabase &); // constructor initializes data members
	void run(string email); // start the MakingOrder
	int editCart(); // modify the quantity of some food in the shopping cart
	void checkout(Account * userAccountPtr); // creates an order, and push it into orderDatabase
private:
	char orderNumber[12];
	Account currentAccount; // current account
	AccountDatabase &accountDatabase; // account database
	OrderDatabase &orderDatabase; // order database

	int enterChoice(); // let user choose: 1. Continue Shopping, 2. Proceed to Checkout or 3. Abandon
}; // end class MakingOrder


MakingOrder::MakingOrder(AccountDatabase &_accountDatabase, OrderDatabase &_orderDatabase)
:accountDatabase(_accountDatabase),
orderDatabase(_orderDatabase)
{
	
}

void MakingOrder::run(string email)
{
	currentAccount = (*accountDatabase.getAccount(email));

	currentAccount.displayCart();
	editCart();
	currentAccount.displayCart();


	int choice = 0;

	while ((choice = enterChoice()) != 3){
		switch (choice)
		{
		case 1:
			editCart();
			currentAccount.displayCart();
			break;
		case 2:
			checkout(&currentAccount);;
			break;
		default:
			break;
		}
	} 
}

int MakingOrder::editCart()
{
	int code,quanity;

	cout << "Enter foods code : ";
	cin >> code;

	cout << "Enter quantity : ";
	cin >> quanity;
		
	currentAccount.modifyCart(code, quanity);

	return 0;
}

int MakingOrder::enterChoice()
{
	cout << "1. Continue Shopping\n"
		<< "2. Proceed to Checkout\n"
		<< "3. Abandon\n?";
		 
	int menuChoice;

	cin >> menuChoice;
	return menuChoice;
}

void MakingOrder::checkout(Account * userAccountPtr)
{
	int total = 0;

	srand(time(NULL));
	
		_itoa_s(rand() % 90000000000 +10000000000, orderNumber,10);//以亂數隨機產生訂單編號
		orderNumber[0] = 'Q';


	cout << "Order Number: " << orderNumber << endl
		<< "Full Name : " << userAccountPtr->getName() << endl
		<< "Shipping Address : " << userAccountPtr->getAddress() << endl
		<< "Phone Number : " << userAccountPtr->getPhone() << endl
		<< "Bank account : 合作金庫 0062013162077139" << endl << endl;

	cout << "Item Code                    Item     Price  Quantity  Subtotal\n";

		for (int i = 1; i < 15; i++)
		if (userAccountPtr->getCart()[i] != 0){
			cout << setw(9) << i << setw(24) << foods[i] << setw(10) << price[i] << setw(10)
				<< userAccountPtr->getCart()[i] << setw(10) << price[i] * userAccountPtr->getCart()[i] << endl << endl;
			total += price[i] * userAccountPtr->getCart()[i];

		}
		
		cout << "Total : " << total << endl;

		Order newOrder(orderNumber, userAccountPtr->getEmail());//宣告一個Order,用來存放此次的訂單資料
	
		newOrder.setOrderDetails(userAccountPtr->getCart());//設定商品數量
		orderDatabase.pushBack(newOrder);
		
}


#endif // MAKING_ORDER_H