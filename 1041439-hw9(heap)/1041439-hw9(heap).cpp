#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

// PriorityQueue class template definition
template< typename T >
class PriorityQueue
{
   template< typename U >
   friend ostream &operator<<( ostream &output, const PriorityQueue< U > &priorityQueue );
public:
   PriorityQueue(); // default constructor
   bool empty() const;
   size_t size() const;
   const T& top() const;
   void push( const T& val );
   void pop();
private:
   vector< T > heap;
}; // end class template PriorityQueue

#endif

// default constructor
template< typename T >
PriorityQueue< T >::PriorityQueue()
{
   heap.push_back( T() );
}

template< typename T >
bool PriorityQueue< T >::empty() const
{
   return ( heap.size() == 1 );
}

template< typename T >
size_t PriorityQueue< T >::size() const
{
   return heap.size() - 1;
}

template< typename T >
const T& PriorityQueue< T >::top() const
{
   return heap[ 1 ];
}

template< typename T >
void PriorityQueue< T >::push(const T& val)
{
	size_t i = 1;
	heap.resize(heap.size() + 1);

	for (; i < heap.size(); i++){
		if (heap[i] < val) {
			for (size_t j = size(); j > i; j--) {	//i以後的往後推一個
				heap[j].id = heap[j - 1].id;
				heap[j].time = heap[j - 1].time;
				heap[j].period = heap[j - 1].period;
			}
			heap[i].id = val.id;
			heap[i].time = val.time;
			heap[i].period = val.period;
			break;
		}
	}

	if (i == heap.size()) {		//比到最後一個都沒放進
		heap[size()].id = val.id;
		heap[size()].time = val.time;
		heap[size()].period = val.period;
	}
}

template< typename T >
void PriorityQueue< T >::pop()
{
	if (!empty()){
		for (size_t i = 1; i < size(); i++) {	//後面的往前補
			heap[i].id = heap[i + 1].id;
			heap[i].time = heap[i + 1].time;
			heap[i].period = heap[i + 1].period;
		}
		heap.resize(size()); 
	}
}

template< typename T >
ostream &operator<<( ostream &output, const PriorityQueue< T > &priorityQueue )
{
   typename vector< T >::const_iterator it;
   for( it = priorityQueue.heap.begin() + 1; it < priorityQueue.heap.end(); ++it )
      output << *it << endl;

   return output; // enables cout << x << y;
}

struct Node
{
   int id;
   int time;
   int period;

   bool operator<( const Node &rhs ) const
   {
      return time > rhs.time || ( time == rhs.time && id > rhs.id );
   }
};

int main()
{
   string command;
   PriorityQueue< Node > priorityQueue;

   while( cin >> command )
   {
      if( command == "#" )
         break;

      Node node;
      cin >> node.id >> node.period;
      node.time = node.period;

      priorityQueue.push( node );
   }

   int k;
   cin >> k;

   for( int i = 0; i < k; i++ )
   {
      Node node = priorityQueue.top();
      priorityQueue.pop();
      cout << node.id << endl;

      node.time += node.period;
      priorityQueue.push( node );
   }
   system("pause");
}
