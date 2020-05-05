// Member-function definitions for class template List

#include "List.h" // include definition of class template List

// Constructs an empty list container, with no elements.
template< typename T >
List< T >::List(unsigned int n)
:size(n)
{
	sentinal = new ListNode< T >;
	sentinal->data = T();
	sentinal->rlink = sentinal->llink = sentinal;

	List< T >::iterator newNode = nullptr;
	if (n > 0)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			newNode = new ListNode< T >;
			newNode->data = T();
			newNode->rlink = sentinal->rlink;
			sentinal->rlink->llink = newNode;
			sentinal->rlink = newNode;
		}
		newNode->llink = sentinal;
	}
}

template< typename T >
List< T >::List(const List< T > &listToCopy)
:size(listToCopy.size)
{
	sentinal = new ListNode< T >;
	sentinal->data = T();
	sentinal->rlink = sentinal->llink = sentinal;

	List< T >::iterator newNode = nullptr;
	if (size > 0)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			newNode = new ListNode< T >;
			newNode->data = T();
			newNode->rlink = sentinal->rlink;
			sentinal->rlink->llink = newNode;
			sentinal->rlink = newNode;
		}
		newNode->llink = sentinal;
	}

	iterator it1 = begin();
	iterator it2 = listToCopy.begin();

	for (; it2 != listToCopy.end(); it1 = it1->llink, it2 = it2->llink)
		it1->data = it2->data;
}

// Destroys all list container elements, and deallocates all the storage allocated by the list container.
template< typename T >
List< T >::~List()
{
	clear();
}

template< typename T >
bool List< T >::operator==(const List< T > &right) const
{

	if (size != right.size)
		return false;

	iterator it1 = begin();
	iterator it2 = right.begin();
	for (; it1 != end(); it1=it1->llink, it2=it2->llink)
	if (it1->data != it2->data)
		return false;
	return true;
}

template< typename T >
bool List< T >::operator!=(const List< T > &right) const
{
	return !(*this == right);
}

template< typename T >
ListNode< T >* List< T >::begin() const
{
	return sentinal->llink;
}

template< typename T >
ListNode< T >* List< T >::end() const
{
	return sentinal;
}

template< typename T >
ListNode< T >* List< T >::rbegin() const
{
	return sentinal->rlink;
}

template< typename T >
ListNode< T >* List< T >::rend() const
{
	return sentinal;
}

// Removes all elements from the list container (which are destroyed)
template< typename T >
void List< T >::clear()
{
	if (size != 0) // the list is not empty
	{
		while (sentinal->llink != sentinal)
		{
			sentinal->llink = sentinal->llink->llink;
			delete sentinal->llink->rlink;
		}

		sentinal->rlink = sentinal;
		size = 0;
	}
}

template< typename T >
unsigned int List< T >::getSize() const
{
	return size;
}

template< typename T >
const List< T > &List< T >::operator=(const List < T > &right)
{
	sentinal = new ListNode< T >;
	sentinal->data = T();
	sentinal->rlink = sentinal->llink = sentinal;

	List< T >::iterator newNode = nullptr;
	if (right.size > 0)
	{
		for (unsigned int i = 0; i < right.size; i++)
		{
			newNode = new ListNode< T >;
			newNode->data = T();
			newNode->rlink = sentinal->rlink;
			sentinal->rlink->llink = newNode;
			sentinal->rlink = newNode;
		}
		newNode->llink = sentinal;
	}

	iterator it1 = begin();
	iterator it2 = right.begin();

	for (; it2 != right.end(); it1 = it1->llink, it2 = it2->llink)
		it1->data = it2->data;

	size = right.size;

	return *this;
}

template< typename T >
void List< T >::resize(unsigned int n)
{
	if (n > 0 && n != size)
	{
		if (n > size){
			 List< T >::iterator newNode = nullptr;
			for (unsigned int i = size; i < n; i++)
			{
				newNode = new ListNode< T >;
				newNode->data = T();
				newNode->rlink = sentinal->rlink;
				sentinal->rlink->llink = newNode;
				sentinal->rlink = newNode;
			}
			newNode->llink = sentinal;
		}
		else{
			while (size - n > 0)
			{
				sentinal->rlink = sentinal->rlink->rlink;
				delete sentinal->rlink->llink;
				sentinal->rlink->llink = sentinal;
				size--;
			}
		}
		size = n;
	}
}