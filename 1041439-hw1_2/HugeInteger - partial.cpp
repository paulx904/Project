// Member-function definitions for class HugeInteger.
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger 

// default constructor; construct a HugeInteger with size 0
HugeInteger::HugeInteger()
{
   size = 0;
} // end HugeInteger default constructor

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( int n )
{
   size = ( n >= 0 && n <= digits ) ? n : digits;
   for( int i = 0; i < size; i++ )
      integer[ i ] = 0;
} // end HugeInteger constructor

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert( char numericString[] )
{
   size = strlen( numericString );
   for( int i = 0; i < size; i++ )
      integer[ i ] = numericString[ size - i - 1 ] - '0';

   for( ; size > 0; size-- )
      if( integer[ size - 1 ] != 0 )
         break;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( int i = 0; i < size; i++ )
      if( integer[ i ] != 0 )
         return false;         
   return true;
} // end function isZero

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( HugeInteger op2 )
{
   int sumSize = ( size >= op2.size ) ? size + 1 : op2.size + 1;
   HugeInteger sum( sumSize );

   for( int i = 0; i < size; i++ )
      sum.integer[ i ] = integer[ i ];

   for( int i = 0; i < op2.size; i++ )
      sum.integer[ i ] += op2.integer[ i ];

   for( int i = 0; i < sum.size - 1; i++ ) 
      if( sum.integer[ i ] > 9 ) // determine whether to carry a 1
      {
         sum.integer[ i ] -= 10; // reduce to 0-9
         sum.integer[ i + 1 ]++;
      }

   if( sum.integer[ sum.size - 1 ] == 0 )
      sum.size--;

   return sum;
} // end function add

// overloaded output operator
void HugeInteger::output()
{
   if( size == 0 )
      cout << 0;
   else
      for( int i = size - 1; i >= 0; i-- )
         cout << integer[ i ];
} // end function output

void HugeInteger::divideByTen()
{
   if( size > 0 )
   {
      for( int i = 1; i < size; i++ )
         integer[ i - 1 ] = integer[ i ];
      integer[ size - 1 ] = 0;
      size--;
   }
} // end function divideByTen

bool HugeInteger::less(HugeInteger op2)
{
	if (op2.size > size)
		return true;
	if (size > op2.size)
		return false;
	for (int i = size - 1; i >= 0; i--)
	{
		if (op2.integer[i] > integer[i])
			return true;
		else if (op2.integer[i] < integer[i])
			return false;
	}
	return false;
}

bool HugeInteger::lessEqual(HugeInteger op2)
{
	if (equal(op2) || less(op2))
		return true;
	else
		return false;
}

bool  HugeInteger::equal(HugeInteger op2)
{
	if (size != op2.size)
		return false;
	for (int i = 0; i < size; i++){
		if (integer[i] != op2.integer[i])
			return false;
	}
	return true;

}

bool  HugeInteger::notEqual(HugeInteger op2)
{
	if (size != op2.size)
		return true;
	for (int i = 0; i < size; i++){
		if (integer[i] != op2.integer[i])
			return true;
	}
	return false;
}

bool  HugeInteger::greater(HugeInteger op2)
{
	if (op2.size < size)
		return true;
	if (size < op2.size)
		return false;
	for (int i = size - 1; i >= 0; i--)
	{
		if (op2.integer[i] < integer[i])
			return true;
		else if (op2.integer[i] > integer[i])
			return false;
	}
	return false;
}

bool HugeInteger::greaterEqual(HugeInteger op2)
{
	if (equal(op2) || greater(op2))
		return true;
	else
		return false;
}

HugeInteger HugeInteger::subtract(HugeInteger op2)
{
	int differenceSize = (size >= op2.size) ? size : op2.size;
	HugeInteger difference(differenceSize);
	if (equal(op2)){
		difference.size = 1;
		difference.integer[0] = 0;
	}
	else{
		if (size >= op2.size)
		{
			for (int i = 0; i < size; i++)
				difference.integer[i] = integer[i] - op2.integer[i];
			for (int i = op2.size; i < size; i++)
				difference.integer[i] = integer[i];
		}
		else
		{
			for (int i = 0; i < size; i++)
				difference.integer[i] = op2.integer[i] - integer[i];
			for (int i = size; i < op2.size; i++)
				difference.integer[i] = op2.integer[i];
		}
		for (int i = 0; i < difference.size - 1; i++)
		if (difference.integer[i] < 0)
		{
			difference.integer[i] += 10;
			difference.integer[i + 1]--;
		}
		for (int i = difference.size - 1; difference.integer[i] == 0; i--)
			difference.size--;
	}
	
	return difference;
}

HugeInteger HugeInteger::multiply(HugeInteger op2)
{
	int productSize = size + op2.size;
	HugeInteger product(productSize);
	if (isZero() || op2.isZero()){
		product.size = 1;
		product.integer[0] = 0;
	}
	else{
		for (int i = 0; i < size; i++){
			for (int j = 0; j < op2.size; j++){
				product.integer[i + j] += integer[i] * op2.integer[j];
			}
		}
		for (int i = 0; i < product.size; i++){
			if (product.integer[i] >= 10){
				product.integer[i + 1] += product.integer[i] / 10;
				product.integer[i] %= 10;
			}
		}
		while (product.integer[product.size - 1] == 0){
			product.size--;
		}
	}
	return product;
}

HugeInteger HugeInteger::divide(HugeInteger op2)
{
	int n = size - op2.size;
	int bufferSize = size, k = 0, remainderSize = size;
	HugeInteger buffer(bufferSize);
	HugeInteger remainder(remainderSize);
	if (size > op2.size)
		buffer.size = size;
	else
		buffer.size = op2.size;

	while (n < 0)
		n++;
	int quotientSize = n + 1;

	HugeInteger quotient(quotientSize);
	

	for (int i = op2.size - 1, b = buffer.size - 1; i >= 0; i--, b--)
	{
		buffer.integer[b] = op2.integer[i];
	}
	
	if (less(buffer))
	{
		buffer.divideByTen();
		quotient.size--;
	}
	
	for (int i = 0; i < quotient.size; i++)
		quotient.integer[i] = 0;


	for (int i = 0; i < size; i++)
	{
		remainder.integer[i] = integer[i];
	}

	for (int k = quotient.size - 1; k >= 0; k--)
	{
		while (buffer.lessEqual(remainder))
		{
			remainder = remainder.subtract(buffer);
			quotient.integer[k]++;

		}
		buffer.divideByTen();
	}
	if (quotient.size == 0)
		quotient.size = 1;
	return quotient;

}

HugeInteger HugeInteger::modulus(HugeInteger op2)
{
	int n = size - op2.size;
	int bufferSize = size, k = 0, remainderSize = size;
	HugeInteger buffer(bufferSize);
	HugeInteger remainder(remainderSize);
	if (size > op2.size)
		buffer.size = size;
	else
		buffer.size = op2.size;

	while (n < 0)
		n++;
	int quotientSize = n + 1;

	HugeInteger quotient(quotientSize);


	for (int i = op2.size - 1, b = buffer.size - 1; i >= 0; i--, b--)
	{
		buffer.integer[b] = op2.integer[i];
	}

	if (less(buffer))
	{
		buffer.divideByTen();
		quotient.size--;
	}

	for (int i = 0; i < quotient.size; i++)
		quotient.integer[i] = 0;


	for (int i = 0; i < size; i++)
	{
		remainder.integer[i] = integer[i];
	}

	for (int k = quotient.size - 1; k >= 0; k--)
	{
		while (buffer.lessEqual(remainder))
		{
			remainder = remainder.subtract(buffer);
			quotient.integer[k]++;

		}
		buffer.divideByTen();
	}
	if (quotient.size == 0)
		quotient.size = 1;

	/*if (op2.size == 1 && op2.integer[0] == 1){
		remainder.size = 1; 
		remainder.integer[0] = 0;
		
	}*/


	return remainder;
}