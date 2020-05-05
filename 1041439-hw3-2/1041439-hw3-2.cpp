#include <iostream>
using namespace std;

int main()
{
	cout << "Enter a positive integer :";
	int number;
	int a=0;
	int sum=0;

	cin >> number;
	for (int i = 1; number >= 10; i++){
		sum = 0;
		for (int i = 1; number > 0; i++){
			a = number % 10;
			sum += a;
			number = number / 10;
		}
		number = sum;
	}


	cout << sum;


	system("pause");
}