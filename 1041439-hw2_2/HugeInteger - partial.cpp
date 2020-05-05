// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor
HugeInteger::HugeInteger()
: size(0), ptr(new int[0]())
{

}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
: size(n),
ptr(new int[n]())

{
	for (int i = 0; i < n; i++)
		ptr[i] = 0;
}

HugeInteger::HugeInteger(const HugeInteger &integerToCopy)
: size(integerToCopy.size),
ptr(new int[size]())
{
	
	for (int i = 0; i < size; i++)
		ptr[i] = integerToCopy.ptr[i];

}

// destructor
HugeInteger::~HugeInteger()
{
	delete[] ptr;
}

bool HugeInteger::equal(const HugeInteger &op2)const
{
	if (size != op2.size)
		return false;
	iterator it1 = begin();
	iterator it2 = op2.begin();
	for (; it1!=end(); ++it1,++it2)
		if (*it1 != *it2)
			return false;
	return true;

}

bool HugeInteger::less(const HugeInteger &op2)const
{
	if (op2.size > size)
		return true;
	if (size > op2.size)
		return false;
	iterator it1 = end();
	iterator it2 = op2.end();
	for (--it1,--it2; it1>=begin(); --it1,--it2)
	{
		if (*it2 > *it1)
			return true;
		else if (*it2 < *it1)
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

bool HugeInteger::notEqual(const HugeInteger &op2)const
{
	if (size != op2.size)
		return true; 
	iterator it1 = begin();
	iterator it2 = op2.begin();
	for (; it1!=end(); ++it1,++it2){
		if (*it1 != *it2)
			return true;
	}
	return false;
}

bool HugeInteger::greater(const HugeInteger &op2)const
{
	if (op2.size < size)
		return true;
	if (size < op2.size)
		return false;
	iterator it1 = end();
	iterator it2 = op2.end();
	for (--it1,--it2; it1>=begin(); --it1,--it2)
	{
		if (*it2 < *it1)
			return true;
		else if (*it2 > *it1)
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


// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( const HugeInteger &op2 ) const
{
   unsigned int sumSize = ( size >= op2.size ) ? size + 1 : op2.size + 1;

   HugeInteger sum( sumSize );

   iterator it1 = begin();
   iterator it3 = sum.begin();
   for( ; it1 != end(); ++it1, ++it3 )
      *it3 = *it1;

   iterator it2 = op2.begin();
   for( it3 = sum.begin(); it2 != op2.end(); ++it2, ++it3 )
      *it3 += *it2;

   it3 = sum.begin();
   iterator it4 = it3;
   for( ++it4; it4 != sum.end(); ++it3, ++it4 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *it4 )++;
      }

   if( *it3 == 0 )
      sum.resize( sumSize - 1 );

   return sum;
} // end function add

HugeInteger HugeInteger::subtract(const HugeInteger &op2) const
{
	unsigned int differenceSize = (size >= op2.size) ? size : op2.size;
	HugeInteger difference(differenceSize);
	iterator it1 = begin();
	iterator it2 = op2.begin();
	iterator it3 = difference.begin();
	if (equal(op2)){
		differenceSize=1;
		*it3 = 0;
		difference.resize(differenceSize);
	}
	else{
		if (greater(op2))
		{
			for (; it2 != op2.end(); ++it1,++it2,++it3)
				*it3 = (*it1) - (*it2);
			for (; it1!=end(); ++it1,++it3)
				*it3 = (*it1);
		}
		else
		{
			for (; it1 != end(); ++it1, ++it2, ++it3)
				*it3 = (*it2) - (*it1);
			for (; it2!=op2.end(); ++it2,++it3)
				*it3 = (*it2);
		}
		
		iterator it4 = it3 = difference.begin();
		for (++it4; it4 != difference.end(); ++it3,++it4)
		if (*it3 < 0)
		{
			(*it3) += 10;
			(*it4)--;
		}
		for (; *it3 == 0; it3--)
			differenceSize--;
		difference.resize(differenceSize);
		
	}

	return difference;
}

HugeInteger HugeInteger::multiply(const HugeInteger &op2) const
{
	unsigned int productSize = size + op2.size;
	HugeInteger product(productSize);
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
			it3 = product.begin()+i;
			i++;
			for (; it1 != end(); ++it1, ++it3)
				(*it3) += (*it1) * (*it2);
				
			it3 = product.begin();
			it1 = begin();
		}
		iterator it4 = it3 = product.begin();
		for (++it4; it4 !=product.end();++it4,++it3){
			if (*it3 >= 10){
				(*it4) += (*it3) / 10;
				(*it3) %= 10;
			}
		}
		while (*it3 == 0){
			productSize--;
			it3--;
		}
		product.resize(productSize);
	}
	return product;
}

HugeInteger HugeInteger::divide(const HugeInteger &op2) const
{
	int n = size - op2.size;
	int bufferSize = size, k = 0, remainderSize = size;
	HugeInteger buffer(bufferSize);
	HugeInteger remainder(remainderSize);
	iterator it1 = begin();
	iterator it2 = op2.begin();
	iterator itb = buffer.begin();
	iterator itr = remainder.begin();
	if (size > op2.size)
		buffer.resize(size);
	else
		buffer.resize(op2.size);

	while (n < 0)
		n++;
	unsigned int quotientSize = n + 1;

	HugeInteger quotient(quotientSize);
	iterator  it3 = quotient.begin();

	if (less(op2)){
		*it3 = 0;
		quotientSize = 1;
		quotient.resize(quotientSize);
		
	}
	else if(equal(op2)){
		*it3 = 1;
		quotientSize = 1;
		quotient.resize(quotientSize);
	}
	else if (*it2 == 1 && op2.size==1) {

		for (; it1 != end(); ++it1, ++it3)
			*it3 = (*it1);
	}
	else{
		for (; it2 != op2.end(); ++it2, ++itb)
			(*itb) = (*it2);

		if (less(buffer))
		{
			buffer.divideByTen();
			quotientSize--;
			quotient.resize(quotientSize);
		}

		for (; it3 != quotient.end(); ++it3)
			*it3 = 0;


		for (; it1 != end(); ++it1, ++itr)
			(*itr) = (*it1);


		
		for (it3--; it3 >= quotient.begin(); --it3)
		{
			while (buffer.lessEqual(remainder))
			{
				remainder.assign(remainder.subtract(buffer));
				(*it3)++;

			}
			buffer.divideByTen();
		}
		if (quotientSize == 0)
			quotientSize = 1;
		quotient.resize(quotientSize);

	}
	return quotient;

}

HugeInteger HugeInteger::modulus(const HugeInteger &op2) const
{
	int n = size - op2.size;
	int bufferSize = size, k = 0, remainderSize = size;
	HugeInteger buffer(bufferSize);
	HugeInteger remainder(remainderSize);
	iterator it1 = begin();
	iterator it2 = op2.begin();
	iterator itb = buffer.begin();
	iterator itr = remainder.begin();

	if (less(op2)){
		for (; itr != remainder.end(); itr++, it1++)
			*itr = *it1;
	}
	else if (*it2 == 1 && op2.size==1){
		*itr = 0;
		remainder.resize(1);
	}
	else{
		if (size > op2.size)
			buffer.resize(size);
		else
			buffer.resize(op2.size);

		while (n < 0)
			n++;
		unsigned int quotientSize = n + 1;

		HugeInteger quotient(quotientSize);
		iterator  it3 = quotient.begin();


		for (; it2 != op2.end(); ++it2, ++itb)
			(*itb) = (*it2);

		if (less(buffer))
		{
			buffer.divideByTen();
			quotientSize--;
		}
		quotient.resize(quotientSize);

		for (; it3 != quotient.end(); ++it3)
			(*it3) = 0;


		for (; it1 != end(); ++it1, ++itr)
			(*itr) = (*it1);


		for (--it3; it3 >= quotient.begin(); it3--)
		{
			while (buffer.lessEqual(remainder))
			{
				remainder.assign(remainder.subtract(buffer));
				(*it3)++;

			}
			buffer.divideByTen();
		}

		it2 = op2.begin();
		itr = remainder.begin();

	}
	return remainder;

}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert( vector< int > intVector )
{
   // intVector[ 0 ] is the most significant digit ( could be 0 )
   // intVector[ intVector.end() - 1 ] is the least significant digit

   iterator end = &intVector[ 0 ] + intVector.size();
   iterator msd = &intVector[ 0 ];
   for( ; msd != end; ++msd ) // find the position of the most significant nonzero digit
      if( *msd != 0 )
         break;

   // msd points to the most significant nonzero digit in intVector

   if( msd == end ) // all digits of intVector are 0
      return;
   
   resize( end - msd );
   iterator it1 = msd;
   reverse_iterator it2 = rbegin();
   for( ; it2 != rend(); ++it1, --it2 )
      *it2 = *it1;

   // begin() points to the least significant digit
   // end() points to the most significant nonzero digit

} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero() const
{
   for( iterator it = begin(); it != end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   iterator it = begin();
   iterator it2 = it;
   for( ++it2; it2 != end(); ++it, ++it2 )
      *it = *it2;
   resize( size - 1 );
}

// overloaded output operator
void HugeInteger::output() const
{
   if( size == 0 )
      cout << 0;
   else
   {
      reverse_iterator it = rbegin();
      for( ; it != rend(); --it )
         cout << *it;
   }
} // end function output

int* HugeInteger::begin() const
{
   return ptr;
}

int* HugeInteger::end() const
{
   return ptr + size;
}

int* HugeInteger::rbegin() const
{
   return ptr + size - 1;
}

int* HugeInteger::rend() const
{
   return ptr - 1;
}

void HugeInteger::resize(unsigned int n)
{
	size = n;
	int *ob;
	ob = new int[size];
	for (int i=0; i < n; i++)
		*(ob+i) = *(ptr+i);
		
	delete [] ptr;
	ptr = new int[n];

	for (int i = 0; i < n; i++)
		ptr[i] = ob[i];
	delete []ob;
}

const HugeInteger &HugeInteger::assign(const HugeInteger &right)
{
	if (size != right.size){
		delete [] ptr;
		size = right.size;
		ptr = new int[size];
	}
	for (int i = 0; i < size; i++)
		ptr[i] = right.ptr[i];

	return *this;

}