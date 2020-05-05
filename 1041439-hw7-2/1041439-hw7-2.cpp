// Perform huge integer operations.
#include <iostream>
using namespace std;

enum sign{ plus, minus };
int enterChoice();// enable user to input menu choice

// enable user to input two positive huge integers from user
void inputTwoHugeInts(int *&hugeInt1, int *&hugeInt2, int &hugeInt1Size, int &hugeInt2Size);

// Returns true if and only if hugeInt == 0
bool isZero(int *hugeInt, int hugeIntSize);

bool equal(int *hugeInt1, int *hugeInt2, int hugeInt1Size, int hugeInt2Size);

bool greater(int *hugeInt1, int *hugeInt2, int hugeInt1size, int hugeInt2size);

// Returns true if and only if hugeInt1 < hugeInt2
bool less(int *hugeInt1, int *hugeInt2, int hugeInt1Size, int hugeInt2Size);

// Returns true if and only if hugeInt1 <= hugeInt2
bool lessEqual(int *hugeInt1, int *hugeInt2, int hugeInt1Size, int hugeInt2Size);

// sum = addend + adder
void addition(int *addend, int *adder, int *&sum, int addendSize, int adderSize, int &sumSize);

// difference = minuend - subtrahend
void subtraction(int *minuend, int *subtrahend, int *&difference,
	int &minuendSize, int subtrahendSize, int &differenceSize);

// product = multiplicand * multiplier
void multiplication(int *multiplicand, int *multiplier, int *&product,
	int multiplicandSize, int multiplierSize, int &productSize);

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int *dividend, int *divisor, int *&quotient, int *&remainder,
	int dividendSize, int divisorSize, int &quotientSize, int &remainderSize);

// hugeInt /= 10
void divideBy10(int *hugeInt, int &hugeIntSize); 


// cout << hugeInt1 << op << hugeInt2 << " == " << hugeInt3 << endl << endl;
void printArithmetic(int *hugeInt1, int *hugeInt2, int *hugeInt3, char op,
	int hugeInt1Size, int hugeInt2Size, int hugeInt3Size, sign resultSign);

// function main begins program execution
int main()
{
	int *n1 = 0;
	int n1Size = 0;
	int *n2 = 0;
	int n2Size = 0;
	int *n3 = 0;
	int n3Size = 0;
	int *n4 = 0;
	int n4Size = 0;

	int choice = enterChoice();

	switch (choice)
	{
	case 1:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		addition(n1, n2, n3, n1Size, n2Size, n3Size); // n3 = n1 + n2
		printArithmetic(n1, n2, n3, '+', n1Size, n2Size, n3Size, sign::plus);
		break;
	case 2:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (::less(n1, n2, n1Size, n2Size))
		{
			subtraction(n2, n1, n3, n2Size, n1Size, n3Size); // n3 = n2 - n1
			printArithmetic(n1, n2, n3, '-', n1Size, n2Size, n3Size, sign::minus);
		}
		else
		{
			subtraction(n1, n2, n3, n1Size, n2Size, n3Size); // n3 = n1 - n2
			printArithmetic(n1, n2, n3, '-', n1Size, n2Size, n3Size, sign::plus);
		}
		break;
	case 3:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		multiplication(n1, n2, n3, n1Size, n2Size, n3Size); // n3 = n1 * n2
		printArithmetic(n1, n2, n3, '*', n1Size, n2Size, n3Size, sign::plus);
		break;
	case 4:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (isZero(n2, n2Size))
		{
			cout << "divide by zero!!\n\n";
			break;
		}
		division(n1, n2, n3, n4, n1Size, n2Size, n3Size, n4Size); // n3 = n1 / n2; n4 = n1 % n2
		printArithmetic(n1, n2, n3, '/', n1Size, n2Size, n3Size, sign::plus);
		printArithmetic(n1, n2, n4, '%', n1Size, n2Size, n4Size, sign::plus);
		break;
	default: // invalid value
		cout << "Program should never get here!";
	} // end switch

	delete[] n1;
	delete[] n2;
	delete[] n3;
	delete[] n4;

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
void inputTwoHugeInts(int *&hugeInt1, int *&hugeInt2, int &hugeInt1Size, int &hugeInt2Size)
{
	const int arraySize = 80;
	char string1[arraySize];
	char string2[arraySize];
	cout << "Enter two positive huge integers:\n";
	cin >> string1 >> string2;
	cout << endl;

	hugeInt1Size = strlen(string1);
	hugeInt1 = new int[hugeInt1Size];
	for (int i = 0; i < hugeInt1Size; ++i)
		hugeInt1[i] = string1[hugeInt1Size - i - 1] - '0';

	hugeInt2Size = strlen(string2);
	hugeInt2 = new int[hugeInt2Size];
	for (int i = 0; i < hugeInt2Size; ++i)
		hugeInt2[i] = string2[hugeInt2Size - i - 1] - '0';
}

bool isZero(int *hugeInt, int hugeIntSize)
{
	if (hugeIntSize == 0)
		return true;
	else
	{
		for (int i = 0; i < hugeIntSize; ++i)
		if (hugeInt[i] != 0)
			return false;
		return true;
	}
}

void addition(int *addend, int *adder, int *&sum, int addendSize, int adderSize, int &sumSize)
{
	sumSize = (addendSize >= adderSize) ? addendSize + 1 : adderSize + 1;
	if (sum != 0)
		delete[] sum;
	sum = new int[sumSize];

	for (int i = 0; i < addendSize; ++i)
		sum[i] = addend[i];

	for (int i = addendSize; i < sumSize; ++i)
		sum[i] = 0;

	for (int i = 0; i < adderSize; ++i)
		sum[i] += adder[i];

	for (int i = 0; i < sumSize - 1; ++i)
	if (sum[i] > 9)
	{
		sum[i] -= 10;
		++sum[i + 1];
	}

	if (sum[sumSize - 1] == 0)
		--sumSize;
}

void subtraction(int *minuend, int *subtrahend, int *&difference,
	int &minuendSize, int subtrahendSize, int &differenceSize){

	differenceSize = (minuendSize >= subtrahendSize) ? minuendSize : subtrahendSize;
	if (difference != 0)
		delete[] difference;
	difference = new int[differenceSize];
	if (minuendSize >= subtrahendSize)
	{
		for (int i = 0; i < subtrahendSize; i++)
			difference[i] = minuend[i] - subtrahend[i];
		for (int i = subtrahendSize; i < minuendSize; i++)
			difference[i] = minuend[i];
	}
	else
	{
		for (int i = 0; i < minuendSize; i++)
			difference[i] = subtrahend[i] - minuend[i];
		for (int i = minuendSize; i < subtrahendSize; i++)
			difference[i] = subtrahend[i];
	}
	for (int i = 0; i < differenceSize - 1; i++)
	if (difference[i] < 0)
	{
		difference[i] += 10;
		difference[i + 1]--;
	}
	for (int i = differenceSize - 1; difference[i] == 0; i--)
		differenceSize--;
}

void multiplication(int *multiplicand, int *multiplier, int *&product,
	int multiplicandSize, int multiplierSize, int &productSize){
	productSize = multiplicandSize + multiplierSize;
	if (product != 0)
		delete[] product;
	product = new int[productSize];
	for (int i = 0; i < productSize; i++)
	{
		product[i] = 0;
	}
	for (int i = 0; i < multiplierSize; i++)
	{
		for (int k = 0; k < multiplicandSize; k++)
			product[i + k] = product[i + k] + multiplicand[k] * multiplier[i];
	}
	for (int i = 0; i < productSize; i++)
	{
		if (product[i] >= 10)
		{
			product[i + 1] += (product[i] / 10);
			product[i] = (product[i] % 10);
		}
	}
	for (int i = productSize - 1; product[i] == 0; i--)
			productSize--;
}

void division(int *dividend, int *divisor, int *&quotient, int *&remainder,
	int dividendSize, int divisorSize, int &quotientSize, int &remainderSize){
	int *buffer;
	int bufferSize = dividendSize;
	buffer = new int[bufferSize];
	remainderSize = divisorSize;
	remainder = new int[remainderSize];

	quotientSize = dividendSize - divisorSize;
	if (quotient != 0)
		delete[] quotient;
	quotient = new int[quotientSize];
	for (int i = 0; i < bufferSize; i++)
		buffer[i] = 0;


	int n = dividendSize - divisorSize;

	for (int i = 0; i < divisorSize; i++)
	{
		buffer[i + n] = divisor[i];
	}

	if (equal(buffer, dividend, bufferSize, dividendSize) || greater(dividend, buffer, dividendSize, dividendSize))
	{
		quotientSize++;
	}

	for (int i = 0; i < quotientSize; i++)
	{
		quotient[i] = 0;
	}

	for (int i = quotientSize - 1; i >= 0; i--)
	{
		quotient[i] = 10;

		do
		{
			quotient[i]--;
			multiplication(divisor, quotient, buffer, divisorSize, quotientSize, bufferSize);
		} while (greater(buffer, dividend, bufferSize, dividendSize));

		if (equal(buffer, dividend, bufferSize, dividendSize))
			break;
	}


	if (equal(buffer, dividend, dividendSize, dividendSize))
	{
		remainderSize = 1;
		remainder[0] = 0;
	}
	else
		subtraction(dividend, buffer, remainder, dividendSize, dividendSize, remainderSize);
}
void divideBy10(int *hugeInt, int &hugeIntSize)
{
	for (int i = 1; i < hugeIntSize; ++i)
		hugeInt[i - 1] = hugeInt[i];

	--hugeIntSize;
	hugeInt[hugeIntSize] = 0;
}

// cout << hugeInt1 << op << hugeInt2 << " == " << hugeInt3 << endl << endl;
void printArithmetic(int *hugeInt1, int *hugeInt2, int *hugeInt3, char op,
	int hugeInt1Size, int hugeInt2Size, int hugeInt3Size, sign resultSign)
{
	for (int i = hugeInt1Size - 1; i >= 0; --i)
		cout << hugeInt1[i];

	cout << " " << op << " ";

	for (int i = hugeInt2Size - 1; i >= 0; --i)
		cout << hugeInt2[i];

	cout << " == ";

	if (resultSign == sign::minus)
		cout << '-';

	for (int i = hugeInt3Size - 1; i >= 0; --i)
		cout << hugeInt3[i];
	cout << endl << endl;
}

bool greater(int *hugeInt1, int *hugeInt2, int hugeInt1size, int hugeInt2size)
{
	if (hugeInt1size < hugeInt2size)
		return false;
	if (hugeInt1size > hugeInt2size)
		return true;
	if (hugeInt1size == hugeInt2size)
	{
		for (int i = hugeInt1size - 1; i >= 0; i--)
		{
			if (hugeInt1[i] < hugeInt2[i])
				return false;
			else
				return true;
		}
	}
}

bool equal(int *hugeInt1, int *hugeInt2, int hugeInt1Size, int hugeInt2Size){
	if (hugeInt1Size != hugeInt2Size)
		return false;
	for (int i = 0; i < hugeInt1Size; i++){
		if (hugeInt1[i] == hugeInt2[i])
			return true;
		else
			return false;
	}
}

bool less(int *hugeInt1, int *hugeInt2, int hugeInt1Size, int hugeInt2Size){
	if (hugeInt2Size > hugeInt1Size)
		return true;
	if (hugeInt1Size > hugeInt2Size)
		return false;
	for (int i = hugeInt1Size - 1; i >= 0; i--)
	{
		if (hugeInt2[i] >hugeInt1[i])
			return true;
		else if (hugeInt2[i] < hugeInt1[i])
			return false;
	}
	return false;
}

bool lessEqual(int *hugeInt1, int *hugeInt2, int hugeInt1Size, int hugeInt2Size){
	if (hugeInt1Size < hugeInt2Size)
		return true;
	if (hugeInt1Size > hugeInt2Size)
		return false;
	for (int i = hugeInt1Size - 1; i >= 0; i--)
	{
		if (hugeInt1[i] < hugeInt2[i])
			return true;
		else if (hugeInt1[i] > hugeInt2[i])
			return false;
	}
	return true;
}