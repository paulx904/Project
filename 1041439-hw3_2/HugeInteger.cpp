// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a HugeInteger with size 0
HugeInteger::HugeInteger()
: integer()
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
: integer(n)
{
} // end HugeInteger constructor

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger(const HugeInteger &integerToCopy)
: integer(integerToCopy.integer)
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign(const HugeInteger &right)
{
	if (&right != this) // avoid self-assignment
		integer.assign(right.integer);

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal(const HugeInteger &right) const
{
	return (integer.equal(right.integer));
} // end function equal

// function that tests if two HugeIntegers are not equal
bool HugeInteger::notEqual(const HugeInteger &right) const
{
	return (integer.notEqual(right.integer));
} // end function notEqual

bool HugeInteger::less(const HugeInteger &op2)const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	if (op2Size > size)
		return true;
	if (size > op2Size)
		return false;
	Vector::iterator it1 = integer.end();
	Vector::iterator it2 = op2.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) > (*it1))
			return true;
		else if ((*it2) < (*it1))
			return false;
	}
	return false;
}

bool HugeInteger::lessEqual(const HugeInteger &op2)const
{
	if (equal(op2) || less(op2))
		return true;
	else
		return false;
}

bool HugeInteger::greater(const HugeInteger &op2)const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();

	if (size > op2Size)
		return true;
	if (size < op2Size)
		return false;
	Vector::iterator it1 = integer.end();
	Vector::iterator it2 = op2.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) < (*it1))
			return true;
		else if ((*it2) > (*it1))
			return false;
	}
	return false;
}

bool HugeInteger::greaterEqual(const HugeInteger &op2)const
{
	if (equal(op2) || greater(op2))
		return true;
	else
		return false;
}

HugeInteger HugeInteger::add(const HugeInteger &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int sumSize = (size >= op2Size) ? size + 1 : op2Size + 1;
	HugeInteger sum(sumSize);
	Vector::iterator it1 = integer.begin();
	Vector::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;
	Vector::iterator it2 = op2.integer.begin();
	it3 = sum.integer.begin();
	for (; it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;
	it3 = sum.integer.begin();
	Vector::iterator it4 = it3;
	for (++it4; it4 != sum.integer.end(); ++it3, ++it4)
	if (*it3 > 9)
	{
		(*it3) -= 10;
		(*it4)++;
	}
	if (*it3 == 0)
		sum.integer.resize(sumSize - 1);
	return sum;
}// convert a string of decimal digits into a HugeInteger

HugeInteger HugeInteger::subtract(const HugeInteger &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int differenceSize = (size >= op2Size) ? size : op2Size;
	HugeInteger difference(differenceSize);
	Vector::iterator it1 = integer.begin();
	Vector::iterator it2 = op2.integer.begin();
	Vector::iterator it3 = difference.integer.begin();
	if (equal(op2)){
		differenceSize = 1;
		*it3 = 0;
		difference.integer.resize(differenceSize);
	}
	else{
		if (size >= op2Size)
		{
			for (; it2 != op2.integer.end(); it1++, it2++, it3++)
				*it3 = (*it1) - (*it2);
			for (; it1 != integer.end(); it1++, it3++)
				(*it3) = (*it1);
		}
		else
		{
			for (; it1 != integer.end(); it1++, it2++, it3++)
				*it3 = (*it2) - (*it1);
			for (; it2 != op2.integer.end(); it2++, it3++)
				(*it3) = (*it2);
		}

		Vector::iterator it4 = it3 = difference.integer.begin();
		for (++it4; it4 != difference.integer.end(); ++it3, ++it4)
		if (*it3 < 0)
		{
			(*it3) += 10;
			(*it4)--;
		}
		for (; *it3 == 0; it3--)
			differenceSize--;
		difference.integer.resize(differenceSize);

	}

	return difference;

}

HugeInteger HugeInteger::multiply(const HugeInteger &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int productSize = size + op2Size;
	HugeInteger product(productSize);
	Vector::iterator it1 = integer.begin();
	Vector::iterator it2 = op2.integer.begin();
	Vector::iterator it3 = product.integer.begin();
	if (isZero() || op2.isZero()){
		productSize = 1;
		*it3 = 0;
		product.integer.resize(productSize);
	}
	else{
		int i = 0;
		for (; it2 != op2.integer.end(); ++it2){
			it3 = product.integer.begin() + i;
			i++;
			for (; it1 != integer.end(); ++it1, ++it3){

				(*it3) += (*it1) * (*it2);

			}
			it3 = product.integer.begin();
			it1 = integer.begin();
		}
		Vector::iterator it4 = it3 = product.integer.begin();
		for (++it4; it4 != product.integer.end(); ++it4, ++it3){
			if (*it3 >= 10){
				(*it4) += (*it3) / 10;
				(*it3) %= 10;
			}
		}
		while (*it3 == 0){
			productSize--;
			it3--;
		}
		product.integer.resize(productSize);
	}
	return product;
}

HugeInteger HugeInteger::divide(const HugeInteger &op2) const
{
	if (less(op2)){
		unsigned int quotientSize =  1;
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

	if (less(buffer))
	{
		buffer.divideByTen();
		quotient.integer.resize(integer.getSize() - op2.integer.getSize());
	}

	for (unsigned int i = 0; i < integer.getSize(); i++)
		*(itr + i) = *(it1 + i);

	for (it3 = quotient.integer.end() - 1; it3 != quotient.integer.begin() - 1; it3--)
	{
		while (buffer.lessEqual(remainder))
		{
			remainder.assign(remainder.subtract(buffer));
			*it3 = *it3 + 1;
			itr = remainder.integer.end() - 1;
			while (*itr == 0 && remainder.integer.getSize() > 1)
			{
				remainder.integer.resize(remainder.integer.getSize() - 1);
				itr = remainder.integer.end() - 1;
			}
		}

		if (buffer.greater(remainder))
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

HugeInteger HugeInteger::modulus(const HugeInteger &op2) const
{
	if (less(op2)){
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

	if (less(buffer))
	{
		buffer.divideByTen();
		quotient.integer.resize(integer.getSize() - op2.integer.getSize());
	}

	for (unsigned int i = 0; i < integer.getSize(); i++)
		*(itr + i) = *(it1 + i);

	for (it3 = quotient.integer.end() - 1; it3 != quotient.integer.begin() - 1; it3--)
	{
		while (buffer.lessEqual(remainder))
		{
			remainder.assign(remainder.subtract(buffer));
			*it3 = *it3 + 1;
			itr = remainder.integer.end() - 1;
			while (*itr == 0 && remainder.integer.getSize() > 1)
			{
				remainder.integer.resize(remainder.integer.getSize() - 1);
				itr = remainder.integer.end() - 1;
			}
		}

		if (buffer.greater(remainder))
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
	for (Vector::iterator it = integer.begin(); it != integer.end(); ++it)
	if (*it != 0)
		return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
	Vector::iterator it = integer.begin();
	Vector::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		*it = *it2;
	integer.resize(integer.getSize() - 1);
}

// overloaded output operator
void HugeInteger::output()
{
	if (integer.getSize() == 0)
		cout << 0;
	else
	{
		Vector::reverse_iterator it = integer.rbegin();
		for (; it != integer.rend(); --it)
			cout << *it;
	}
} // end function output

