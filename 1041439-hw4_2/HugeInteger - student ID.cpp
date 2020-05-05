// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor
HugeInteger::HugeInteger()
: integer()
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
: integer(n)
{
}

// copy constructor
HugeInteger::HugeInteger(const HugeInteger &integerToCopy)
: integer(integerToCopy.integer)
{
}

// destructor
HugeInteger::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::operator=(const HugeInteger &right)
{
	if (&right != this) // avoid self-assignment
		integer = right.integer;

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==(const HugeInteger &right) const
{
	return (integer == right.integer);
} // end function operator==

// function that tests if two HugeIntegers are not equal
bool HugeInteger::operator!=(const HugeInteger &right) const
{
	return (integer != right.integer);
} // end function operator!=

bool HugeInteger::operator<(const HugeInteger &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();
	if (rightSize > size)
		return true;
	if (size > rightSize)
		return false;
	Vector::iterator it1 = integer.end();
	Vector::iterator it2 = right.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) > (*it1))
			return true;
		else if ((*it2) < (*it1))
			return false;
	}
	return false;
}

bool HugeInteger::operator>(const HugeInteger &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();

	if (size > rightSize)
		return true;
	if (size < rightSize)
		return false;
	Vector::iterator it1 = integer.end();
	Vector::iterator it2 = right.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) < (*it1))
			return true;
		else if ((*it2) > (*it1))
			return false;
	}
	return false;
}

bool HugeInteger::operator<=(const HugeInteger &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();
	if (rightSize > size)
		return true;
	if (size > rightSize)
		return false;
	Vector::iterator it1 = integer.end();
	Vector::iterator it2 = right.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) > (*it1))
			return true;
		else if ((*it2) < (*it1))
			return false;
	}
	return true;
	
	
}

bool HugeInteger::operator>=(const HugeInteger &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();

	if (size > rightSize)
		return true;
	if (size < rightSize)
		return false;
	Vector::iterator it1 = integer.end();
	Vector::iterator it2 = right.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) < (*it1))
			return true;
		else if ((*it2) > (*it1))
			return false;
	}
	return true;
}
// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+(const HugeInteger &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int sumSize = (size >= op2Size) ? size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);

	for (unsigned int i = 0; i < size; i++)
		sum.integer[i] = integer[i];

	for (unsigned int i = 0; i < op2Size; i++)
		sum.integer[i] += op2.integer[i];

	for (unsigned int i = 0; i < sumSize - 1; i++)
	if (sum.integer[i] > 9)
	{
		sum.integer[i] -= 10;
		sum.integer[i + 1]++;
	}

	if (sum.integer[sumSize - 1] == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
} // end function operator+

HugeInteger HugeInteger::operator-(const HugeInteger &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int differenceSize = (size >= op2Size) ? size : op2Size;
	HugeInteger difference(differenceSize);

	if (*this == op2){
		difference.integer[0] = 0;
		difference.integer.resize(1);
	}
	else{
		if (*this > op2)
		{
			int temp = 0;

			for (unsigned int i = 0; i < size; i++)
				difference.integer[i] = integer[i];
			for (unsigned int i = 0; i < op2Size; i++){
				temp = i;
				if (difference.integer[i] < op2.integer[i]){
					difference.integer[i] += 10;
					for (;; i++){
						if (difference.integer[i + 1] > 0){
							difference.integer[i + 1]--;
							i = temp;
							break;
						}
						else
							difference.integer[i + 1] = 9;
					}


					difference.integer[i] -= op2.integer[i];
				}
				else
					difference.integer[i] -= op2.integer[i];
			}
		}
		else
		{
			int temp = 0;

			for (unsigned int i = 0; i < op2Size; i++)
				difference.integer[i] = op2.integer[i];
			for (unsigned int i = 0; i < size; i++){
				temp = i;
				if (difference.integer[i] < integer[i]){
					difference.integer[i] += 10;
					for (;; i++){
						if (difference.integer[i + 1] > 0){
							difference.integer[i + 1]--;
							i = temp;
							break;
						}
						else
							difference.integer[i + 1] = 9;
					}


					difference.integer[i] -= integer[i];
				}
				else
					difference.integer[i] -= integer[i];
			}
		}
	}
	return difference;
}

HugeInteger HugeInteger::operator*(const HugeInteger &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int productSize = size + op2Size;
	HugeInteger product(productSize);
	if (isZero() || op2.isZero()){
		productSize = 1;
		product.integer[0] = 0;
		product.integer.resize(1);
	}
	else{
		for (unsigned int i = 0; i < size; i++){
			for (unsigned int j = 0; j < op2Size; j++){
				product.integer[i + j] += integer[i] * op2.integer[j];
			}
		}
		for (unsigned int i = 0; i < productSize; i++){
			if (product.integer[i] >= 10){
				product.integer[i + 1] += product.integer[i] / 10;
				product.integer[i] %= 10;
			}
		}
		while (product.integer[productSize - 1] == 0){
			productSize--;
			product.integer.resize(productSize);
		}
	}
	return product;
}

HugeInteger HugeInteger::operator/(const HugeInteger &op2) const
{
	if (*this < op2){
		unsigned int quotientSize = 1;
		HugeInteger quotient(quotientSize);
		Vector::iterator it3 = quotient.integer.begin();
		*it3 = 0;

		return quotient;
	}


	unsigned int quotientSize = integer.getSize() - op2.integer.getSize() + 1;
	HugeInteger quotient(quotientSize);

	int n = integer.getSize() - op2.integer.getSize();
	HugeInteger buffer(integer.getSize());
	unsigned int remainderSize = integer.getSize();
	HugeInteger remainder(remainderSize);
	Vector::iterator it1 = integer.begin();
	Vector::iterator it2 = op2.integer.begin();
	Vector::iterator it3 = quotient.integer.begin();
	Vector::iterator itb = buffer.integer.begin();
	Vector::iterator itr = remainder.integer.begin();


	for (unsigned int i = 0; i < op2.integer.getSize(); i++)
	{
		*(itb + i + n) = *(it2 + i);
	}

	if (*this < buffer)
	{
		buffer.divideByTen();
		quotient.integer.resize(integer.getSize() - op2.integer.getSize());
	}

	for (unsigned int i = 0; i < integer.getSize(); i++)
		*(itr + i) = *(it1 + i);

	for (it3 = quotient.integer.end() - 1; it3 != quotient.integer.begin() - 1; it3--)
	{
		while (buffer <= remainder)
		{
			remainder = remainder - buffer;
			*it3 = *it3 + 1;
			itr = remainder.integer.end() - 1;
			while (*itr == 0 && remainder.integer.getSize() > 1)
			{
				remainder.integer.resize(remainder.integer.getSize() - 1);
				itr = remainder.integer.end() - 1;
			}
		}

		if (buffer > remainder)
			buffer.divideByTen();
	}

	itr = remainder.integer.end();

	while (*(itr - 1) == 0 && remainder.integer.getSize() > 1)
	{
		remainder.integer.resize(remainder.integer.getSize() - 1);
		itr = remainder.integer.end();
	}
	return quotient;
}

HugeInteger HugeInteger::operator%(const HugeInteger &op2) const
{
	if (*this < op2){
		unsigned int remainderSize = integer.getSize();
		HugeInteger remainder(remainderSize);
		Vector::iterator it1 = integer.begin();
		Vector::iterator itr = remainder.integer.begin();

		for (unsigned int i = 0; i < integer.getSize(); i++){
			*(itr + i) = *(it1 + i);
		}

		return remainder;
	}

	unsigned int quotientSize = integer.getSize() - op2.integer.getSize() + 1;
	HugeInteger quotient(quotientSize);

	int n = integer.getSize() - op2.integer.getSize();
	HugeInteger buffer(integer.getSize());
	unsigned int remainderSize = integer.getSize();
	HugeInteger remainder(remainderSize);
	Vector::iterator it1 = integer.begin();
	Vector::iterator it2 = op2.integer.begin();
	Vector::iterator it3 = quotient.integer.begin();
	Vector::iterator itb = buffer.integer.begin();
	Vector::iterator itr = remainder.integer.begin();

	for (unsigned int i = 0; i < op2.integer.getSize(); i++)
	{
		*(itb + i + n) = *(it2 + i);
	}

	if (*this < buffer)
	{
		buffer.divideByTen();
		quotient.integer.resize(integer.getSize() - op2.integer.getSize());
	}

	for (unsigned int i = 0; i < integer.getSize(); i++)
		*(itr + i) = *(it1 + i);

	for (it3 = quotient.integer.end() - 1; it3 != quotient.integer.begin() - 1; it3--)
	{
		while (buffer <= remainder)
		{
			remainder = remainder - buffer;
			*it3 = *it3 + 1;
			itr = remainder.integer.end() - 1;
			while (*itr == 0 && remainder.integer.getSize() > 1)
			{
				remainder.integer.resize(remainder.integer.getSize() - 1);
				itr = remainder.integer.end() - 1;
			}
		}

		if (buffer > remainder)
			buffer.divideByTen();
	}

	itr = remainder.integer.end();

	while (*(itr - 1) == 0 && remainder.integer.getSize() > 1)
	{
		remainder.integer.resize(remainder.integer.getSize() - 1);
		itr = remainder.integer.end();
	}
	return remainder;
}
	
HugeInteger &HugeInteger::operator++()
{
	HugeInteger prefixone(1);
	prefixone.integer[0] = 1;
	*this = (*this + prefixone);

	return *this;
}

HugeInteger HugeInteger::operator++(int)
{
	HugeInteger postfixone(1);
	postfixone.integer[0] = 1;
	*this = (*this + postfixone);
	return (*this - postfixone);
}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert(Vector vector)
{
	// vector[ 0 ] is the most significant digit ( could be 0 )
	// vector[ vector.end() - 1 ] is the least significant digit

	Vector::iterator msd = vector.begin();
	for (; msd != vector.end(); ++msd) // find the position of the most significant nonzero digit
	if (*msd != 0)
		break;

	// msd points to the most significant nonzero digit in vector

	if (msd == vector.end()) // all digits of vector are 0
		return;

	integer.resize(vector.end() - msd);
	Vector::iterator it1 = msd;
	Vector::reverse_iterator it2 = integer.rbegin();
	for (; it1 != vector.end(); ++it1, --it2)
		*it2 = *it1;

	// integer.begin() points to the least significant digit
	// integer.end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const
{
	for (unsigned int i = 0; i < integer.getSize(); i++)
	if (integer[i] != 0)
		return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
	unsigned int size = integer.getSize();
	if (size > 0)
	{
		for (unsigned int i = 1; i < size; i++)
			integer[i - 1] = integer[i];
		integer.resize(size - 1);
	}
}

// overloaded output operator for class HugeInteger
ostream &operator<<(ostream &output, HugeInteger &hugeInteger)
{
	unsigned int size = hugeInteger.integer.getSize();
	if (size == 0)
		output << 0;
	else
	for (int i = size - 1; i >= 0; i--)
		output << hugeInteger.integer[i];

	return output; 
}