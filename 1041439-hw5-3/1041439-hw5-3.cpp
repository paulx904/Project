// Perform huge integer division.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// enable user to input menu choice
int enterChoice();

// enable user to input two positive huge integers from user
void inputTwoHugeInts(int hugeInt1[], int hugeInt2[], int &hugeInt1Size, int &hugeInt2Size);

// Returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size);

// Returns true if and only if hugeInt1 <= hugeInt2
bool lessEqual(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size);

// sum = addend + adder
void addition(int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize);

// difference = minuend - subtrahend
void subtraction(int minuend[], int subtrahend[], int difference[],
	int &minuendSize, int subtrahendSize, int &differenceSize);

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],
	int multiplicandSize, int multiplierSize, int &productSize);

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
	int dividendSize, int divisorSize, int &quotientSize, int &remainderSize);

bool equal(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size);

// hugeInt /= 10
void divideBy10(int hugeInt[], int &hugeIntSize);

// cout << hugeInt1 << string << hugeInt2 << endl << endl;
void printRelational(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size, char string[]);

// cout << hugeInt1 << op << hugeInt2 << " == " << hugeInt3 << endl << endl;
void printArithmetic(int hugeInt1[], int hugeInt2[], int hugeInt3[], char op,
	int hugeInt1Size, int hugeInt2Size, int hugeInt3Size);

const int arraySize = 80;

// function main begins program execution
int main()
{
	int n1[arraySize] = { 0 };
	int n1Size = 0;
	int n2[arraySize] = { 0 };
	int n2Size = 0;
	int n3[arraySize] = { 0 };
	int n3Size = 0;
	int n4[arraySize] = { 0 };
	int n4Size = 0;

	int choice = enterChoice();

	switch (choice)
	{
	case 1:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		addition(n1, n2, n3, n1Size, n2Size, n3Size);
		printArithmetic(n1, n2, n3, '+', n1Size, n2Size, n3Size);
		break;
	case 2:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (lessEqual(n2, n1, n2Size, n1Size))
		{
			subtraction(n1, n2, n3, n1Size, n2Size, n3Size);
			printArithmetic(n1, n2, n3, '-', n1Size, n2Size, n3Size);
		}
		break;
	case 3:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		multiplication(n1, n2, n3, n1Size, n2Size, n3Size);
		printArithmetic(n1, n2, n3, '*', n1Size, n2Size, n3Size);
		break;
	case 4:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		division(n1, n2, n3, n4, n1Size, n2Size, n3Size, n4Size);
		printArithmetic(n1, n2, n3, '/', n1Size, n2Size, n3Size);
		printArithmetic(n1, n2, n4, '%', n1Size, n2Size, n4Size);
		break;
	default: // invalid value
		cout << "Program should never get here!";
	} // end switch

	system("pause");
} // end function main

// enable user to input menu choice
int enterChoice()
{
	// display available options
	cout << "Enter your choice\n"
		<< " 1 - test add\n"
		<< " 2 - test subtract\n"
		<< " 3 - test multiply\n"
		<< " 4 - test divide\n";

	int menuChoice;
	do {
		cout << "? ";
		cin >> menuChoice; // input menu selection from user
	} while ((menuChoice < 1) || (menuChoice > 4));
	cout << endl;

	return menuChoice;
} // end function enterChoice

// enable user to input two positive huge integers from user
void inputTwoHugeInts(int hugeInt1[], int hugeInt2[], int &hugeInt1Size, int &hugeInt2Size)
{
	char string1[arraySize];
	char string2[arraySize];
	cout << "Enter two positive huge integers:\n";
	cin >> string1 >> string2;
	cout << endl;

	hugeInt1Size = strlen(string1);
	for (int i = 0; i < hugeInt1Size; ++i)
		hugeInt1[i] = string1[hugeInt1Size - i - 1] - '0';

	hugeInt2Size = strlen(string2);
	for (int i = 0; i < hugeInt2Size; ++i)
		hugeInt2[i] = string2[hugeInt2Size - i - 1] - '0';
}

void divideBy10(int hugeInt[], int &hugeIntSize)
{
	for (int i = 1; i < hugeIntSize; i++)
		hugeInt[i - 1] = hugeInt[i];

	hugeIntSize--;
	hugeInt[hugeIntSize] = 0;
}

// cout << hugeInt1 << string << hugeInt2 << endl << endl;
void printRelational(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size, char string[])
{
	for (int i = hugeInt1Size - 1; i >= 0; i--)
		cout << hugeInt1[i];

	cout << " " << string << " ";

	for (int i = hugeInt2Size - 1; i >= 0; i--)
		cout << hugeInt2[i];
	cout << endl << endl;
}

// cout << hugeInt1 << op << hugeInt2 << " == " << hugeInt3 << endl << endl;
void printArithmetic(int hugeInt1[], int hugeInt2[], int hugeInt3[], char op,
	int hugeInt1Size, int hugeInt2Size, int hugeInt3Size)
{
	for (int i = hugeInt1Size - 1; i >= 0; i--)
		cout << hugeInt1[i];

	cout << " " << op << " ";
	for (int i = hugeInt2Size - 1; i >= 0; i--)
		cout << hugeInt2[i];

	cout << " == ";
	for (int i = hugeInt3Size - 1; i >= 0; i--)
		cout << hugeInt3[i];
	cout << endl << endl;
}

bool less(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size)
{
	for (int i = hugeInt1Size - 1; i >= 0; i--){
		if (hugeInt2[i] > hugeInt1[i]){
			return true;
		}
		else  {
			return false;
		}
	}
}

bool lessEqual(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size)
{
	if (equal(hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size) || less(hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size))
		return true;
	else
		return false;
}


void addition(int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize)
{
	sumSize = (addendSize >= adderSize) ? addendSize + 1 : adderSize + 1;
	for (int i = 0; i < sumSize; i++){
		sum[i] += addend[i] + adder[i];
		if (sum[i] >= 10){
			sum[i] -= 10;
			sum[i + 1]++;
		}
	}
	for (int i = sumSize - 1; sum[i] == 0; i--)
		sumSize--;
}

void subtraction(int minuend[], int subtrahend[], int difference[],
	int &minuendSize, int subtrahendSize, int &differenceSize)
{
	differenceSize = (minuendSize >= subtrahendSize) ? minuendSize + 1 : subtrahendSize + 1;
	if (equal(minuend, subtrahend, minuendSize, subtrahendSize)){
		differenceSize = 1;
		difference[0] = 0;
	}
	else{
		if (less(subtrahend, minuend, subtrahendSize, minuendSize)){
			for (int i = 0; i < minuendSize; i++){
				difference[i] += minuend[i] - subtrahend[i];
				if (difference[i] < 0){
					difference[i + 1] --;
					difference[i] += 10;
				}
			}

			for (int i = differenceSize - 1; difference[i] == 0; i--)
				differenceSize--;
		}
	}
}

void multiplication(int multiplicand[], int multiplier[], int product[], 
	int multiplicandSize, int multiplierSize, int &productSize)
{
	productSize = multiplicandSize + multiplierSize;
	for (int i = 0; i < multiplicandSize; i++){
		for (int j = 0; j < multiplierSize; j++){
			product[i + j] += multiplicand[i] * multiplier[j];
		}
	}
	for (int i = 0; i < productSize; i++){
		if (product[i] >= 10){
			product[i + 1] += product[i] / 10;
			product[i] %= 10;
		}
	}
	while (product[productSize - 1] == 0){
		productSize--;
	}
}

void division(int dividend[], int divisor[], int quotient[], int remainder[],
	int dividendSize, int divisorSize, int &quotientSize, int &remainderSize)
{
	int n = dividendSize - divisorSize;
	int bufferSize, k, buffer[arraySize] = {};

	if (equal(dividend, divisor, dividendSize, divisorSize)){
		quotient[0] = 1;
		remainder[0] = 0;
		quotientSize = 1;
		remainderSize = 1;
	}
	else{
		for (int i = divisorSize - 1; i >= 0; i--){
			buffer[n + i] = divisor[i];
		}

		bufferSize = dividendSize;
		quotientSize = n + 1;

		if (less(dividend, buffer, dividendSize, bufferSize)){
			divideBy10(buffer, bufferSize);
			quotientSize--;
		}

		

		for (int i = 0; i < dividendSize; i++)
			remainder[i] = dividend[i];

		remainderSize = dividendSize;

		for (k = quotientSize - 1; k >= 0; k--){
			while (lessEqual(buffer, remainder, bufferSize, remainderSize)){
				subtraction(remainder, buffer, remainder, remainderSize, bufferSize, remainderSize);
				quotient[k]++;
			}
			divideBy10(buffer, bufferSize);
		}
	}
}

bool equal(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size)
{
	int i = 0;
	if (hugeInt1Size != hugeInt2Size)
		return false;
	else{
		for (; hugeInt1Size; i++){
			if (hugeInt1[i] != hugeInt2[i])
				break;

		}
	}
	if (i == hugeInt1Size)
			return true;
}