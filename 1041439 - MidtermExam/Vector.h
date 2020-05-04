#ifndef VECTOR_H
#define VECTOR_H

// Vector class template definition
template< typename T >
class Vector
{
public:
	typedef T* iterator;
	typedef T* reverse_iterator;

	Vector(unsigned int n = 0); // Constructor; Constructs a vector with n elements.

	// Copy constructor; Constructs a vector with a copy of each of the elements in vectorToCopy.
	Vector(const Vector< T > &vectorToCopy);

	~Vector(); // Destructor; Destroys the vector.

	const Vector< T > &operator=(const Vector< T > &right); // assignment operator

	bool operator==(const Vector &right) const; // equal to

	// Returns a pointer pointing to the first element in the vector.
	// If the vector is empty, the returned pointer shall not be dereferenced.
	iterator begin() const;

	// Returns an pointer pointing to the past-the-end element in the vector.
	// The past-the-end element is the theoretical element that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	iterator end() const;

	reverse_iterator rbegin() const; // Returns a pointer pointing to the last element in the vector.

	// Returns a pointer pointing to the theoretical element preceding the first element in the vector.
	reverse_iterator rend() const;

	unsigned int getSize() const; // Returns the number of elements in the vector.

	// Resizes the vector so that it contains n elements.
	// If n is smaller than the current vector size,
	// the content is reduced to its first n elements, removing those beyond.
	// If n is greater than the current vector size,
	// the content is expanded by inserting at the end as many elements as needed to reach a size of n.
	// The new elements are initialized as 0.
	void resize(unsigned int n);

	// The vector is extended by inserting a new element before the element at position,   
	// effectively increasing the container size by one.   
	// This causes an automatic reallocation of the allocated storage space.   
	// Relocates all the elements that were after position to their new positions.
	void insert(T *position, const T val);

private:
	unsigned int size; // the number of elements in the vector
	T *ptr; // points to a dynamically allocated array
}; // end class template Vector

#endif