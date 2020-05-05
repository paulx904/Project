#include"ATM.h"
using namespace std;



#ifndef User1_H
#define User1_H

class User1 : public ATM
{
public:
	User1();
	~User1();

private:

	
};

#endif

User1::User1()
{
	string acn = {"12345"};
	string pin = {"54321"};

	set_accountNumber(acn);
	set_PIN(pin);
	set_availableBalance(1000.0);
	set_totalBalance(1200.0);
}

User1::~User1()
{

}



