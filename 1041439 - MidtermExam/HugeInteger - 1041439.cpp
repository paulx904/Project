// Member-function definitions for class template HugeInteger

#include <iomanip>
using namespace std;
#include "HugeInteger.h" // include definition of class template HugeInteger
#include "Vector - 1041439.cpp" // include member-function definitions for class template Vector 

// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger< T >::HugeInteger()
: integer()
{
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
: integer(n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger< T > &integerToCopy)
: integer(integerToCopy.integer)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=(const HugeInteger< T > &right)
{
	if (&right != this) // avoid self-assignment
		integer = right.integer;

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(const HugeInteger< T > &right) const
{
	return (integer == right.integer);
} // end function operator==

template< typename T >
bool HugeInteger< T >::operator<(const HugeInteger< T > &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();

	if (size < rightSize)
		return true;
	if (size > rightSize)
		return false;

	Vector< T >::iterator it1 = integer.end();
	Vector< T >::iterator it2 = right.integer.end();

	for (--it1, --it2; it1 != integer.end() && it2 != right.integer.end(); --it1, --it2){
		if (*it1 < *it2)
			return true;
		if (*it1 > *it2)
			return false;
	}
	return false;
}

// function that tests if one HugeInteger< T > is greater than or equal to another
template< typename T >
bool HugeInteger< T >::operator>=(const HugeInteger< T > &right) const
{
	return (!(*this < right));
}

template< typename T >
void HugeInteger< T >::reset()
{
	integer.resize(0);
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert(Vector< T > vector)
{
	// vector[ 0 ] is the least significant digit
	// vector[ vector.end() - 1 ] is the most significant digit ( could be 0 )

	unsigned int size = vector.getSize();
	Vector< T >::reverse_iterator it = vector.rbegin();
	for (; it != vector.rend(); --it, --size) // size -= the number of leading zeros
	if (*it != 0)
		break;

	if (size == 0) // all digits of vector are 0
		return;

	vector.resize(size);

	integer.resize(((size - 1) / 4) + 1);
	unsigned int power;
	unsigned int bigDigit;
	Vector< T >::iterator it1 = vector.begin();
	Vector< T >::iterator it2 = integer.begin();
	for (; it2 != integer.end(); ++it2)
	{
		power = 1;
		bigDigit = 0;
		for (unsigned int i = 0; i < 4 && it1 != vector.end(); ++i)
		{
			bigDigit += (*it1) * power;
			power *= 10;
			++it1;
		}
		*it2 = bigDigit;
	}

	// integer.begin() points to the least significant digit
	// integer.end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
	if (integer.getSize() == 0)
		return true;

	for (Vector< T >::iterator it = integer.begin(); it != integer.end(); ++it)
	if (*it != 0)
		return false;

	return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<(ostream &output, const HugeInteger< T > &hugeInteger)
{
	if (hugeInteger.integer.getSize() == 0)
		output << 0;
	else
	{
		Vector< T >::reverse_iterator it = hugeInteger.integer.rbegin();
		output << *it;
		for (--it; it != hugeInteger.integer.rend(); --it)
			output << ' ' << setw(4) << setfill('0') << *it;
	}

	return output; // enables cout << x << y;
} // end function operator<<

template< typename T >
void HugeInteger< T >::operator+=(const HugeInteger &op2)
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int sumSize = (size > op2Size) ? size + 1 : op2Size + 1;

	integer.resize(sumSize);

	Vector < T >::iterator it1 = integer.begin();
	Vector < T >::iterator it2 = op2.integer.begin();

	for (; it1 != integer.end() && it2 != op2.integer.end(); ++it1, ++it2)
		*it1 = *it1 + *it2;

	it1 = integer.begin();
	Vector < T >::iterator it3 = integer.begin() + 1;

	for (; it3 != integer.end(); ++it1, ++it3)
	if (*it1 > 9999){
		*it1 = *it1 - 10000;
		*it3 = *it3 + 1;
	}

	if (*it1 <= 0)
		integer.resize(sumSize - 1);


}

template< typename T >
void HugeInteger< T >::operator-=(const HugeInteger &op2)
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int differenceSize = (size > op2Size) ? size : op2Size;

	integer.resize(differenceSize);

	Vector < T >::iterator it1 = integer.begin();
	Vector < T >::iterator it2 = op2.integer.begin();


	for (; it1 != integer.end() && it2 != op2.integer.end(); ++it1, ++it2){
		if (*it1 < *it2){	//add	
			*it1 = *it1 + 10000 - *it2;		//add
			++it1;		//add    
			int temp = 0;		//add
			for (; *it1 < 1; temp++){		//add
				*it1 = 9999;		//add
				++it1;		//add
			}
			*it1 -= 1;		//add
			it1 = it1 - temp - 1;	//add
		}
		else
		*it1 = *it1 - *it2;
	}
	

	it1 = integer.begin();
	Vector < T >::iterator it3 = integer.begin() + 1;

	for (; it3 != integer.end(); ++it1, ++it3)
	if (*it1 < 0){
		*it1 = *it1 + 10000;
		*it3 = *it3 - 1;
	}

	while (*it1 == 0){
		differenceSize--;
		integer.resize(differenceSize);
		it1--;  //add
	}

}

template< typename T >
void HugeInteger< T >::operator*=(const HugeInteger &op2)
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int productSize = size + op2Size;

	HugeInteger< T > product(productSize);

	Vector < T >::iterator it1 = integer.begin();
	Vector < T >::iterator it2 = op2.integer.begin();
	Vector < T >::iterator it3 = product.integer.begin();

	int increment = 0;
	for (; it1 != integer.end(); ++it1){
		
		for (; it2 != op2.integer.end(); ++it3, ++it2)
			*it3 = *it3 + (*it1)*(*it2);
			
		increment++;
		it2 = op2.integer.begin();
		it3 = product.integer.begin() + increment;
	}

	it3 = product.integer.begin();
	Vector < T >::iterator it4 = product.integer.begin() + 1;

	for (; it4 != product.integer.end(); ++it3, ++it4){
		*it4 += (*it3 / 10000);//上下兩行交換
		*it3 %= 10000; //上下兩行交換
	}
	
	while (*it3 == 0){
		productSize--;
		product.integer.resize(productSize);
		it3--; //add
	}

	integer = product.integer;
}