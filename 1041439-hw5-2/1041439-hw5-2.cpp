// Convert a binary value to its decimal equivalent.
#include <iostream>
#include <math.h>
using namespace std;

int decimal(int binary);

int main()
{
	int binary; // binary value
	// prompt for and read in a binary number
	cout << "Enter a positive binary integer: ";
	cin >> binary;

	cout << "The decimal equivalent of " << binary << " is " << decimal(binary) << endl;

	system("pause");
} // end main


int decimal(int binary){
	static int i = -1;
	i++;
	int number = binary;
	if (number >= 10){
		number /= 10;
		return (binary % 10) *pow(2,i) + decimal(number);
	}
	else
		return binary*pow(2,i);
}