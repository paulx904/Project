#include <iostream>
using namespace std;

#ifndef LIST_NODE_H
#define LIST_NODE_H

template< typename T > class LinkedList;   // forward declare
template< typename T > class ListIterator; // forward declare
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
	ListIterator(ListNode< T > *p = 0); // default constructor
	~ListIterator(); // destructor
	T& operator*() const; // dereferencing operator
	T* operator->() const; // class member access operator
	ListIterator< T >& operator++(); // prefix increment operator
	//   ListIterator< T > operator++( int ); // postfix increment operator
	bool operator==(const ListIterator< T > &right) const; // equal to
	bool operator!=(const ListIterator< T > &right) const; // not equal to
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
bool ListIterator< T >::operator==(const ListIterator< T > &right) const
{
	return ptr == right.ptr;
}

// overloaded inequality operator
template< typename T >
bool ListIterator< T >::operator!=(const ListIterator< T > &right) const
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
	LinkedList(const LinkedList< T > &listToCopy);

	// Destroys all linked list elements, and deallocates all the storage allocated by the linked list.
	~LinkedList();

	// Copies all the elements from "right" into the linked list
	const LinkedList< T > &operator=(const LinkedList< T > &right);

	const ListIterator< T > begin() const; // Returns head

	const ListIterator< T > end() const; // Returns NULL

	// The linked list is extended by inserting a new element before the head of the linked list.
	iterator insertHead(const T val);

	// The linked list is extended by inserting a new element before the element at the specified position.
	// This effectively increases the list size by one.
	iterator insert(iterator position, const T val);

	// Removes from the linked list the element at the specified position.
	// This effectively reduces the list size by one.
	iterator erase(iterator position);

	//Returns a bool value indicating whether the linked list is empty, i.e. whether head == NULL.
	bool empty() const;

	// Removes all elements from the linked list (which are destroyed),
	void clear(); // and resets head and tail to null pointer
private:
	ListNode< T > *head; // pointer to the first element of linked list
	ListNode< T > *tail; // pointer to the last element of linked list
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
LinkedList< T >::LinkedList(const LinkedList< T > &listToCopy)
:head(listToCopy.head),
tail(listToCopy.tail)
{
}

// Destroys all linked list elements, and deallocates all the storage allocated by the linked list.
template< typename T >
LinkedList< T >::~LinkedList()
{
	//clear();
}

template< typename T >
const LinkedList< T >& LinkedList< T >::operator=(const LinkedList< T > &right)
{
	
	head = right.head;
	tail = right.tail;

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

// The linked list is extended by inserting a new element before the head of the linked list.
template< typename T >
ListIterator< T > LinkedList< T >::insertHead(const T val)
{
	ListNode< T > *newNode = new ListNode< T >;
	newNode->data = val;
	newNode->next = NULL;
	if (head == NULL) // empty list
		tail = newNode;
	else
		newNode->next = head;
	head = newNode;

	return iterator(newNode);
}

template< typename T >
ListIterator< T > LinkedList< T >::insert(iterator position, const T val)
{
	ListNode< T > *newNode = new ListNode< T >;
	newNode->data = val;
	newNode->next = NULL;
	ListNode< T > *temp = new ListNode< T >;

		if (head == NULL){   //耞琌
			tail = newNode;
			head = newNode;
		}
		else{
			for (temp = head; temp != NULL; temp = temp->next){
				if (temp->next == NULL){ //newNode程ソ薄猵
					temp->next = newNode;
					tail = newNode;
					break;
				}

				if (temp->next == position.ptr){
					newNode->next = temp->next;
					temp->next = newNode;
					break;
				}
			}
		}
		return iterator(newNode);
}

template< typename T >
ListIterator< T > LinkedList< T >::erase(iterator position)
{
	if (head != NULL) // the list is not empty
	{
		ListNode< T > *temp = new ListNode< T >;
		ListNode< T > *trail;
	
		for (temp = head;temp != NULL; temp = temp->next)
		if (temp->next == position.ptr){
			trail = temp->next;
			temp->next = position.ptr->next;
			delete trail;
			break;
		}
		return iterator(temp);
	}
	
}

// Removes all elements from the linked list (which are destroyed),
// and resets head and tail to null pointer
template< typename T >
void LinkedList< T >::clear()
{
	if (head != NULL) // the list is not empty
	{
		ListNode< T > *trail;
		ListNode< T > *ptr = head;

		while (ptr != NULL)
		{
			trail = ptr;
			ptr = ptr->next;
			delete trail;
		}

		head = NULL;
		tail = NULL;
	}
}

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// Represents a term of a polynomial
struct Term
{
	int coef;
	int expon;
};

// Polynomial class template definition
template< typename T >
class Polynomial
{
	// Overloaded stream insertion operator
	template< typename U >
	friend ostream &operator<<(ostream &output, const Polynomial< U > &a);
public:
	Polynomial(); // Constructs an empty polynomial, with no terms.

	// Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
	Polynomial(const Polynomial< T > &polynomialToCopy);

	~Polynomial(); // Destructor with empty body

	// Copies all the terms from "right" into the polynomial
	const Polynomial< T > operator=(const Polynomial< T > &right);

	void create(); // Creates a polynomial

	Polynomial< T > operator*(const Polynomial< T > &b); // Returns the product of two polynomials
private:
	T polynomial; // a polynomial

	void insert(Term termToInsert); // Inserts a new term into the polynomial

	bool zero() const; // Returns true if and only if polynomial is a zero polynomial
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
const Polynomial< T > Polynomial< T >::operator=(const Polynomial< T > &right)
{
	if (&right != this) // avoid self-assignment
		polynomial = right.polynomial;

	return *this; // enables x = y = z, for example
}

// Randomly generates a polynomial with "numTerms" terms
template< typename T >
void Polynomial< T >::create()
{
	int numTerms;
	cin >> numTerms;
	Term newTerm;
	for (int i = 0; i < numTerms; i++)
	{
		cin >> newTerm.coef >> newTerm.expon;
		insert(newTerm);
	}

}

// Multiplies two polynomials
template< typename T >
Polynomial< T > Polynomial< T >::operator*(const Polynomial< T > &b)
{
	Polynomial< T > product;
	Term newTerm;
	if (!zero() && !b.zero())
	for (LinkedList< Term >::iterator itA = polynomial.begin(); itA != polynomial.end(); ++itA)
	for (LinkedList< Term >::iterator itB = b.polynomial.begin(); itB != b.polynomial.end(); ++itB)
	{
		newTerm.coef = itA->coef * itB->coef;
		newTerm.expon = itA->expon + itB->expon;
		product.insert(newTerm);
	}
	return product;
}

template< typename T >
void Polynomial< T >::insert(Term termToInsert)
{
	if (termToInsert.coef != 0){   //玒计0杠ぃinsert
		if (polynomial.empty())    //狦㊣insertHead();
			polynomial.insertHead(termToInsert);
		else{
			LinkedList< Term >::iterator it = polynomial.begin();
			if (termToInsert.expon > it->expon)   //Ω计Τ程Ω计㊣insertHead();
				polynomial.insertHead(termToInsert);
			else
			{
				for (; it != polynomial.end(); ++it){
					if (termToInsert.expon == it->expon){ //Ω计单玒计
						it->coef += termToInsert.coef;
						if (it->coef == 0)            //璝玒计0㊣erase()
							polynomial.erase(it);
						break;
					}
					if (it->expon < termToInsert.expon){  //磅︽forloopт碝insert竚
						polynomial.insert(it, termToInsert);
						break;
					}
				}
				if (it == polynomial.end())   //insertソ薄猵
					polynomial.insert(it, termToInsert);
			}
		}
	}
}

// Returns true if and only if polynomial is a zero polynomial
template< typename T >
bool Polynomial< T >::zero() const
{
	return polynomial.empty();
}

// Overloaded stream insertion operator
template< typename T >
ostream &operator<<(ostream &output, const Polynomial< T > &a)
{
	if (a.zero())
	{
		output << 0 << endl;
		return output;
	}

	LinkedList< Term >::iterator it = a.polynomial.begin();

	output << it->coef;
	if (it->expon != 0)
		output << "x^" << it->expon;

	for (++it; it != a.polynomial.end(); ++it)
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

int main()
{
	Polynomial< LinkedList< Term > > multiplicand; // create an empty polynomial
	Polynomial< LinkedList< Term > > multiplier; // create an empty polynomial
	Polynomial< LinkedList< Term > > product; // create an empty polynomial
	multiplicand.create(); // create a polynomial with 3 terms
	multiplier.create(); // create a polynomial with 4 terms
	product = multiplicand * multiplier;
	cout << product;

	system("pause");
}
