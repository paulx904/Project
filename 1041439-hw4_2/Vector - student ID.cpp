// Member-function definitions for class Vector
#include <iostream>
using namespace std;
#include "Vector.h" // include definition of class Vector

// Constructs a vector with n elements. Each element is a copy of val
Vector::Vector(unsigned int n)
: size(n),
capacity(n),
ptr(new unsigned int[n]())
{
} // end Vector default constructor

Vector::Vector(const Vector &vectorToCopy)
: size(vectorToCopy.size),
ptr(new unsigned int[size]())
{

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = vectorToCopy.ptr[i];

}

// destructor
Vector::~Vector()
{
	delete[] ptr;
} // end destructor

unsigned int* Vector::begin() const
{
	return ptr;
}

unsigned int* Vector::end() const
{
	return ptr + size;
}

unsigned int* Vector::rbegin() const
{
	return ptr + size - 1;
}

unsigned int* Vector::rend() const
{
	return ptr - 1;
}

unsigned int Vector::getSize() const
{
	return size;
}

void Vector::push_back(const unsigned int val)
{

	resize(size + 1);
	ptr[size - 1] = val;

}

const Vector &Vector::operator=(const Vector &right)
{
	if (size != right.size){
		delete[] ptr;
		size = right.size;
		ptr = new unsigned int[size];
	}
	for (unsigned int i = 0; i < size; i++)
		ptr[i] = right.ptr[i];

	return *this;

}

bool Vector::operator==(const Vector &op2)const
{
	if (size != op2.size)
		return false;
	iterator it1 = begin();
	iterator it2 = op2.begin();
	for (; it1 != end(); ++it1, ++it2)
	if (*it1 != *it2)
		return false;
	return true;

}

bool Vector::operator!=(const Vector &op2)const
{
	if (size != op2.size)
		return true;
	iterator it1 = begin();
	iterator it2 = op2.begin();
	for (; it1 != end(); ++it1, ++it2)
	if (*it1 != *it2)
		return true;
	return false;
}

void Vector::resize(unsigned int n)
{
	int *temp;
	temp = new int[n];

	for (unsigned int i = 0; i < n; i++)
		temp[i] = 0;

	for (unsigned int i = 0; i < size && i < n; i++)
		temp[i] = ptr[i];


	size = n;


	ptr = new unsigned int[size];

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = 0;

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = temp[i];


	delete[] temp;
}

unsigned int &Vector::operator[](unsigned int subscript)
{
	return ptr[subscript];
}

unsigned int Vector::operator[](unsigned int subscript) const
{
	return ptr[subscript];
}
