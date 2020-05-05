// Perform huge integer operations.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// enable user to input menu choice
int enterChoice();

// enable user to input two positive huge integers from user
void inputTwoHugeInts(int hugeInt1[], int hugeInt2[], int &hugeInt1Size, int &hugeInt2Size);

// Returns true if and only if hugeInt1 == hugeInt2
bool equal(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size){
	for (int i = 0; i < hugeInt1Size; i++){
		if (hugeInt1[i] == hugeInt2[i]){
			return true;
		}
		else{
			return false;
		}
	}
}

// Returns true if and only if hugeInt1 != hugeInt2
bool notEqual(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size){
	for (int i = 0; i < hugeInt1Size; i++){
		if (hugeInt1[i] == hugeInt2[i]){
			return false;
		}
		else{
			return true;
		}
	}
}

// Returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size){

	
	if (hugeInt1Size < hugeInt2Size){
		return true;
	}
	if (hugeInt1Size > hugeInt2Size){
		return false;
	}
	for (int i = hugeInt1Size - 1; i >= 0; i--){
		if (hugeInt2[i] > hugeInt1[i]){
			return true;
		}
		else  {
			return false;
		}
	}
}

// Returns true if and only if hugeInt1 > hugeInt2
bool greater(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size){
	if (hugeInt1Size < hugeInt2Size){
		return false;
	}
	if (hugeInt1Size > hugeInt2Size){
		return true;
	}
	for (int i = hugeInt1Size - 1; i >= 0; i--){
		if (hugeInt2[i] < hugeInt1[i]){
			return true;
		}
		else {
			return false;
		}
	}

}

// Returns true if and only if hugeInt1 <= hugeInt2
bool lessEqual(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size){
	if (equal(hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size) || less(hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size))
		return true;
	else
		return false;
}

// Returns true if and only if hugeInt1 >= hugeInt2
bool greaterEqual(int hugeInt1[], int hugeInt2[], int hugeInt1Size, int hugeInt2Size){
	if (equal(hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size) || greater(hugeInt1, hugeInt2, hugeInt1Size, hugeInt2Size))
		return true;
	else
		return false;
}

// sum = addend + adder
void addition(int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize)
{
		sumSize = (addendSize >= adderSize) ? addendSize + 1 : adderSize + 1;
		for (int i = 0; i < sumSize; i++)
			sum[i] = 0;
		if (addendSize <= adderSize)
		{
			for (int i = 0; i < addendSize; i++)
				sum[i] = addend[i] + adder[i];
			for (int i = addendSize; i < adderSize; i++)
				sum[i] = adder[i];
		}
		else
		{
			for (int i = 0; i < adderSize; i++)
				sum[i] = addend[i] + adder[i];
			for (int i = adderSize; i < addendSize; i++)
				sum[i] = addend[i];
		}
		for (int i = 0; i < sumSize - 1; i++)
		if (sum[i]>=10)
		{
			sum[i] -= 10;
			sum[i + 1]+=1;
		}
		if (sum[sumSize - 1] == 0)
			sumSize-=1;
}

// difference = minuend - subtrahend
void subtraction(int minuend[], int subtrahend[], int difference[],
	int minuendSize, int subtrahendSize, int &differenceSize){

	differenceSize = (minuendSize >= subtrahendSize) ? minuendSize + 1 : subtrahendSize + 1;
	for (int i = 0; i < differenceSize; i++)
		difference[i] = 0;
	if (minuendSize <= subtrahendSize)
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

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],int multiplicandSize, int multiplierSize, int &productSize){
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

	int choice = enterChoice();

	switch (choice)
	{
	case 1:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (equal(n1, n2, n1Size, n2Size))
			printRelational(n1, n2, n1Size, n2Size, "==");
		break;
	case 2:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (notEqual(n1, n2, n1Size, n2Size))
			printRelational(n1, n2, n1Size, n2Size, "!=");
		break;
	case 3:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (less(n1, n2, n1Size, n2Size))
			printRelational(n1, n2, n1Size, n2Size, "<");
		break;
	case 4:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (greater(n1, n2, n1Size, n2Size))
			printRelational(n1, n2, n1Size, n2Size, ">");
		break;
	case 5:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (lessEqual(n1, n2, n1Size, n2Size))
			printRelational(n1, n2, n1Size, n2Size, "<=");
		break;
	case 6:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (greaterEqual(n1, n2, n1Size, n2Size))
			printRelational(n1, n2, n1Size, n2Size, ">=");
		break;
	case 7:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		addition(n1, n2, n3, n1Size, n2Size, n3Size);
		printArithmetic(n1, n2, n3, '+', n1Size, n2Size, n3Size);
		break;
	case 8:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		if (greaterEqual(n1, n2, n1Size, n2Size))
		{
			subtraction(n1, n2, n3, n1Size, n2Size, n3Size);
			printArithmetic(n1, n2, n3, '-', n1Size, n2Size, n3Size);
		}
		break;
	case 9:
		inputTwoHugeInts(n1, n2, n1Size, n2Size);
		multiplication(n1, n2, n3, n1Size, n2Size, n3Size);
		printArithmetic(n1, n2, n3, '*', n1Size, n2Size, n3Size);
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
		<< " 1 - test equal\n"
		<< " 2 - test notEqual\n"
		<< " 3 - test less\n"
		<< " 4 - test greater\n"
		<< " 5 - test lessEqual\n"
		<< " 6 - test greaterEqual\n"
		<< " 7 - test add\n"
		<< " 8 - test subtract\n"
		<< " 9 - test multiply\n";

	int menuChoice;
	do {
		cout << "? ";
		cin >> menuChoice; // input menu selection from user
	} while ((menuChoice < 1) || (menuChoice > 9));
	cout << endl;

	return menuChoice;
} // end function enterChoiceint 



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