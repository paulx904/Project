// OrderHistory.h
// OrderHistory class definition.
#ifndef ORDER_HISTORY_H
#define ORDER_HISTORY_H

#include "AccountDatabase.h" // AccountDatabase class definition
#include "OrderDatabase.h" // OrderDatabase class definition

class OrderHistory
{
public:
	OrderHistory(AccountDatabase &, OrderDatabase &); // constructor initializes data members
	void run(string email); // start the OrderHistory
private:
	AccountDatabase &accountDatabase; // account database
	OrderDatabase &orderDatabase; // order database
}; // end class OrderHistory



OrderHistory::OrderHistory(AccountDatabase &_accountDatabase, OrderDatabase &_orderDatabase)
	:accountDatabase(_accountDatabase), orderDatabase(_orderDatabase)
{

}

void OrderHistory::run(string email)
{
	vector< Order > historicalOrders;

	orderDatabase.getOrders(email, historicalOrders);//將屬於當前用戶的所有訂單資料存放到historicalOrders
	

	cout << "Your order history : \n"
		<< "Code    Order no.     Name\n";

	for (unsigned int i = 0; i < historicalOrders.size(); i++){
		cout << setw(4) << i << setw(13) << historicalOrders[i].getOrderNumber()
			<< setw(9) << (*accountDatabase.getAccount(email)).getName() << endl << endl;

	}
	

	int code;

	cout << "Choose a code (0 ~ " << historicalOrders.size() - 1 << ")";
	cin >> code;

	
	historicalOrders[code].displayOrderDetails();
	
}




#endif // ORDER_HISTORY_H