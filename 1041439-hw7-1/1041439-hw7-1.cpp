// Uses "selection sort" algorithm to sort the sequence data[] in ascending order.
#include<iostream>
#include<iomanip>
#include<ctime>
using namespace::std;

// recursively Print all elements in the array intArray
void recursivePrintArray(const int intArray[], int last);

// recursive function to sort the array data using the Selection sort algorithm
void recursiveSelectionSort(int data[], int last);

// find largest element and put it in last position
void putMaxInLast(int data[], int last);

// function main begins program execution

int main()
{
	//   srand( static_cast< int >( time(0) ) );

	unsigned int seed;
	cout << "Enter seed: ";
	cin >> seed;
	cout << endl;
	srand(seed);

	
	int number;
	cout << "Enter the number of integers to be sorted: ";
	cin >> number;

	int *data = new int[number];

	// fill array with random numbers between 1-MAXRANGE
	for (int i = 0; i < number; i++)
		data[i] = 1 + rand() % 100;

	cout << "\nUnsorted array is:\n";
	recursivePrintArray(data, number - 1); // display unsorted array

	recursiveSelectionSort(data, number - 1);

	cout << "\n\nSorted array is:\n";
	recursivePrintArray(data, number - 1); // display sorted array
	cout << endl << endl;

	delete[] data;

	system("pause");
} // end function main

void recursivePrintArray(const int data[], int last)
{
	if (last > 0){
		cout << "  " << data[last];
		last--;
		recursivePrintArray(data, last);
	}
	else
		cout << "  " << data[last];

}

void recursiveSelectionSort(int data[], int last)
{
	static int i = 0, j = i + 1, max;
	if (i <= last){
		max = i;
		for (int j = i + 1; j <= last; j++){
			if (data[j] > data[max]){
				max = j;
			}
		}
		putMaxInLast(data, max);
		i++;
        recursiveSelectionSort(data, last);
	}
}


void putMaxInLast(int data[], int last)
{
	int variable;
	static int k = 0;
	variable = data[k];
	data[k] = data[last];
	data[last] = variable;
	k++;
}