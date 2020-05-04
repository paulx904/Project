// Member-function definitions for class template Vector

#include "Vector.h" // include definition of class template Vector

// constructor; constructs a zero vector with size n
template< typename T >
Vector< T >::Vector(unsigned int n)
: size(n)
{
	if (n == 0)
		ptr = nullptr;
	else
		ptr = new T[n]();
} // end Vector constructor

template< typename T >
Vector< T >::Vector(const Vector< T > &vectorToCopy)
: size(vectorToCopy.size)
{

	ptr = new T[size];

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = vectorToCopy.ptr[i];
}

// destructor; destroys the Vector
template< typename T >
Vector< T >::~Vector()
{
	if (ptr != nullptr)
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
const Vector< T > &Vector< T >::operator=(const Vector< T > &right)
{
	if (size != right.size){
		size = right.size;
		delete[] ptr;
		ptr = new T[size];
	}

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = right.ptr[i];


	return *this;
}



template< typename T >
bool Vector< T >::operator==(const Vector &right) const
{
	if (size != right.size)
		return false;

	iterator it1 = end();
	iterator it2 = right.end();

	for (--it1, --it2; it1 != begin(); --it1, --it2)
	if (*it1 != *it2)
		return false;

	return true;

}

template< typename T >
void Vector< T >::resize(unsigned int n)
{


	T *temp;
	temp = new T[n];

	for (int i = 0; i < n; i++)
		temp[i] = 0;

	for (unsigned int i = 0; i < size && i < n; i++)
		temp[i] = ptr[i];


	size = n;

	delete[] ptr;
	ptr = new T[size];

	for (int i = 0; i < size; i++)
		ptr[i] = 0;

	for (unsigned int i = 0; i < size; i++)
		ptr[i] = temp[i];


	delete[] temp;
}

template< typename T >
void Vector< T >::insert(T *position, const T val)
{
	if (size == 0){
		size = 1;
		ptr = new T[1];
		ptr[0] = val;
	}
	else
		resize(size + 1);

	for (unsigned int i = 1; i < size; i++){
		ptr[size - i] = ptr[size - i - 1];

	}
	ptr[0] = val;
}

