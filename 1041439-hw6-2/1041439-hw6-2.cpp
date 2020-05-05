// Check if a positive integer is a Palindrome
#include <iostream>
using namespace std;

bool isPalindrome(int number, int factor);

int main()
{
	int number; // a positive integer
	cout << "Enter a positive integer: ";
	cin >> number;

	// puts 10^(numDigits-1) (i.e., the smallest numDigits-digit positive integer) into factor
	int temp = number;
	int factor = 1; // power of ten
	while (temp > 9)
	{
		temp /= 10;
		factor *= 10;
	}

	// print whether the number is a palindrome
	if (isPalindrome(number, factor))
		cout << endl << number << " is a palindrome." << endl << endl;
	else
		cout << endl << number << " is not a palindrome." << endl << endl;

	system("pause");
}

int digits[80] = {};
int k = 0;
bool isPalindrome(int number, int factor)
{
	int a, b;
	static int i = 1;
	if (number >= 10){
		digits[i-1] = number % 10;
		i++;
		number /= 10;
			isPalindrome(number, factor);
		}
	
	else{
		digits[i - 1] = number;
		for (int j = 0; j < i / 2; j++){
			if (digits[j] == digits[i - 1 - j])
				k++;
			else
				return false;
		}
		if (k == i / 2)
			return true;
	}
}