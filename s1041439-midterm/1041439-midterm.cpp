#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#ifndef LIST_NODE_H
#define LIST_NODE_H

// ListNode class template definition
template< typename T >
class ListNode
{
	template< typename U > friend class LinkedList;
	template< typename U > friend class ListIterator;
private:
	T data;
	ListNode< T > *next;
}; // end class template ListNode

#endif

// ListIterator class template definition
#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

// ListIterator class template definition
template< typename T >
class ListIterator
{
	template< typename U > friend class LinkedList;
public:
	ListIterator(ListNode< T > *p = NULL); // default constructor
	~ListIterator(); // destructor
	T& operator*() const; // dereferencing operator
	T* operator->() const; // class member access operator
	ListIterator< T >& operator++(); // prefix increment operator
	bool operator==(const ListIterator &right) const; // equal to
	bool operator!=(const ListIterator &right) const; // not equal to
private:
	ListNode< T > *ptr; // keep a pointer to LinkedList
}; // end class template ListIterator

#endif

// default constructor
template< typename T >
ListIterator< T >::ListIterator(ListNode< T > *p)
: ptr(p)
{
}

// destructor
template< typename T >
ListIterator< T >::~ListIterator()
{
}

// overloaded dereference operator
template< typename T >
T& ListIterator< T >::operator*() const
{
	return ptr->data;
}

// overloaded class member access operator
template< typename T >
T* ListIterator< T >::operator->() const
{
	return &(ptr->data);
}

// overloaded prefix increment operator
template< typename T >
ListIterator< T >& ListIterator< T >::operator++()
{
	ptr = ptr->next;
	return *this;
}

// overloaded equality operator
template< typename T >
bool ListIterator< T >::operator==(const ListIterator &right) const
{
	return ptr == right.ptr;
}

// overloaded inequality operator
template< typename T >
bool ListIterator< T >::operator!=(const ListIterator &right) const
{
	return ptr != right.ptr;
}

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// LinkedList class template definition
template< typename T >
class LinkedList
{
public:
	typedef ListIterator< T > iterator;
	LinkedList(); // Constructs an empty linked list, with no elements.

	// Constructs a linked list with a copy of each of the elements in listToCopy, in the same order.
	LinkedList(const LinkedList &listToCopy);

	// Destroys all linked list elements, and deallocates all the storage allocated by the linked list.
	~LinkedList();

	// Copies all the elements from "right" into the linked list
	const LinkedList< T > &operator=(const LinkedList &right);

	const ListIterator< T > begin() const; // Returns head

	const ListIterator< T > end() const; // Returns NULL

	//Returns a bool value indicating whether the linked list is empty, i.e. whether head == NULL.
	bool empty() const;

	// Inserts a new element at the end of the linked list, right after its current last element.
	void push_back(const T val);
private:
	ListNode< T > *head; // pointer to the first element of linked list
	ListNode< T > *tail; // pointer to the last element of linked list

	// Removes all elements from the linked list (which are destroyed),
	void clear(); // and resets head and tail to null pointer
}; // end class template LinkedList

#endif

// Constructs an empty linked list, with no elements.
template< typename T >
LinkedList< T >::LinkedList()
: head(NULL),
tail(NULL)
{
}

template< typename T >
LinkedList< T >::LinkedList(const LinkedList &listToCopy)
: head(listToCopy.head),
tail(listToCopy.tail)
{
}

// Destroys all linked list elements, and deallocates all the storage allocated by the linked list.
template< typename T >
LinkedList< T >::~LinkedList()
{
	/*clear();*/
}

template< typename T >
const LinkedList< T > &LinkedList< T >::operator=(const LinkedList &right)
{
	if (&right != this){
		head = right.head;
		tail = right.tail;
	}
	return *this;
}

template< typename T >
const ListIterator< T > LinkedList< T >::begin() const
{
	return ListIterator< T >(head);
}

template< typename T >
const ListIterator< T > LinkedList< T >::end() const
{
	return ListIterator< T >(NULL);
}

//Returns a bool value indicating whether the linked list is empty.
template< typename T >
bool LinkedList< T >::empty() const
{
	return (head == NULL);
}

template< typename T >
void LinkedList< T >::push_back(const T val)
{
	if (val.coef != 0){
		ListNode< T > *newNode = new ListNode< T >;
		newNode->data.expon = val.expon;
		newNode->data.coef = val.coef;

		if (empty()){
			head = newNode;
			tail = newNode;
			newNode->next = NULL;
		}
		else{
			typename LinkedList< T >::iterator it = begin();
			if (it->expon < val.expon){
				newNode->next = head;
				head = newNode;
			}
			else{
				for (; it != end(); ++it){
					if (it->expon == val.expon){
						it->coef += val.coef;
						if (it->coef == 0){
							it->expon = '\0';
						}
						break;
					}
					if (it.ptr->next != NULL)
					if (it.ptr->next->data.expon < val.expon){
						newNode->next = it.ptr->next;
						it.ptr->next = newNode;
						break;
					}
				}
				if (it == end()){
					tail->next = newNode;
					newNode->next = NULL;
					tail = newNode;
				}
			}
		}
	}
}

template< typename T >
void LinkedList< T >::clear()
{
	if (!empty()){
		tail->next = NULL;
		ListNode< T > *ptr;
		while (head != NULL){
			ptr = head;
			head = head->next;
			ptr->next = NULL;
			ptr = NULL;
		}
		tail = NULL;
		head = NULL;
	}
}

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// Polynomial class template definition
template< typename T >
class Polynomial
{
	// Overloaded stream extraction operator
	template< typename U >
	friend istream &operator>>(istream &input, Polynomial< U > &right);

	// Overloaded stream insertion operator
	template< typename U >
	friend ostream &operator<<(ostream &output, const Polynomial< U > &right);
public:
	Polynomial(); // Constructs an empty polynomial, with no terms.

	// Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
	Polynomial(const Polynomial &polynomialToCopy);

	~Polynomial(); // Destructor with empty body

	// Copies all the terms from "right" into the polynomial
	const Polynomial operator=(const Polynomial &right);

	// Returns the quotient after polynomial division
	const Polynomial operator/(const Polynomial &divisor) const;

	// Returns the remainder after polynomial division
	const Polynomial operator%(const Polynomial &divisor) const;

	bool zero() const; // Returns true if and only if polynomial is a zero polynomial
private:
	LinkedList< T > polynomial; // a polynomial

	// Returns the difference of two polynomials
	const Polynomial operator-(const Polynomial &subtrahend) const;

	// Returns the product of two polynomials where the second consists of one term
	const Polynomial operator*(const T &term) const;

	// Attaches a new term to the polynomial
	void attach(const int coefficient, const int exponent);

	// Returns 0 if x == y; returns -1 if x < y; and returns 1 if x > y
	int compare(const int x, const int y) const;

	int degree() const; // Returns the highest degree of polynomial's terms
}; // end class template Polynomial

#endif

// Constructs an empty polynomial, with no terms.
template< typename T >
Polynomial< T >::Polynomial()
: polynomial()
{
}

// Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
template< typename T >
Polynomial< T >::Polynomial(const Polynomial &polynomialToCopy)
: polynomial(polynomialToCopy.polynomial)
{
}

// Destructor with empty body
template< typename T >
Polynomial< T >::~Polynomial()
{
}

// Copies all the terms from "right" into the polynomial
template< typename T >
const Polynomial< T > Polynomial< T >::operator=(const Polynomial &right)
{
	if (&right != this) // avoid self-assignment
		polynomial = right.polynomial;

	return *this; // enables x = y = z, for example
}

template< typename T >
const Polynomial< T > Polynomial< T >::operator/(const Polynomial &divisor) const
{
	Polynomial< T > quotient;
	Polynomial< T > q;
	Polynomial< T > temp(*this);
	T newTerm;

	while (temp.degree() >= divisor.degree()){
		newTerm.coef = temp.polynomial.begin()->coef / divisor.polynomial.begin()->coef;
		newTerm.expon = (temp.polynomial.begin()->expon) - (divisor.polynomial.begin()->expon);
		q.polynomial.push_back(newTerm);
		temp = temp - (divisor*newTerm);
	}
	for (typename LinkedList< T >::iterator it = q.polynomial.begin(); it != q.polynomial.end(); ++it)
		quotient.attach(it->coef, it->expon);
	return quotient;
}

template< typename T >
const Polynomial< T > Polynomial< T >::operator%(const Polynomial &divisor) const
{
	Polynomial< T > quotient;
	Polynomial< T > remainder;
	Polynomial< T > temp(*this);
	T newTerm;

	while (temp.degree() >= divisor.degree()){
		newTerm.coef = temp.polynomial.begin()->coef / divisor.polynomial.begin()->coef;
		newTerm.expon = (temp.polynomial.begin()->expon) - (divisor.polynomial.begin()->expon);
		quotient.polynomial.push_back(newTerm);
		temp = temp - (divisor*newTerm);
	}
	/*if (temp.degree() < divisor.degree()){
		for (typename LinkedList< T >::iterator it = divisor.polynomial.begin(); it != divisor.polynomial.end(); ++it)
			remainder.attach(it->coef, it->expon);
	}
	else*/
	for (typename LinkedList< T >::iterator it = temp.polynomial.begin(); it != temp.polynomial.end(); ++it)
		remainder.attach(it->coef, it->expon);
	return remainder;
}


template< typename T >
const Polynomial< T > Polynomial< T >::operator-(const Polynomial &subtrahend) const
{
	Polynomial< T > different;
	typename LinkedList< T >::iterator it1 = polynomial.begin();
	typename LinkedList< T >::iterator it2 = subtrahend.polynomial.begin();
	T newTerm;

/*if*/ while (it2 != subtrahend.polynomial.end() && it1 != polynomial.end()){
			if (it1->expon == it2->expon){
				newTerm.coef = it1->coef - it2->coef;
				newTerm.expon = it1->expon;
				++it1;
				++it2;
			}
			else if (it1->expon > it2->expon){
				newTerm.coef = it1->coef;
				newTerm.expon = it1->expon;
				++it1;
			}
			else if (it1->expon < it2->expon){
				newTerm.coef = -it2->coef;
				newTerm.expon = it2->expon;
				++it2;
			}
			if (newTerm.coef != 0)
				different.polynomial.push_back(newTerm);
		}

		while (it2 != subtrahend.polynomial.end()){
			newTerm.expon = it2->expon;
			newTerm.coef = -it2->coef;
			++it2;
			different.polynomial.push_back(newTerm);
		}
		while (it1 != polynomial.end()){
			newTerm.expon = it1->expon;
			newTerm.coef = it1->coef;
			++it1;
			different.polynomial.push_back(newTerm);
		}
	return different;
}

// Returns the product of two polynomials where the second consists of one term
template< typename T >
const Polynomial< T > Polynomial< T >::operator*(const T &term) const
{
	Polynomial< T > product;
	if (!zero())
	for (typename LinkedList< T >::iterator it = polynomial.begin(); it != polynomial.end(); ++it)
	{
		T newTerm;
		newTerm.coef = it->coef * term.coef;
		newTerm.expon = it->expon + term.expon;
		product.polynomial.push_back(newTerm);
	}

	return product;
}

// Returns 0 if x == y; returns -1 if x < y; and returns 1 if x > y.
template< typename T >
int Polynomial< T >::compare(const int x, const int y) const
{
	if (x < y)
		return -1;
	else if (x == y)
		return 0;
	else
		return 1;
}

// Attaches a new term to the polynomial
template< typename T >
void Polynomial< T >::attach(const int coefficient, const int exponent)
{
	T tempTerm;
	tempTerm.coef = coefficient;
	tempTerm.expon = exponent;
	polynomial.push_back(tempTerm);
}

// Returns the highest degree of polynomial's terms
template< typename T >
int Polynomial< T >::degree() const
{
	if (polynomial.empty())
		return -1;
	else
		return polynomial.begin()->expon;
}

// Returns true if and only if polynomial is a zero polynomial
template< typename T >
bool Polynomial< T >::zero() const
{
	return polynomial.empty();
}

// Overloaded stream extraction operator
template< typename T >
istream &operator>>(istream &input, Polynomial< T > &right)
{
	int numTerms;
	input >> numTerms;
	T newTerm;
	for (int i = 0; i < numTerms; i++)
	{
		input >> newTerm.coef >> newTerm.expon;
		right.polynomial.push_back(newTerm);
	}
	return input; // enables cin >> a >> b >> c;
}

// Overloaded stream insertion operator
template< typename T >
ostream &operator<<(ostream &output, const Polynomial< T > &right)
{
	if (right.zero())
	{
		output << 0 << endl;
		return output;
	}

	typename LinkedList< T >::iterator it = right.polynomial.begin();

	output << it->coef;
	if (it->expon != 0)
		output << "x^" << it->expon;

	for (++it; it != right.polynomial.end(); ++it)
	{
		if (it->coef > 0)
			output << " + " << it->coef;
		else
			output << " - " << -it->coef;

		if (it->expon != 0)
			output << "x^" << it->expon;
	}

	output << endl;

	return output; // enables cout << x << y;
} // end function operator<<

// Represents a term of a polynomial
struct Term
{
	int coef;
	int expon;
};

int main()
{
	Polynomial< Term > dividend; // create a zero polynomial
	cin >> dividend;

	Polynomial< Term > divisor; // create a zero polynomial
	cin >> divisor;

	if (divisor.zero())
		cout << "Divide by zero error encountered!\n";
	else
	{
		Polynomial< Term > quotient; // create a zero polynomial
		quotient = dividend / divisor;
		cout << quotient;

		Polynomial< Term > remainder; // create a zero polynomial
		remainder = dividend % divisor;
		cout << remainder;
	}

	system("pause");
}
