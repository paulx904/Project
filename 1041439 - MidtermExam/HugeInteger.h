// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include <iostream>
#include "Vector.h" // include definition of class template Vector 

template< typename T >
class HugeInteger
{
	template< typename T >
	friend ostream &operator<<(ostream &, const HugeInteger< T > &);
public:
	HugeInteger(); // default constructor; construct a HugeInteger with size 0

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger &integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger &operator=(const HugeInteger &right); // assignment operator

	bool operator==(const HugeInteger &right) const; // less than or equal to
	bool operator<(const HugeInteger &right) const;  // less than
	bool operator>=(const HugeInteger &right) const; // greater than or equal to

	// addition assignment operator; HugeInteger += HugeInteger
	void operator+=(const HugeInteger &op2);

	// subtraction assignment operator; HugeInteger -= HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	void operator-=(const HugeInteger &op2);

	// multiplication assignment operator; HugeInteger *= HugeInteger
	void operator*=(const HugeInteger &op2);

	void reset(); // set a HugeInteger to zero
	void convert(Vector< T > vector); // convert a vector of decimal digits into a HugeInteger
	bool isZero() const; // return true if and only if all digits are zero

private:
	Vector< T > integer;

	HugeInteger(unsigned int n); // constructor; construct a zero HugeInteger with size n
}; // end class template HugeInteger

#endif