//#include "list.h" // include definition of class template list 
//#include "vector.h" // include definition of class template vector 

#include <list> // include definition of class template list 
#include <vector> // include definition of class template vector
using namespace std;

// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

template< typename T >
class HugeInteger : public list< T >
{
	template< typename T >
	friend std::ostream &operator<<(std::ostream &, HugeInteger< T > &);
public:
	HugeInteger(); // default constructor; construct a HugeInteger with size 0

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger &integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger &operator=(const HugeInteger &right); // assignment operator

	bool operator<(HugeInteger &right);  // less than
	bool operator>(HugeInteger &right);  // greater than
	bool operator<=(HugeInteger &right); // less than or equal to
	bool operator>=(HugeInteger &right); // greater than or equal to

	// addition operator; HugeInteger + HugeInteger
	HugeInteger operator+(HugeInteger &op2);

	// subtraction operator; HugeInteger - HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	HugeInteger operator-(HugeInteger &op2);

	// multiplication operator; HugeInteger * HugeInteger
	HugeInteger operator*(HugeInteger &op2);

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator/(HugeInteger &op2);

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator%(HugeInteger &op2);

	// convert a vector of decimal digits into a HugeInteger
	void convert(vector< unsigned int > intVector);

	bool isZero(); // return true if and only if all digits are zero

private:
	// constructor; construct a zero HugeInteger with size n
	HugeInteger(unsigned int n);

	void divideByTen(); // divides a HugeInteger by 10
}; // end class template HugeInteger

#endif


// default constructor; construct a HugeInteger with size 0
template< typename T >
HugeInteger< T >::HugeInteger()
: list()
{
}

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
: list(n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger< T > &integerToCopy)
: list(integerToCopy)
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
	list< T >::operator=(right);

	return *this; // enables x = y = z, for example
}

template< typename T >
bool HugeInteger< T >::operator<(HugeInteger< T > &right)
{
	unsigned int op1Size = size();
	unsigned int rightSize = right.size();
	if (rightSize > op1Size)
		return true;
	if (op1Size > rightSize)
		return false;

	reverse_iterator it1 = rbegin();
	reverse_iterator it2 = right.rbegin();

	for (; it1 != rend(); ++it1, ++it2)
	{
		if ((*it2) > (*it1))
			return true;
		else if ((*it2) < (*it1))
			return false;
	}
	return false;
}

// function to test if one HugeInteger< T > is greater than another
template< typename T >
bool HugeInteger< T >::operator>(HugeInteger< T > &right)
{
	return (right < *this);
}

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger< T > &right)
{
	return (*this == right || *this < right);
}

// function that tests if one HugeInteger< T > is greater than or equal to another
template< typename T >
bool HugeInteger< T >::operator>=(HugeInteger< T > &right)
{
	return (!(*this < right));
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(HugeInteger< T > &op2)
{
	unsigned int op1Size = size();
	unsigned int op2Size = op2.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger< T > sum(*this);
	sum.resize(sumSize);

	iterator it2 = op2.begin();
	iterator it3 = sum.begin();
	for (; it2 != op2.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.begin();
	iterator it4 = it3;
	for (++it4; it4 != sum.end(); ++it3, ++it4)
	if (*it3 > 9)
	{
		(*it3) -= 10;
		(*it4)++;
	}

	if (*it3 == 0)
		sum.resize(sumSize - 1);

	return sum;
} // end function operator+

template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger< T > &op2)
{
	unsigned int op1Size = size();
	unsigned int op2Size = op2.size();
	unsigned int differenceSize = (op1Size > op2Size) ? op1Size : op2Size;

	HugeInteger< T > difference(differenceSize);

	iterator it1 = begin();
	iterator it2 = op2.begin();
	iterator it3 = difference.begin();

	for (; it1 != end(); ++it1, ++it3)
		*it3 = *it1;

	it3 = difference.begin();

	for (; it3 != difference.end() && it2 != op2.end(); ++it2, ++it3){
		if (*it3 < *it2){
			*it3 = *it3 + 10 - *it2;
			++it3;
			int temp = 0;
			for (; *it3 < 1; temp++){
				*it3 = 9;
				++it3;
			}
			*it3 -= 1;
			for (int i = temp; i >= 0; i--)
				--it3;
		}
		else
			*it3 = *it3 - *it2;
	}

	if (differenceSize == 0)
		differenceSize = 1;
	difference.resize(differenceSize);

	it3 = difference.end();
	--it3;

	while (*it3 == 0 && differenceSize > 1){
		differenceSize--;
		--it3;
	}

	difference.resize(differenceSize);

	return difference;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger< T > &op2)
{
	unsigned int op1Size = size();
	unsigned int op2Size = op2.size();
	unsigned int productSize = op1Size + op2Size;

	HugeInteger < T > product(productSize);

	iterator it1 = begin();
	iterator it2 = op2.begin();
	iterator it3 = product.begin();
	if (isZero() || op2.isZero()){
		productSize = 1;
		*it3 = 0;
		product.resize(productSize);
	}
	else{
		int i = 0;
		for (; it2 != op2.end(); ++it2){
			for (int j = i; j > 0; j--)
				++it3;
			i++;
			for (; it1 != end(); ++it1, ++it3){

				(*it3) += (*it1) * (*it2);

			}
			it3 = product.begin();
			it1 = begin();
		}
		iterator it4 = it3 = product.begin();
		for (++it4; it4 != product.end(); ++it4, ++it3){
			if (*it3 >= 10){
				(*it4) += (*it3) / 10;
				(*it3) %= 10;
			}
		}
		while (*it3 == 0){
			productSize--;
			--it3;
		}
		product.resize(productSize);
	}
	return product;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger< T > &op2)
{
	if (*this < op2){
		unsigned int quotientSize = 1;
		HugeInteger< T > quotient(quotientSize);
		iterator it3 = quotient.begin();
		*it3 = 0;

		return quotient;
	}


	unsigned int quotientSize = size() - op2.size() + 1;
	HugeInteger< T > quotient(quotientSize);

	int n = size() - op2.size();
	HugeInteger< T > buffer(size());
	unsigned int remainderSize = size();
	HugeInteger< T > remainder(remainderSize);
	iterator it1 = begin();
	iterator it2 = op2.begin();
	reverse_iterator it3 = quotient.rbegin();
	iterator itb = buffer.begin();
	iterator itr = remainder.begin();

	for (int i = 0; i < n; i++)
		++itb;

	for (; it2 != op2.end(); ++itb, ++it2)
		*itb = *it2;

	if (*this < buffer)
	{
		buffer.divideByTen();
		quotient.resize(size() - op2.size());
	}

	for (; it1 != end(); ++itr, ++it1)
		*itr = *it1;


	for (it3 = quotient.rbegin(); it3 != quotient.rend(); ++it3)
	{
		while (buffer <= remainder)
		{
			remainder = remainder - buffer;
			(*it3)++;
			itr = remainder.end();
			--itr;
			while (*itr == 0 && remainder.size() > 1)
			{
				remainder.resize(remainder.size() - 1);
				itr = remainder.end();
				--itr;
			}
		}

		if (buffer > remainder)
			buffer.divideByTen();

	}

	itr = remainder.end();
	--itr;

	while (*itr == 0 && remainder.size() > 1)
	{
		remainder.resize(remainder.size() - 1);
		itr = remainder.end();
	}
	return quotient;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T > &op2)
{

	if (*this < op2){
		unsigned int remainderSize = size();
		HugeInteger< T > remainder(remainderSize);
		iterator it1 = begin();
		iterator itr = remainder.begin();

		for (; it1 != end(); ++itr, ++it1)
			*itr = *it1;


		return remainder;
	}

	unsigned int quotientSize = size() - op2.size() + 1;
	HugeInteger< T > quotient(quotientSize);

	int n = size() - op2.size();
	HugeInteger< T > buffer(size());
	unsigned int remainderSize = size();
	HugeInteger< T > remainder(remainderSize);
	iterator it1 = begin();
	iterator it2 = op2.begin();
	reverse_iterator it3 = quotient.rbegin();
	iterator itb = buffer.begin();
	iterator itr = remainder.begin();

	for (int i = 0; i < n; i++)
		++itb;

	for (; it2 != op2.end(); ++itb, ++it2)
		*itb = *it2;

	if (*this < buffer)
	{
		buffer.divideByTen();
		quotient.resize(size() - op2.size());
	}

	for (; it1 != end(); ++itr, ++it1)
		*itr = *it1;

	for (it3 = quotient.rbegin(); it3 != quotient.rend(); ++it3)
	{

		while (buffer <= remainder)
		{
			remainder = remainder - buffer;
			(*it3)++;
			itr = remainder.end();
			--itr;
			while (*itr == 0 && remainder.size() > 1)
			{
				remainder.resize(remainder.size() - 1);
				itr = remainder.end();
				--itr;
			}
		}

		if (buffer > remainder)
			buffer.divideByTen();
	}

	itr = remainder.end();
	--itr;

	while (*itr == 0 && remainder.size() > 1)
	{
		remainder.resize(remainder.size() - 1);
		itr = remainder.end();
	}
	return remainder;
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert(vector< unsigned int > intVector)
{
	// intVector[ intVector.end() - 1 ] is the most significant digit ( could be 0 )
	// intVector[ 0 ] is the least significant digit

	unsigned int numDigits = intVector.size();
	vector< unsigned int >::reverse_iterator it = intVector.rbegin();
	for (; it != intVector.rend(); ++it, --numDigits)
	if (*it != 0)
		break;

	// it points to the most significant nonzero digit in intVector

	if (numDigits == 0) // all digits of intVector are 0
		return;

	resize(numDigits);
	vector< unsigned int >::iterator it1 = intVector.begin();
	iterator it2 = begin();
	for (; it2 != end(); ++it1, ++it2)
		*it2 = *it1;

	// begin() points to the least significant digit
	// end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	for (iterator it = begin(); it != end(); ++it)
	if (*it != 0)
		return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	iterator it1 = begin();
	iterator it2 = it1;
	for (++it2; it2 != end(); ++it1, ++it2)
		*it1 = *it2;
	resize(size() - 1);
}

// overloaded output operator for class HugeInteger
template< typename T >
std::ostream &operator<<(std::ostream &output, HugeInteger< T > &hugeInteger)
{
	if (hugeInteger.size() == 0)
		output << 0;
	else
	{
		list< T >::reverse_iterator it = hugeInteger.rbegin();
		for (; it != hugeInteger.rend(); ++it)
			output << *it;
	}

	return output; // enables cout << x << y;
}