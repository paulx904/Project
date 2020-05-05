// Account.h
// Account class definition.
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iomanip>
using namespace std;

const char foods[15][24] = { "", "小籠包（12入）", "菜肉蒸餃（8入）", "蝦肉蒸餃（8入）", "鮮魚蒸餃（8入）",
"香菇素餃（8入）", "蝦仁燒賣（12入）", "鮮肉大包（5入）", "菜肉大包（5入）",
"豆沙大包（5入）", "芝麻大包（5入）", "芋泥大包（5入）", "香菇素包（5入）",
"鮮肉粽子（5入）", "豆沙粽子（5入）" };

class Account
{
public:
	Account(string = "", string = "", string = "", string = "", string = ""); // constructor sets attributes

	bool validatePassword(string userPassword) const; // determines whether a user-specified password
	// matches password in Account

	// accessor functions for email
	void setEmail(string);
	string getEmail() const;

	// accessor functions for password
	void setPassword(string);
	string getPassword() const;

	// accessor functions for name
	void setName(string);
	string getName() const;

	// accessor functions for address
	void setAddress(string);
	string getAddress() const;

	// accessor functions for phone
	void setPhone(string);
	string getPhone() const;

	// accessor functions for cart
	void setCart(int *);
	int * getCart();

	void modifyCart(int code, int amount); // cart[ code ] is modified to amount

	void displayAccountDetails() const; // display email, name, address and phone of Account

	void displayCart() const; // Code, Item and Quantity of each foods in the shopping cart
private:
	char email[40]; // used as the account number
	char password[20];
	char name[8];
	char address[80];
	char phone[12];
	int cart[15]; // cart[ i ] is the quantity of food #i in the shopping cart
}; // end class Account


Account::Account(string _email, string _password, string _name, string _address, string _phone)
{
	int _cart[15] = { 0 };

	setEmail(_email);
	setPassword(_password);
	setName(_name);
	setAddress(_address);
	setPhone(_phone);
	setCart(_cart);
}

bool Account::validatePassword(string userPassword) const
{
	if (getPassword() == userPassword)
		return true;
	else
		return false;
}

void Account::setEmail(string _email)
{
	for (unsigned int i = 0; i < _email.size(); i++)
		email[i] = _email[i];
	for (unsigned int i = _email.size(); i < 40; i++)
		email[i] = 0;
		
}
	
string Account::getEmail() const
{
	return email;
}

void Account::setPassword(string _password)
{
	for (unsigned int i = 0; i < _password.size(); i++)
		password[i] = _password[i];
	for (unsigned int i = _password.size(); i < 20; i++)
		password[i] = 0;
}

string Account::getPassword() const
{
	return password;
}

void Account::setName(string _name)
{
	for (unsigned int i = 0; i < _name.size(); i++)
		name[i] = _name[i];
	for (unsigned int i = _name.size(); i < 8; i++)
		name[i] = 0;
}

string Account::getName() const
{
	return name;
}

void Account::setAddress(string _address)
{
	for (unsigned int i = 0; i < _address.size(); i++)
		address[i] = _address[i];
	for (unsigned int i = _address.size(); i < 80; i++)
		address[i] = 0;
}

string Account::getAddress() const
{
	return address;
}

void Account::setPhone(string _phone)
{
	for (unsigned int i = 0; i < _phone.size(); i++)
		phone[i] = _phone[i];
	for (unsigned int i = _phone.size(); i < 12; i++)
		phone[i] = 0;
}

string Account::getPhone() const
{
	return phone;
}

void Account::setCart(int *_cart)
{

	for (int i = 0; i < 15; i++)
		cart[i] = _cart[i];
	
}

int *Account::getCart()
{
	return cart;
}

void Account::modifyCart(int code, int amount)
{
	cart[code] = amount;
}

void Account::displayAccountDetails() const
{

}

void Account::displayCart() const
{
	cout << "Your shopping cart:\n"
		<< "Code                    Item  Quantity\n";
		
	for (int i = 1; i < 15; i++)
		cout << setw(4) << i << setw(24) << foods[i] << setw(10) << cart[i] << endl;

}






#endif // ACCOUNT_H