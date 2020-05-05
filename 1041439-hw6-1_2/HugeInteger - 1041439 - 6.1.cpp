// Member-function definitions for class template HugeInteger

#include "HugeInteger.h" // include definition of class template HugeInteger
#include "List - 1041439 - 6.cpp" // include member-function definitions for class template List 
#include "Vector - 1041439 - 6.cpp" // include member-function definitions for class template Vector 

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

// function to test if one HugeInteger< T > is greater than another

template< typename T >
bool HugeInteger< T >::operator<(const HugeInteger< T > &right) const
{
	unsigned int size = integer.getSize();
	unsigned int rightSize = right.integer.getSize();
	if (rightSize > size)
		return true;
	if (size > rightSize)
		return false;
	List < T >::iterator it1 = integer.rbegin();
	List < T >::iterator it2 = right.integer.rbegin();
	for (; it1 != integer.rend(); it1 = it1->rlink, it2 = it2->rlink)
	{
		if (it1->data < it2->data)
			return true;
		else if (it2->data < it1->data)
			return false;
	}
	return false;
}

template< typename T >
bool HugeInteger< T >::operator>(const HugeInteger< T > &right) const
{
	return (right < *this);
}

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(const HugeInteger< T > &right) const
{
	return (*this == right || *this < right);
}

// function that tests if one HugeInteger< T > is greater than or equal to another
template< typename T >
bool HugeInteger< T >::operator>=(const HugeInteger< T > &right) const
{
	return (!(*this < right));
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(const HugeInteger< T > &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int sumSize = (size >= op2Size) ? size + 1 : op2Size + 1;

	HugeInteger< T > sum(sumSize);

	List< T >::iterator it1 = integer.begin();
	List< T >::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); it1 = it1->llink, it3 = it3->llink)
		it3->data = it1->data;

	List< T >::iterator it2 = op2.integer.begin();
	it3 = sum.integer.begin();
	for (; it2 != op2.integer.end(); it2 = it2->llink, it3 = it3->llink)
		it3->data += it2->data;

	it3 = sum.integer.begin();
	List< T >::iterator it4 = it3;
	it4 = it4->llink;
	for (; it4 != sum.integer.end(); it3 = it3->llink, it4 = it4->llink)
	if (it3->data > 9)
	{
		it3->data -= 10;
		(it4->data)++;
	}

	if (it3->data == 0)
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

	List < T >::iterator it1 = integer.begin();
	List < T >::iterator it2 = op2.integer.begin();
	List < T >::iterator it3 = difference.integer.begin();

	for (; it1 != integer.end(); it1 = it1->llink, it3 = it3->llink)
		it3->data = it1->data;

	it3 = difference.integer.begin();

	for (; it3 != difference.integer.end() && it2 != op2.integer.end(); it2 = it2->llink, it3 = it3->llink){
		if (it3->data < it2->data){
			it3->data = it3->data + 10 - it2->data;
			it3 = it3->llink;
			int temp = 0;
			for (; it3->data < 1; temp++){
				it3->data = 9;
				it3 = it3->llink;
			}
			(it3->data)--;
			for (; temp >= 0; temp--)
				it3 = it3->rlink;
		}
		else
			it3->data = it3->data - it2->data;
	}


	it3 = difference.integer.rbegin();

	while (it3->data == 0 && differenceSize > 1){
		differenceSize--;
		it3 = difference.integer.rbegin();
	}	difference.integer.resize(differenceSize);
	cout << differenceSize << endl;

	/*if (differenceSize == 0)
		difference.integer.resize(1);*/
	return difference;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(const HugeInteger< T > &op2) const
{
	unsigned int size = integer.getSize();
	unsigned int op2Size = op2.integer.getSize();
	unsigned int productSize = size + op2Size;

	HugeInteger < T > product(productSize);

	List < T >::iterator it1 = integer.begin();
	List < T >::iterator it2 = op2.integer.begin();
	List < T >::iterator it3 = product.integer.begin();
	if (isZero() || op2.isZero()){
		productSize = 1;
		it3->data = 0;
		product.integer.resize(productSize);
	}
	else{
		int i = 0;
		for (; it2 != op2.integer.end(); it2=it2->llink){
			for (int temp = i; temp > 0; temp--){
				it3 = it3->llink;
			}
			i++;
			for (; it1 != integer.end(); it1 = it1->llink, it3 = it3->llink){

				it3->data += (it1->data * it2->data);

			}
			it3 = product.integer.begin();
			it1 = integer.begin();
		}

		List < T >::iterator it4 = it3 = product.integer.begin();
		for (it4 = it4->llink; it4 != product.integer.end(); it4 = it4->llink, it3 = it3->llink){
			if (it3->data >= 10){
				it4->data += (it3->data / 10);
				it3->data %= 10;
			}
		}
		while (it3->data == 0 && productSize > 1){
			productSize--;
			it3 = it3->rlink;
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
		List < T >::iterator it3 = quotient.integer.begin();
		it3->data = 0;

		return quotient;
	}

	
	unsigned int quotientSize = integer.getSize() - op2.integer.getSize() + 1;
	HugeInteger< T > quotient(quotientSize);
	int n = integer.getSize() - op2.integer.getSize();
	HugeInteger< T > buffer(integer.getSize());
	unsigned int remainderSize = integer.getSize();
	HugeInteger< T > remainder(remainderSize);
	List< T >::iterator it1 = integer.begin();
	List< T >::iterator it2 = op2.integer.begin();
	List< T >::iterator it3 = quotient.integer.begin();
	List< T >::iterator itb = buffer.integer.begin();
	List< T >::iterator itr = remainder.integer.begin();
	
	for (int i = 0; i < n; i++)
		itb = itb->llink;

	for (; it2 != op2.integer.end(); it2 = it2->llink, itb = itb->llink)
		itb->data = it2->data;



	if (*this < buffer)
	{
		buffer.divideByTen();
		quotient.integer.resize(integer.getSize() - op2.integer.getSize());
	}

	for (; it1 != integer.end(); it1 = it1->llink, itr = itr->llink)
		itr->data = it1->data;

	for (it3 = quotient.integer.rbegin(); it3 != quotient.integer.rend(); it3=it3->rlink)
	{
		while (buffer <= remainder)
		{
			remainder = remainder - buffer;
			(it3->data)++;
			itr = remainder.integer.rbegin();
			while (itr->data == 0 && remainder.integer.getSize() > 1)
			{
				remainder.integer.resize(remainder.integer.getSize() - 1);
				itr = remainder.integer.rbegin();
			}
		}

		if (buffer > remainder)
			buffer.divideByTen();
	}

	itr = remainder.integer.rbegin();

	while (itr->data == 0 && remainder.integer.getSize() > 1)
	{
		remainder.integer.resize(remainder.integer.getSize() - 1);
		itr = remainder.integer.rbegin();
	}
	return quotient;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(const HugeInteger< T > &op2) const
{
	if (*this < op2){
		unsigned int remainderSize = integer.getSize();
		HugeInteger< T > remainder(remainderSize);
		List< T >::iterator it1 = integer.begin();
		List< T >::iterator itr = remainder.integer.begin();

		for (; it1!=integer.end(); it1=it1->llink,itr=itr->llink){
			itr->data = it1->data;
		}

		return remainder;
	}


	unsigned int quotientSize = integer.getSize() - op2.integer.getSize() + 1;
	HugeInteger< T > quotient(quotientSize);

	int n = integer.getSize() - op2.integer.getSize();
	HugeInteger< T > buffer(integer.getSize());
	unsigned int remainderSize = integer.getSize();
	HugeInteger< T > remainder(remainderSize);
	List< T >::iterator it1 = integer.begin();
	List< T >::iterator it2 = op2.integer.begin();
	List< T >::iterator it3 = quotient.integer.begin();
	List< T >::iterator itb = buffer.integer.begin();
	List< T >::iterator itr = remainder.integer.begin();

	for (int i = 0; i < n; i++)
		itb = itb->llink;

	for (; it2 != op2.integer.end(); it2 = it2->llink, itb = itb->llink)
	{
		itb->data = it2->data;
	}

	if (*this < buffer)
	{
		buffer.divideByTen();
		quotient.integer.resize(integer.getSize() - op2.integer.getSize());
	}

	for (; it1 != integer.end(); it1 = it1->llink, itr = itr->llink)
		itr->data = it1->data;

	for (it3 = quotient.integer.rbegin(); it3 != quotient.integer.rend(); it3 = it3->rlink)
	{
		while (buffer <= remainder)
		{
			remainder = remainder - buffer;
			(it3->data)++;
			itr = remainder.integer.rbegin();
			while (itr->data == 0 && remainder.integer.getSize() > 1)
			{
				remainder.integer.resize(remainder.integer.getSize() - 1);
				itr = remainder.integer.rbegin();
			}
		}

		if (buffer > remainder)
			buffer.divideByTen();
	}

	itr = remainder.integer.rbegin();

	while (itr->data == 0 && remainder.integer.getSize() > 1)
	{
		remainder.integer.resize(remainder.integer.getSize() - 1);
		itr = remainder.integer.rbegin();
	}
	return remainder;
}

template < typename T >
HugeInteger< T > &HugeInteger< T >::operator++()
{

	HugeInteger< T > prefixone(1);
	List < T >::iterator it = prefixone.integer.begin();
	it->data = 1;
	*this = (*this + prefixone);

	return *this;
}

template < typename T >
HugeInteger< T > HugeInteger< T >::operator++(int)
{
	HugeInteger< T > postfixone(1);
	List < T >::iterator it = postfixone.integer.begin();
	it->data = 1;
	*this = (*this + postfixone);
	return (*this - postfixone);
}

// convert a vector of decimal digits into a HugeInteger
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
	List< T >::reverse_iterator it2 = integer.rbegin();
	for (; it1 != vector.end(); ++it1, it2 = it2->rlink)
		it2->data = *it1;

	// integer.begin() points to the least significant digit
	// integer.end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
	for (List< T >::iterator it = integer.begin(); it != integer.end(); it = it->llink)
	if (it->data != 0)
		return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	List< T >::iterator it = integer.begin();
	List< T >::iterator it2 = it;
	for (it2 = it2->llink; it2 != integer.end(); it = it->llink, it2 = it2->llink)
		it->data = it2->data;
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
		List< T >::reverse_iterator it = hugeInteger.integer.rbegin();
		for (; it != hugeInteger.integer.rend(); it = it->rlink)
			output << it->data;
	}

	return output; // enables cout << x << y;
}