// Member-function definitions for class template Vector

#include "Vector.h" // include definition of class template Vector

// Constructs a vector with n elements. Each element is a copy of val
template< typename T >
Vector< T >::Vector(unsigned int n)
: size(n),
capacity(n),
ptr(new T[n]())
{
} // end Vector constructor

template< typename T >
Vector< T >::Vector(const Vector < T > &vectorToCopy)
: size(vectorToCopy.size),
capacity(vectorToCopy.size),
ptr(new T[size]())
{

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = vectorToCopy.ptr[i];

}

// destructor
template< typename T >
Vector< T >::~Vector()
{
	delete[] ptr;
} // end destructor

template< typename T >
T* Vector< T >::begin() const
{
	return ptr;
}

template< typename T >
T* Vector< T >::end() const
{
	return ptr + size;
}

template< typename T >
T* Vector< T >::rbegin() const
{
	return ptr + size - 1;
}

template< typename T >
T* Vector< T >::rend() const
{
	return ptr - 1;
}

template< typename T >
unsigned int Vector< T >::getSize() const
{
	return size;
}

template< typename T >
void Vector< T >::push_back(const T val)
{
	resize(size + 1);
	ptr[size - 1] = val;
}

template< typename T >
const Vector< T > &Vector< T >::operator=(const Vector < T > &right)
{
	if (size != right.size){
		delete[] ptr;
		size = right.size;
		ptr = new T[size];
	}
	for (unsigned int i = 0; i < size; i++)
		ptr[i] = right.ptr[i];

	return *this;

}


template< typename T >
bool Vector< T >::operator==(const Vector &op2)const
{
	/*if (size != op2.size)
		return false;*/
	iterator it1 = begin();
	iterator it2 = op2.begin();
	for (; it1 != end(); ++it1, ++it2)
	if (*it1 != *it2)
		return false;
	return true;

}

template< typename T >
bool Vector< T >::operator!=(const Vector &op2)const
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

template< typename T >
void Vector< T >::resize(unsigned int n)
{
	T *temp;
	temp = new T[n];

	for (unsigned int i = 0; i < n; i++)
		temp[i] = 0;

	for (unsigned int i = 0; i < size && i < n; i++)
		temp[i] = ptr[i];


	size = n;


	ptr = new T[size];

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = 0;

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = temp[i];


	delete[] temp;
}