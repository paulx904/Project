// Reverse the digits of a positive integer
#include <iostream>
using namespace std;

int main()	
{
	int number;
	int a;
	cout << "Enter a positive integer : ";
	cin >> number;
	
	cout << endl << "The reverse of " << number << " : ";
	for (int i = 1; number != 0; i++)
	{
		a = number % 10;
		cout << a;
		number = number / 10;
		
		
	}
	cout << endl << endl;
	system("pause");
} // end main