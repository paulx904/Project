#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

enum Color{ Red, Black };

template< typename T1, typename T2 >
struct Pair
{
	Pair()
	: first(T1()),
	second(T2())
	{
	}

	Pair(const T1 a, const T2 b)
		: first(a),
		second(b)
	{
	}

	T1 first;
	T2 second;
};

#ifndef TREE_NODE_H
#define TREE_NODE_H

// TreeNode class template definition
template< typename Key, typename T >
class TreeNode
{
	template< typename K, typename U > friend class Map;
	template< typename K, typename U > friend class MapIterator;
private:
	Pair< Key, T > myval;
	TreeNode *left; // left subtree, or smallest element if head
	TreeNode *parent; // parent, or root of tree if head
	TreeNode *right; // right subtree, or largest element if head
	Color color; // red or black, black if head
	bool isNil; // true only if head (also nil) node
}; // end class template TreeNode

#endif

// MapIterator class template definition
#ifndef MAP_ITERATOR_H
#define MAP_ITERATOR_H

// MapIterator class template definition
template< typename Key, typename T >
class MapIterator
{
	template< typename K, typename U > friend class Map;
public:
	MapIterator(TreeNode< Key, T > *p = NULL); // default constructor
	~MapIterator(); // destructor
	Pair< Key, T >& operator*() const; // dereferencing operator
	Pair< Key, T >* operator->() const; // class member access operator
	MapIterator< Key, T >& operator++(); // prefix increment operator
	bool operator==(const MapIterator &right) const; // equal to
	bool operator!=(const MapIterator &right) const; // not equal to
private:
	TreeNode< Key, T > *ptr; // keep a pointer to Map
}; // end class template MapIterator

#endif

// default constructor
template< typename Key, typename T >
MapIterator< Key, T >::MapIterator(TreeNode< Key, T > *p)
: ptr(p)
{
}

// destructor
template< typename Key, typename T >
MapIterator< Key, T >::~MapIterator()
{
}

// overloaded dereference operator
template< typename Key, typename T >
Pair< Key, T >& MapIterator< Key, T >::operator*() const
{
	return ptr->myval;
}

// overloaded class member access operator
template< typename Key, typename T >
Pair< Key, T >* MapIterator< Key, T >::operator->() const
{
	return &(ptr->myval);
}

// overloaded equality operator
template< typename Key, typename T >
bool MapIterator< Key, T >::operator==(const MapIterator &right) const
{
	return ptr == right.ptr;
}

// overloaded inequality operator
template< typename Key, typename T >
bool MapIterator< Key, T >::operator!=(const MapIterator &right) const
{
	return ptr != right.ptr;
}

#ifndef MAP_H
#define MAP_H

// Map class template definition
template< typename Key, typename T >
class Map
{
public:
	typedef MapIterator< Key, T > iterator;

	Map(); // Constructs an empty map object, with no elements.

	// Constructs a map object with a copy of each of the elements in mapToCopy, in the same structure.
	Map(const Map &mapToCopy);

	// Destroys all map object elements, and deallocates all the storage allocated by the map object.
	~Map();

	// Copies all the elements from "right" into the map object
	const Map< Key, T > &operator=(const Map &right);

	unsigned int size() const; // Returns mySize

	const iterator begin() const; // Returns the address of the node with smallest key

	const iterator end() const; // Returns myHead

	// Returns a bool value indicating whether the map object is empty, i.e. whether mySize == 0.
	bool empty() const;

	const iterator find(const Key& k) const;

	Pair< iterator, bool > insert(const Pair< Key, T >& val);

	T& operator[](const Key& k);

	bool correct();

	//   void preorder();
private:
	TreeNode< Key, T > *myHead; // pointer to head node
	unsigned int mySize; // number of elements ( not include head node )

	TreeNode< Key, T >* copy(TreeNode< Key, T > *node, TreeNode< Key, T > *parent);

	// Removes all elements from the map object (which are destroyed), except the head node
	void clear();
	void clearBase(TreeNode< Key, T > *ptr);

	void reBalance(TreeNode< Key, T > *node);
	void LLbRotation(TreeNode< Key, T > *node);
	void LRbRotation(TreeNode< Key, T > *node);
	void RLbRotation(TreeNode< Key, T > *node);
	void RRbRotation(TreeNode< Key, T > *node);

	bool correctBase(TreeNode< Key, T > *node, int numBlackNodes1, int numBlackNodes2);
	//   void preorderBase( TreeNode< Key, T > *node );
}; // end class template Map

#endif

// Constructs an empty map, with head node.
template< typename Key, typename T >
Map< Key, T >::Map()
: myHead(new TreeNode< Key, T >),
mySize(0)
{
	myHead->left = NULL;
	myHead->parent = NULL;
	myHead->right = NULL;
	myHead->color = Black;
	myHead->isNil = true;
}

// Constructs a map object with a copy of each of the elements in listToCopy, in the same order.
template< typename Key, typename T >
Map< Key, T >::Map(const Map< Key, T > &mapToCopy)
: myHead(new TreeNode< Key, T >),
mySize(mapToCopy.mySize)
{
	myHead->left = NULL;
	myHead->parent = NULL;
	myHead->right = NULL;
	myHead->color = Black;
	myHead->isNil = true;
	if (mapToCopy.mySize > 0)
		myHead->left = copy(mapToCopy.myHead->left, myHead);
}

// Destroys all map object elements, and deallocates all the storage allocated by the map object.
template< typename Key, typename T >
Map< Key, T >::~Map()
{
	clear();
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename Key, typename T >
const Map< Key, T > &Map< Key, T >::operator=(const Map< Key, T > &right)
{
	if (&right != this) // avoid self-assignment
	{
		if (mySize > 0) // the LHS list is not empty
			clear();

		if (right.mySize > 0) // the RHS list is not empty
			myHead->left = copy(right.myHead->left, myHead);
	}

	return *this; // enables x = y = z, for example
} // end function operator=

template< typename Key, typename T >
unsigned int Map< Key, T >::size() const
{
	return mySize;
}

template< typename Key, typename T >
const MapIterator< Key, T > Map< Key, T >::begin() const
{
	TreeNode< Key, T > *node = myHead->left;
	while (node->left != myHead)
		node = node->left;
	return MapIterator< Key, T >(node);
}

template< typename Key, typename T >
const MapIterator< Key, T > Map< Key, T >::end() const
{
	return MapIterator< Key, T >(myHead);
}

//Returns a bool value indicating whether the map object is empty.
template< typename Key, typename T >
bool Map< Key, T >::empty() const
{
	return (mySize == 0);
}

template< typename Key, typename T >
T& Map< Key, T >::operator[](const Key& k)
{
	return (insert(Pair< Key, T >(k, T())).first)->second;
}

// Removes all elements from the map object (which are destroyed), except the head node
template< typename Key, typename T >
void Map< Key, T >::clear()
{
	clearBase(myHead->left);
	myHead->left = myHead;
}

template< typename Key, typename T >
void Map< Key, T >::clearBase(TreeNode< Key, T > *node)
{
	if (!node->isNil)
	{
		clearBase(node->left);
		clearBase(node->right);
		delete node;
	}
}

template< typename Key, typename T >
bool Map< Key, T >::correct()
{
	int numBlackNodes1 = 0;
	for (TreeNode< Key, T > *node = myHead->left; node != myHead; node = node->left)
	if (node->color == Black)
		numBlackNodes1++;

	int numBlackNodes2 = 0;
	if ((myHead->left)->color == Black)
		return correctBase(myHead->left, numBlackNodes1, numBlackNodes2);
	else
		return false;
}

template< typename Key, typename T >
bool Map< Key, T >::correctBase(TreeNode< Key, T > *node, int numBlackNodes1, int numBlackNodes2)
{
	if (node == myHead)
		return (numBlackNodes1 == numBlackNodes2);
	else
	{
		if ((node->left != myHead && (node->left)->myval.first > node->myval.first) ||
			(node->right != myHead && node->myval.first > (node->right)->myval.first))
			return false;
		else
		if (node->color == Black)
			return correctBase(node->left, numBlackNodes1, numBlackNodes2 + 1) &&
			correctBase(node->right, numBlackNodes1, numBlackNodes2 + 1);
		else
			return (node->left)->color == Black && (node->right)->color == Black &&
			correctBase(node->left, numBlackNodes1, numBlackNodes2) &&
			correctBase(node->right, numBlackNodes1, numBlackNodes2);
	}
}

struct Value
{
	Value(int c = 0, int o = 0)
	{
		count = c;
		order = o;
	}

	int count;
	int order;
};

void bubbleSort(vector< Pair< int, Value > > &sortedIntegers);

int main()
{
	Map< int, Value > uniqueIntegers;
	int key, order = 1;
	while (cin >> key)
	if (uniqueIntegers.find(key) == uniqueIntegers.end())
		uniqueIntegers[key] = Value(1, order++);
	else
		++(uniqueIntegers[key].count);

	if (!uniqueIntegers.correct())
		cout << "\nIncorrect Red-Black Tree\n\n";

	vector< Pair< int, Value > > sortedIntegers;
	Map< int, Value >::iterator it1;
	for (it1 = uniqueIntegers.begin(); it1 != uniqueIntegers.end(); ++it1)
		sortedIntegers.push_back(*it1);

	bubbleSort(sortedIntegers);

	vector< Pair< int, Value > >::iterator it2;
	for (it2 = sortedIntegers.begin(); it2 != sortedIntegers.end(); ++it2)
		cout << it2->first << ' ' << it2->second.count << endl;

	system("pause");
}

void bubbleSort(vector< Pair< int, Value > > &sortedIntegers)
{
	Pair< int, Value > buffer;
	for (int pass = sortedIntegers.size() - 1; pass > 0; pass--)
	for (int i = 0; i < pass; i++)
	if (sortedIntegers[i].second.order > sortedIntegers[i + 1].second.order)
	{
		buffer = sortedIntegers[i];
		sortedIntegers[i] = sortedIntegers[i + 1];
		sortedIntegers[i + 1] = buffer;
	}
}

template< typename Key, typename T >
void Map< Key, T >::reBalance(TreeNode< Key, T > *node)
{
	TreeNode< Key, T > *u = new TreeNode< Key, T >;
	TreeNode< Key, T > *Pu = new TreeNode< Key, T >;
	TreeNode< Key, T > *Gu = new TreeNode< Key, T >;
	u = node; Pu = u->parent; Gu = u->parent->parent;


	if (Gu->left->color == Red && Gu->right->color == Red)	// GU的左右都是紅色
	{
		Gu->left->color = Black;
		Gu->right->color = Black;
		if (Gu != myHead->left)
			Gu->color = Red;
	}
	else if (Pu->right == u && Gu->right == Pu)
		RRbRotation(u);
	else if (Pu->left == u && Gu->left == Pu)
		LLbRotation(u);
	else if (Pu->left == u && Gu->right == Pu)
		RLbRotation(u);
	else if (Pu->right == u && Gu->left == Pu)
		LRbRotation(u);

	if (!correct())
	{
		reBalance(Gu);	// 還是不對就往Gu以上繼續修正
	}
}

template< typename Key, typename T >
void Map< Key, T >::LLbRotation(TreeNode< Key, T > *node)
{
	TreeNode< Key, T > *u = new TreeNode< Key, T >;
	TreeNode< Key, T > *Pu = new TreeNode< Key, T >;
	TreeNode< Key, T > *Gu = new TreeNode< Key, T >;
	u = node; Pu = u->parent; Gu = u->parent->parent;

	Pu->parent = Gu->parent;	//旋轉
	Gu->left = Pu->right;
	Pu->right->parent = Gu;
	Pu->right = Gu;
	Gu->parent = Pu;

	if (Pu->parent == myHead)
		Pu->parent->left = Pu;
	else{
		if (Pu->myval.first < Pu->parent->myval.first)		//如果parent不是myHead就判斷大小接上去
			Pu->parent->left = Pu;
		else
			Pu->parent->right = Pu;
	}
	Gu->color = Red;
	Pu->color = Black;
}

template< typename Key, typename T >
void Map< Key, T >::LRbRotation(TreeNode< Key, T > *node)
{
	TreeNode< Key, T > *u = new TreeNode< Key, T >;
	TreeNode< Key, T > *Pu = new TreeNode< Key, T >;
	TreeNode< Key, T > *Gu = new TreeNode< Key, T >;
	u = node; Pu = u->parent; Gu = u->parent->parent;

	u->parent = Gu->parent;		//拉上去
	Gu->left = u->right;
	u->right->parent = Gu;
	Pu->right = u->left;
	u->left->parent = Pu;

	u->right = Gu;
	u->left = Pu;
	Gu->parent = u;
	Pu->parent = u;

	if (u->parent == myHead)
		u->parent->left = u;
	else{
		if (u->myval.first < u->parent->myval.first)		//如果parent不是myHead就判斷大小接上去
			u->parent->left = u;
		else
			u->parent->right = u;
	}
	Gu->color = Red;
	u->color = Black;
}

template< typename Key, typename T >
void Map< Key, T >::RRbRotation(TreeNode< Key, T > *node)
{
	TreeNode< Key, T > *u = new TreeNode< Key, T >;
	TreeNode< Key, T > *Pu = new TreeNode< Key, T >;
	TreeNode< Key, T > *Gu = new TreeNode< Key, T >;
	u = node; Pu = u->parent; Gu = u->parent->parent;

	Pu->parent = Gu->parent;	//旋轉
	Gu->right = Pu->left;
	Pu->left->parent = Gu;
	Pu->left = Gu;
	Gu->parent = Pu;

	if (Pu->parent == myHead)
		Pu->parent->left = Pu;
	else{
		if (Pu->myval.first < Pu->parent->myval.first)		////如果parent不是myHead就判斷大小接上去
			Pu->parent->left = Pu;
		else
			Pu->parent->right = Pu;
	}
	Gu->color = Red;
	Pu->color = Black;
}

template< typename Key, typename T >
void Map< Key, T >::RLbRotation(TreeNode< Key, T > *node)
{
	TreeNode< Key, T > *u = new TreeNode< Key, T >;
	TreeNode< Key, T > *Pu = new TreeNode< Key, T >;
	TreeNode< Key, T > *Gu = new TreeNode< Key, T >;
	u = node; Pu = u->parent; Gu = u->parent->parent;

	u->parent = Gu->parent;		//拉上去
	Gu->right = u->left;
	u->left->parent = Gu;
	Pu->left = u->right;
	u->right->parent = Pu;

	u->right = Pu;
	u->left = Gu;
	Gu->parent = u;
	Pu->parent = u;

	if (u->parent == myHead)
		u->parent->left = u;
	else{
		if (u->myval.first < u->parent->myval.first)	////如果parent不是myHead就判斷大小接上去
			u->parent->left = u;
		else
			u->parent->right = u;
	}
	Gu->color = Red;
	u->color = Black;
}

template< typename Key, typename T >
Pair< MapIterator< Key, T >, bool > Map< Key, T >::insert(const Pair< Key, T >& val)
{
	TreeNode< Key, T > *newNode = new TreeNode< Key, T >;
	newNode->color = Red;
	newNode->isNil = false;
	newNode->myval = val;
	newNode->left = newNode->right = myHead;
	mySize++;
	Pair< MapIterator< Key, T >, bool > n1;

	TreeNode< Key, T > *temp;
	temp = myHead;

	if (temp->left == NULL){	//如果為空
		myHead->left = newNode;
		newNode->parent = myHead;
		newNode->color = Black;
		MapIterator< Key, T > n1(newNode);
		return Pair< MapIterator< Key, T >, bool >(n1, true);
	}

	temp = temp->left;	//走到root

	while (true){
		if (temp->myval.first == newNode->myval.first){	 //找到一樣的
			MapIterator< Key, T > n1(temp);
			return Pair< MapIterator< Key, T >, bool >(n1, false);
		}
		else if (newNode->myval.first < temp->myval.first){	 //比較小
			if (temp->left == myHead){	//空就插入
				temp->left = newNode;
				newNode->parent = temp;
				temp = temp->left;
				break;
			}
			temp = temp->left;
		}
		else if (newNode->myval.first > temp->myval.first){  //比較大
			if (temp->right == myHead){	 //空就插入
				temp->right = newNode;
				newNode->parent = temp;
				temp = temp->right;
				break;
			}
			temp = temp->right;
		}
	}
	if (size() != 0 && !correct())	//顏色不對
		reBalance(temp);

	MapIterator< Key, T > n2(newNode);
	return Pair< MapIterator< Key, T >, bool >(n2, true);
}

template< typename Key, typename T >
const MapIterator< Key, T > Map< Key, T >::find(const Key& k) const
{
	MapIterator< Key, T > it = myHead->left;

	while (it != NULL && it != end()){
		if (it->first == k)	//找到
			return it;
		else if (k < it->first)	//比較小往左走
			it = it.ptr->left;
		else if (k > it->first)	//比較大往右走
			it = it.ptr->right;
	}
	return myHead;
}

template< typename Key, typename T >
TreeNode< Key, T >*Map< Key, T >::copy(TreeNode< Key, T > *node, TreeNode< Key, T > *parent)
{
	TreeNode< Key, T > *newNode = new TreeNode< Key, T >;
	newNode->myval->first = node->myval->first;
	newNode->myval->second = node->myval->second;

	newNode->left = copy(node->left, newNode);	//接左邊	
	newNode->right = copy(node->right, newNode);	//接右邊

	newNode->parent = parent;

	return newNode;
}

template< typename Key, typename T >
MapIterator< Key, T >& MapIterator< Key, T >::operator++()
{
	if (ptr->right->isNil){				//如果沒有右邊
		int temp = ptr->myval.first;

		while (!ptr->parent->isNil && temp > ptr->parent->myval.first){		//一直往上找到比較大的
			ptr = ptr->parent;
		}
		ptr = ptr->parent;
		return *this;
	}
	if (!ptr->right->isNil){		   //如果有右邊
		ptr = ptr->right;

		while (!ptr->left->isNil)	   //往右一個之後找最左邊
			ptr = ptr->left;
		return *this;
	}
}