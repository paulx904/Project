// Member-function definitions for class Vector

#include "Vector.h" // include definition of class Vector

// constructor; constructs a zero vector with size n
Vector::Vector(unsigned int n)
: size(n),
capacity(n),
ptr(new int[n]())
{
} // end Vector constructor

Vector::Vector(const Vector &vectorToCopy)
: size(vectorToCopy.size),
ptr(new int[size]())
{

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = vectorToCopy.ptr[i];

}

// destructor; destroys the Vector
Vector::~Vector()
{
	delete[] ptr;
} // end destructor

int* Vector::begin() const
{
	return ptr;
}

int* Vector::end() const
{
	return ptr + size;
}

int* Vector::rbegin() const
{
	return ptr + size - 1;
}

int* Vector::rend() const
{
	return ptr - 1;
}

unsigned int Vector::getSize() const
{
	return size;
}

void Vector::push_back(const int val)
{
	
	resize(size + 1);
	ptr[size - 1] = val;
}

bool Vector::equal(const Vector &op2)const
{
	if (size != op2.size)
		return false;
	iterator it1 = begin();
	iterator it2 = op2.begin();
	for (; it1 != end(); ++it1,++it2)
	if (*it1 != *it2)
		return false;
	return true;

}

bool Vector::notEqual(const Vector &op2)const
{
	if (size != op2.size)
		return true;
	iterator it1 = begin();
	iterator it2 = op2.begin();
	for (; it1 != end(); ++it1,++it2)
	if (*it1 != *it2)
		return true;
	return false;
}

void Vector::resize(unsigned int n)
{
	if (size < n)
	{

		int *temp;
		temp = new int[n];
		capacity = n;

		for (int i = 0; i < n; i++)
			temp[i] = 0;

		for (unsigned int i = 0; i < size && i < n; i++)
			temp[i] = ptr[i];

		delete[] ptr;
		ptr = temp;
	}
	size = n;
	/*
	for (int i = 0; i < size; i++)
		ptr[i] = 0;

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = temp[i];


	delete[] temp;
	*/
}

const Vector &Vector::assign(const Vector &right)
{
	if (size != right.size){
		delete[] ptr;
		size = right.size;
		ptr = new int[size];
	}
	for (unsigned int i = 0; i < size; i++)
		ptr[i] = right.ptr[i];

	return *this;

}