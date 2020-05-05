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
	
	int i = 1;
	while (number != 0)
	{
		a = number % 10;
		cout << a;
		number = number / 10;

		i++;
	}
	
	cout << endl << endl;
	
	system("pause");
} // end main