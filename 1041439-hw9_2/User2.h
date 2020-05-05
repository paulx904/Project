#include"ATM.h"
using namespace std;



#ifndef User2_H
#define User2_H

class User2 : public ATM
{
public:
	User2();
	~User2();

private:


};

#endif


User2::User2()
{
	string acn = { "98765" };
	string pin = { "56789" };

	set_accountNumber(acn);
	set_PIN(pin);
	set_availableBalance(200.0);
	set_totalBalance(200.0);
}

User2::~User2()
{

}

