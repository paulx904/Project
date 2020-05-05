#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
	int number1; // first integer read from user
	int number2; // second integer read from user
	int number3; // third integer read from user
	int number4; // fourth integer read from user
	int number5; // fifth integer read from user
	int smallest; // smallest integer read from user
	int largest; // largest integer read from user

	cout << "Enter five integers: "; // prompt user for data
	cin >> number1 >> number2 >> number3 >> number4 >> number5;

	largest = number1; // assume first integer is largest
	smallest = number1; // assume first integer is smallest

	if (largest < number2)
		largest = number2;
	if (largest < number3)
		largest = number3;
	if (largest < number4)
		largest = number4;
	if (largest < number5)
		largest = number5;
	if (smallest > number2)
		smallest = number2;
	if (smallest > number3)
		smallest = number3;
	if (smallest > number4)
		smallest = number4;
	if (smallest > number5)
		smallest = number5;

	cout << "Largest is " << largest
		<< "\nSmallest is " << smallest << endl;

	system("pause");
} // end main