// Order.h
// Order class definition.
#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

const int price[15] = { 0, 200, 144, 184, 176, 176, 396, 200, 200, 175, 175, 200, 225, 375, 350 };

class Order
{
public:
	Order(string = "", string = ""); // constructor initializes data members
	void setOrderNumber(string theOrderNumber);
	string getOrderNumber() const;
	void setEmail(string theEmail);
	string getEmail() const;
	void setOrderDetails(int theOrderDetails[]);
	void displayOrderDetails() const;
private:
	char orderNumber[12];
	char email[40];
	int quantity[15]; // quantity[ i ] is the quantity of food #i in the order
}; // end class Order



Order::Order(string _orderNumber, string _Email)
{
	setOrderNumber(_orderNumber);
	setEmail(_Email);

}

void Order::setOrderNumber(string theOrderNumber)
{
	for (unsigned int i = 0; i < theOrderNumber.size(); i++)
	orderNumber[i] = theOrderNumber[i];
	for (int i = theOrderNumber.size(); i < 12; i++)
		orderNumber[i] = 0;
}

string Order::getOrderNumber() const
{
	return orderNumber;
}

void Order::setEmail(string theEmail)
{
	for (unsigned int i = 0; i < theEmail.size(); i++)
		email[i] = theEmail[i];
	for (int i = theEmail.size(); i < 40; i++)
		email[i] = 0;
}

string Order::getEmail() const
{
	return email;
}

void Order::setOrderDetails(int theOrderDetails[])
{
	
	for (int i = 0; i < 15; i++)
		quantity[i] = theOrderDetails[i];
		
}

void Order::displayOrderDetails() const
{

	cout << "Your order details : \n"
	<< "                    Item  Price  Quantity  Subtotal\n";
		
	for (int i = 1; i < 15; i++){

		if (quantity[i] > 0){
			cout << setw(24) << foods[i] << setw(7) << price[i]
				<< setw(10) << quantity[i] << setw(10) << quantity[i] * price[i] << endl;
		}
	}
}


#endif // ORDER_H