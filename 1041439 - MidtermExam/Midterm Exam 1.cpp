// HugeInteger test program.
#include <fstream>
#include "HugeInteger - 1041439.cpp" // include member-function definitions for class template HugeInteger 

int enterChoice1();

template< typename T >
void testHugeIntegerOperators(HugeInteger< T > n1, HugeInteger< T > n2);

int enterChoice2();

template< typename T >
void loadTwoHugeIntegers(HugeInteger< T > &n1, HugeInteger< T > &n2);

int enterChoice3();

template< typename T >
void testAdd(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testSubtract(HugeInteger< T > n1, HugeInteger< T > n2);

template< typename T >
void testMultiply(HugeInteger< T > n1, HugeInteger< T > n2);

int main()
{
	HugeInteger< int > n1;
	HugeInteger< int > n2;
	HugeInteger< unsigned int > n3;
	HugeInteger< unsigned int > n4;
	HugeInteger< unsigned short int > n5;
	HugeInteger< unsigned short int > n6;

	int choice = enterChoice1();

	switch (choice)
	{
	case 1:
		testHugeIntegerOperators(n1, n2);
		break;
	case 2:
		testHugeIntegerOperators(n3, n4);
		break;
	case 3:
		testHugeIntegerOperators(n5, n6);
		break;
	default:
		cout << "Program should never get here!";
	}

	system("pause");
}

int enterChoice1()
{
	cout << "Enter your choice\n"
		<< " 1 - test HugeInteger< int >\n"
		<< " 2 - test HugeInteger< unsigned int >\n"
		<< " 3 - test HugeInteger< unsigned short int >\n";

	int menuChoice;
	do {
		cout << "? ";
		cin >> menuChoice;
	} while ((menuChoice < 1) || (menuChoice > 3));
	cout << endl;

	return menuChoice;
}

template< typename T >
void testHugeIntegerOperators(HugeInteger< T > n1, HugeInteger< T > n2)
{
	loadTwoHugeIntegers(n1, n2);

	int choice = enterChoice2();

	switch (choice)
	{
	case 1:
		testAdd(n1, n2);
		break;
	case 2:
		testSubtract(n1, n2);
		break;
	case 3:
		testMultiply(n1, n2);
		break;
	default:
		cout << "Program should never get here!";
	}

	cout << endl << endl;
}

int enterChoice2()
{
	cout << "Enter your choice\n"
		<< " 1 - test add\n"
		<< " 2 - test subtract\n"
		<< " 3 - test multiply\n";

	int menuChoice;
	do {
		cout << "? ";
		cin >> menuChoice;
	} while ((menuChoice < 1) || (menuChoice > 3));
	cout << endl;

	return menuChoice;
}

template< typename T >
void loadTwoHugeIntegers(HugeInteger< T > &n1, HugeInteger< T > &n2)
{
	char fileName[13][20] = { "0", "hugeIntegers1.txt", "hugeIntegers2.txt",
		"hugeIntegers3.txt", "hugeIntegers4.txt",
		"hugeIntegers5.txt", "hugeIntegers6.txt",
		"hugeIntegers7.txt", "hugeIntegers8.txt",
		"hugeIntegers9.txt", "hugeIntegers10.txt",
		"hugeIntegers11.txt", "hugeIntegers12.txt" };
	int choice = enterChoice3();

	// ifstream constructor opens the file
	ifstream inFile(fileName[choice], ios::in);

	// exit program if ifstream could not open file
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	char digit;
	Vector< T > vector1, vector2;

	while ((digit = inFile.get()) != '\n')
	if (digit != ' ')
		vector1.insert(vector1.begin(), digit - '0');
	// n1.integer.begin() points to the least significant digit (i.e., the rightmost digit )

	while ((digit = inFile.get()) != '\n')
	if (digit != ' ')
		vector2.insert(vector2.begin(), digit - '0');
	// n2.integer.begin() points to the least significant digit (i.e., the rightmost digit )

	n1.convert(vector1);
	n2.convert(vector2);

	inFile.close();
}

int enterChoice3()
{
	cout << "Enter your choice\n"
		<< " 1 - hugeIntegers1.txt\n"
		<< " 2 - hugeIntegers2.txt\n"
		<< " 3 - hugeIntegers3.txt\n"
		<< " 4 - hugeIntegers4.txt\n"
		<< " 5 - hugeIntegers5.txt\n"
		<< " 6 - hugeIntegers6.txt\n"
		<< " 7 - hugeIntegers7.txt\n"
		<< " 8 - hugeIntegers8.txt\n"
		<< " 9 - hugeIntegers9.txt\n"
		<< "10 - hugeIntegers10.txt\n"
		<< "11 - hugeIntegers11.txt\n"
		<< "12 - hugeIntegers12.txt\n";

	int menuChoice;
	do {
		cout << "? ";
		cin >> menuChoice;
	} while ((menuChoice < 1) || (menuChoice > 12));
	cout << endl;

	return menuChoice;
} // end function enterChoice2

template< typename T >
void testAdd(HugeInteger< T > n1, HugeInteger< T > n2)
{
	cout << "n1 = " << n1 << endl;
	cout << "n2 = " << n2 << endl;
	n1 += n2;
	cout << "After the execution of n1 += n2,\n";
	cout << "n1 = " << n1;
}

template< typename T >
void testSubtract(HugeInteger< T > n1, HugeInteger< T > n2)
{
	cout << "n1 = " << n1 << endl;
	cout << "n2 = " << n2 << endl;

	if (n1 >= n2)
	{
		n1 -= n2;
		cout << "After the execution of n1 -= n2,\n";
		cout << "n1 = " << n1;
	}
	else
		cout << "Cannot perform n1 -= n2";
}

template< typename T >
void testMultiply(HugeInteger< T > n1, HugeInteger< T > n2)
{
	cout << "n1 = " << n1 << endl;
	cout << "n2 = " << n2 << endl;
	n1 *= n2;
	cout << "After the execution of n1 *= n2,\n";
	cout << "n1 = " << n1;
}