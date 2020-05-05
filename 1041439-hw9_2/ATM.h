
using namespace std;

#ifndef ATM_H
#define ATM_H

class ATM
{
public:
	
	ATM(){};
	~ATM(){};

	int get_accountNumber();
	int get_PIN(); 
	float get_availableBalance();
	float get_totalBalance();

	void set_accountNumber(int acn);
	void set_PIN(int pin);
	void set_availableBalance(float ab);
	void set_totalBalance(float tb);

	bool checkID(int accountNumber, int PIN);
	void withdraw(int withdrawOptions);
	void deposit(float ammount);

private:
	int accountNumber;
	int PIN;
	float availableBalance;
	float totalBalance;
};



class User1 : public ATM
{
public:
	User1();
	~User1();

private:


};



class User2 : public ATM
{
public:
	User2();
	~User2();

private:


};




#endif






