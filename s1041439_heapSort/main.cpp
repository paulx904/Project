#include <iostream>
#include <sstream>
#include <iomanip> 
#include<cmath> 
using namespace std;

const int MAX_SIZE = 100;

int power(int n){
	while (n > 0){
		int i = 0;
		while (n >= pow(2, i)){
			if (n == pow(2, i))
				return i;
			else i++;
		}
		n++;
	}
	return 0;
}

void print(int input[], int index){
	index++;
	int temp, count = 1, i = 1, line, width = 0;

	line = power(index - 1) * 2 + 1;
	temp = count;
	while (true){
		temp = count;
		cout << setw(line - width);
		width++;
		while (--temp >= 0){
			if (i >= index)
				break;
			cout << input[i] << "  ";
			i++;
		}
		if (i >= index)
			break;
		cout << endl << setw(line - width);
		width++;
		temp = count;
		while (--temp >= 0){
			cout << "/" << " \\ ";
		}
		cout << endl;
		count *= 2;
		if (i >= index)
			break;
	}
	cout << endl;
}

void MaxHeapify(int input[], int i, int n)
{
	int l, r, largest;  
	l = 2 * i;
	r = 2 * i + 1;

	if (l <= n && input[l] > input[i]) largest = l;
	else largest = i;

	if (r <= n && input[r] > input[largest])
		largest = r;
	if (largest != i) {                         
		swap(input[largest], input[i]);         
		MaxHeapify(input, largest, n);        
	}
}
void BuildMaxHeap(int input[], int n)
{
	int i;
	for (i = n / 2; i >= 1; i--)
		MaxHeapify(input, i, n);
}
void HeapSort(int input[], int n)
{
	int size = n;
	for (int i = n; i >= 2; i--)
	{
		int temp = input[i];
		input[i] = input[1];
		input[1] = temp;
		n--;
		MaxHeapify(input, 1, n);
		cout << "Sorted numbers: ";
		for (int j = size; j > n; j--)
			cout << (int)input[j] << " ";
		cout << endl;
		print(input, n);
	}
	cout << "Sorted numbers: ";
	for (int j = size; j > 0; j--)
		cout << (int)input[j] << " ";
	cout << endl;
}

int main(){
	int input[MAX_SIZE] = { 0 };
	int index = 1;

	string line;
	while (getline(cin, line))
	{
		istringstream in(line);

		while (in >> input[index])
			index++;
		index--;
		BuildMaxHeap(input, index);
		cout << "The construction of max-heap tree" << endl;
		print(input, index);

		HeapSort(input, index);
	}
	system("pause");
}