// OrderDatabase.h
// OrderDatabase class definition. Represents the order's database.
#ifndef ORDER_DATABASE_H
#define ORDER_DATABASE_H

#include <vector>
#include "Order.h" // Order class definition

class OrderDatabase
{
public:
	OrderDatabase(); // constructor loads orders from Orders.dat
	~OrderDatabase(); // destructor saves orders into Orders.dat
	void pushBack(Order &newOrder); // add newOrder at the end of orders

	// called in OrderHistory::run to put all Order objects containing specified email address into historicalOrders
	void getOrders(string theEmail, vector< Order > &historicalOrders);
private:
	vector< Order > orders; // vector of the customer's orders

	void loadOrderDetails();
	void saveOrderDetails();
}; // end class OrderDatabase



OrderDatabase::OrderDatabase()
{
	loadOrderDetails();
}

OrderDatabase::~OrderDatabase()
{
	saveOrderDetails();
}


void OrderDatabase::loadOrderDetails()
{
	ifstream inFile("Orders.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}


	Order temp;
	
	while (inFile.read(reinterpret_cast<char *>(&temp), sizeof(Order)))
		pushBack(temp);

	inFile.close();
}

void OrderDatabase::saveOrderDetails()
{
	ofstream outFile("Orders.dat", ios::binary);

	if (!outFile) {
		cout << "The file couldn't be stored.";
		exit(1);
	}

	for (unsigned int i = 0; i < orders.size(); i++)

		outFile.write(reinterpret_cast<const char *>(&orders[i]), sizeof(Order));

	outFile.close();
}


void OrderDatabase::pushBack(Order &newOrder)
{
	orders.push_back(newOrder);
	
}

void OrderDatabase::getOrders(string theEmail, vector< Order > &historicalOrders)
{
	for (unsigned int i = 0; i < orders.size(); i++)
	if (orders[i].getEmail() == theEmail){
		historicalOrders.push_back(orders[i]);	
	}
}



#endif // ORDER_DATABASE_H