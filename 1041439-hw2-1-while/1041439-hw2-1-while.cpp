// Convert a binary number to its decimal equivalent.
#include <iostream>
using namespace std;

int main()
{
	int number1;
	int number2;
	int number3;
	int sum = 0;
	int finallysum = 0;
	int i = 0;
	cout << "Enter a positive binary integer : ";
	cin >> number1;

	number2 = number1;
	while (number2 != 0){
		number3 = number2;
		number2 = number2 / 10;
		if (number3 % 10 != 0){
			sum = number3 % 10 * pow(2, i);
			finallysum += sum;
			
		}
		
		i++;
	}


	cout << "The decimal equivalent of " << number1 << " is " << finallysum << " ." << endl;


	system("pause");
} // end main