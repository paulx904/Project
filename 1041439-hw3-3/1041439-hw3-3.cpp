#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int digits;
	int i = 0;
	cout << "Enter the number of digits(taken from 2, 4, 6, 8) :";
	cin >> digits;
	for (; i < 1 * pow(10, digits); i++){
		int a = 1 * pow(10, digits / 2);
		int b = i / a;
		int c = i % a;
		if ((b + c)*(b + c) == i)
		{
			int j = i;
			int g = 0;
			if (i == 0)
				g = 1;
			for (; j>0;g++){
				j = j / 10;
			}
			for (; g != digits; g++){
				cout << "0";
			}
				cout << i << endl;
			
		}
	}
	system("pause");
}