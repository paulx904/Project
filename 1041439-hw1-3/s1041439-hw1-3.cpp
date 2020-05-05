#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
	int number; // integer read from user
	int a;
	int b;
	int c;
	int d;
	int e;

	cout << "Enter a five-digit integer: "; // prompt
	cin >> number; // read integer from user

	a = number / 10000;
	b = number / 1000 - (a * 10);
	c = number / 100 - (a * 100 + b * 10);
	d = number / 10 - (a * 1000 + b * 100 + c * 10);
	e = number - (a * 10000 + b * 1000 + c * 100 + d * 10);


	cout <<a<<"   "<<b<<"   "<<c<<"   "<<d<<"  "<<e<< endl;

	system("pause");
} // end main