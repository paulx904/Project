#include <iostream>
using namespace std;

void digits(int number, int factor);

int main()
{
	int number; // a positive integer
	cout << "Enter a positive integer: ";
	cin >> number;

	int factor = 1; // power of ten
	int temp = number;
	while (temp > 9)
	{
		temp /= 10;
		factor *= 10;
	}

	cout << "\nThe digits: ";

	digits(number, factor);

	cout << endl << endl;

	system("pause");
} // end main

void digits(int number, int factor)
{
	if (number >= 10)
	{
		cout << number / factor << "  ";
		number %= factor;
		factor /= 10;
		digits(number, factor);
	}
	else
		cout << number;
}