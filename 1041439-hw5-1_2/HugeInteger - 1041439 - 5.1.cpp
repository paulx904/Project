// Member-function definitions for class template HugeInteger

using namespace std;
#include "HugeInteger.h" // include definition of class template HugeInteger
#include "Vector - 1041439 - 5.cpp" // include member-function definitions for class template Vector 

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

// function that tests if two HugeIntegers are not equal
template< typename T >
bool HugeInteger< T >::operator!=(const HugeInteger< T > &right) const
{
	return (integer != right.integer);
} // end function operator!=

template< typename T >
bool HugeInteger< T >::operator<(const HugeInteger< T > &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();
	if (rightSize > size)
		return true;
	if (size > rightSize)
		return false;
	Vector < T >::iterator it1 = integer.end();
	Vector < T >::iterator it2 = right.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) > (*it1))
			return true;
		else if ((*it2) < (*it1))
			return false;
	}
	return false;
}

template< typename T >
bool HugeInteger< T >::operator>(const HugeInteger< T > &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();

	if (size > rightSize)
		return true;
	if (size < rightSize)
		return false;
	Vector < T >::iterator it1 = integer.end();
	Vector < T >::iterator it2 = right.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) < (*it1))
			return true;
		else if ((*it2) > (*it1))
			return false;
	}
	return false;
}

template< typename T >
bool HugeInteger< T >::operator<=(const HugeInteger< T > &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();
	if (rightSize > size)
		return true;
	if (size > rightSize)
		return false;
	Vector < T >::iterator it1 = integer.end();
	Vector < T >::iterator it2 = right.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) > (*it1))
			return true;
		else if ((*it2) < (*it1))
			return false;
	}
	return true;
}

template< typename T >
bool HugeInteger< T >::operator>=(const HugeInteger< T > &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();

	if (size > rightSize)
		return true;
	if (size < rightSize)
		return false;
	Vector < T >::iterator it1 = integer.end();
	Vector < T >::iterator it2 = right.integer.end();
	for (--it1, --it2; it1 >= integer.begin(); --it1, --it2)
	{
		if ((*it2) < (*it1))
			return true;
		else if ((*it2) > (*it1))
			return false;
	}
	return true;
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(const HugeInteger< T > &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int sumSize = (size >= op2Size) ? size + 1 : op2Size + 1;

	HugeInteger< T > sum(sumSize);

	Vector< T >::iterator it1 = integer.begin();
	Vector< T >::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	Vector< T >::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.integer.begin();
	Vector< T >::iterator it4 = it3;
	for (++it4; it4 != sum.integer.end(); ++it3, ++it4)
	if (*it3 > 9)
	{
		(*it3) -= 10;
		(*it4)++;
	}

	if (*it3 == 0)
		sum.integer.resize(sumSize - 1);

	return sum;
} // end function operator+

template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(const HugeInteger< T > &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int differenceSize = (size > op2Size) ? size : op2Size;

	HugeInteger< T > difference(differenceSize);

	Vector < T >::iterator it1 = integer.begin();
	Vector < T >::iterator it2 = op2.integer.begin();
	Vector < T >::iterator it3 = difference.integer.begin();
	
		for (; it1 != integer.end(); ++it1, ++it3)
			*it3 = *it1;

		it3 = difference.integer.begin();

		for (; it3 != difference.integer.end() && it2 != op2.integer.end(); ++it2, ++it3){
			if (*it3 < *it2){
				*it3 = *it3 + 10 - *it2;
				++it3;
				int temp = 0;
				for (; *it3 < 1; temp++){
					*it3 = 9;
					++it3;
				}
				*it3 -= 1;
				it3 = it3 - temp - 1;
			}
			else
				*it3 = *it3 - *it2;
		}
		it3 = difference.integer.rbegin();

	while (*it3 == 0){
		differenceSize--;
		difference.integer.resize(differenceSize);
		it3--; 
	}
	return difference;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(const HugeInteger< T > &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int productSize = size + op2Size;

	HugeInteger < T > product(productSize);

	Vector < T >::iterator it1 = integer.begin();
	Vector < T >::iterator it2 = op2.integer.begin();
	Vector < T >::iterator it3 = product.integer.begin();
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
		Vector < T >::iterator it4 = it3 = product.integer.begin();
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

template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(const HugeInteger< T > &op2) const
{
	if (*this < op2){
		unsigned int quotientSize = 1;
		HugeInteger< T > quotient(quotientSize);
		Vector < T >::iterator it3 = quotient.integer.begin();
		*it3 = 0;

		return quotient;
	}


	unsigned int quotientSize = integer.getSize() - op2.integer.getSize() + 1;
	HugeInteger< T > quotient(quotientSize);

	int n = integer.getSize() - op2.integer.getSize();
	HugeInteger< T > buffer(integer.getSize());
	unsigned int remainderSize = integer.getSize();
	HugeInteger< T > remainder(remainderSize);
	Vector< T >::iterator it1 = integer.begin();
	Vector< T >::iterator it2 = op2.integer.begin();
	Vector< T >::iterator it3 = quotient.integer.begin();
	Vector< T >::iterator itb = buffer.integer.begin();
	Vector< T >::iterator itr = remainder.integer.begin();


	for (unsigned int i = 0; i < op2.integer.getSize(); i++)
		*(itb + i + n) = *(it2 + i);


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

template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(const HugeInteger< T > &op2) const
{
	if (*this < op2){
		unsigned int remainderSize = integer.getSize();
		HugeInteger< T > remainder(remainderSize);
		Vector< T >::iterator it1 = integer.begin();
		Vector< T >::iterator itr = remainder.integer.begin();

		for (unsigned int i = 0; i < integer.getSize(); i++){
			*(itr + i) = *(it1 + i);
		}

		return remainder;
	}

	unsigned int quotientSize = integer.getSize() - op2.integer.getSize() + 1;
	HugeInteger< T > quotient(quotientSize);

	int n = integer.getSize() - op2.integer.getSize();
	HugeInteger< T > buffer(integer.getSize());
	unsigned int remainderSize = integer.getSize();
	HugeInteger< T > remainder(remainderSize);
	Vector< T >::iterator it1 = integer.begin();
	Vector< T >::iterator it2 = op2.integer.begin();
	Vector< T >::iterator it3 = quotient.integer.begin();
	Vector< T >::iterator itb = buffer.integer.begin();
	Vector< T >::iterator itr = remainder.integer.begin();

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

template < typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{
	
	HugeInteger< T > prefixone(1);
	Vector < T >::iterator it = prefixone.integer.begin();
	*it = 1;
	*this = (*this + prefixone);

	return *this;
}

template < typename T >
HugeInteger< T > HugeInteger< T >::operator++(int)
{
	HugeInteger< T > postfixone(1);
	Vector < T >::iterator it = postfixone.integer.begin();
	*it = 1;
	*this = (*this + postfixone);
	return (*this - postfixone);
}

// convert a string of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert(Vector< T > vector)
{
	// vector[ 0 ] is the most significant digit ( could be 0 )
	// vector[ vector.end() - 1 ] is the least significant digit

	unsigned int size = vector.getSize();
	Vector< T >::iterator msd = vector.begin();
	for (; msd != vector.end(); ++msd, --size) // find the position of the most significant nonzero digit
	if (*msd != 0)
		break;

	// msd points to the most significant nonzero digit in vector

	if (size == 0) // all digits of vector are 0
		return;

	integer.resize(size);
	Vector< T >::iterator it1 = msd;
	Vector< T >::reverse_iterator it2 = integer.rbegin();
	for (; it1 != vector.end(); ++it1, --it2)
		*it2 = *it1;

	// integer.begin() points to the least significant digit
	// integer.end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
	for (Vector< T >::iterator it = integer.begin(); it != integer.end(); ++it)
	if (*it != 0)
		return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	Vector< T >::iterator it = integer.begin();
	Vector< T >::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		*it = *it2;
	integer.resize(integer.getSize() - 1);
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream &operator<<(ostream &output, HugeInteger< T > &hugeInteger)
{
	if (hugeInteger.integer.getSize() == 0)
		output << 0;
	else
	{
		Vector< T >::reverse_iterator it = hugeInteger.integer.rbegin();
		for (; it != hugeInteger.integer.rend(); --it)
			output << *it;
	}

	return output; // enables cout << x << y;
}