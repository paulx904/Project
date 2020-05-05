#include"ATM.h"
int ATM::get_accountNumber()
{
	return accountNumber;
}

int ATM::get_PIN()
{
	return PIN;
}

float ATM::get_availableBalance()
{
	return availableBalance;
}

float ATM::get_totalBalance()
{
	return totalBalance;
}

void ATM::set_accountNumber(int acn)
{
	accountNumber = acn;
}

void ATM::set_PIN(int pin)
{
	PIN = pin;
}

void ATM::set_availableBalance(float ab)
{
	availableBalance = ab;
}

void ATM::set_totalBalance(float tb)
{
	totalBalance = tb;
}

bool ATM::checkID(int acn, int pin)
{
	if (accountNumber == acn && PIN == pin)
		return true;
	else
		return false;
}

void ATM::withdraw(int withdrawOptions)
{
	switch (withdrawOptions)
	{
	case 1:
		if (availableBalance - 20>=0)
		set_availableBalance(availableBalance - 20);
		break;
	case 2:
		if (availableBalance - 40 >= 0)
		set_availableBalance(availableBalance - 40);
		break;
	case 3:
		if (availableBalance - 60 >= 0)
		set_availableBalance(availableBalance - 60);
		break;
	case 4:
		if (availableBalance - 100 >= 0)
		set_availableBalance(availableBalance - 100);
		break;
	case 5:
		if (availableBalance - 200 >= 0)
		set_availableBalance(availableBalance - 200);
		break;
	case 6:
		break;
	}

}

void ATM::deposit(float ammount)
{
	
	set_totalBalance(totalBalance + ammount/100);
}

User1::User1()
{
	int acn = 12345;
	int pin = 54321;

	set_accountNumber(acn);
	set_PIN(pin);
	set_availableBalance(1000.0);
	set_totalBalance(1200.0);
}

User1::~User1()
{

}


User2::User2()
{
	int acn = 98765;
	int pin = 56789;

	set_accountNumber(acn);
	set_PIN(pin);
	set_availableBalance(200.0);
	set_totalBalance(200.0);
}

User2::~User2()
{

}

