// Compute all positive factors of a positive integer
#include <iostream>
using namespace std;

int main()
{
	int number;
	int factor;
	
	cout << "Enter a positive integer: ";
	cin >> number;
	cout << "\n\nThe positive factors of " << number << " :" << endl;
	
	int i=1;
	while (i <= number)
	{
		if (number % i == 0)
			cout << i << endl;
		i++;
	}
	cout << endl << endl;

	system("pause");
} // end main