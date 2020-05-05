#include <iostream>
using namespace std;
int main(){

	int number;
	cin >> number;
	int x ;
	int largest = number;
	int secondlargest = number;
	cout << "Enter the number of integers to be processed followed by the integers:"<<endl;
	 
	for (int i = 1; i <= number; i++){
		cin >> x;
		if (x > largest){
			secondlargest = largest;
			largest = x;
		}
		
	
	}
	cout << "Largest is " << largest << endl << "Second largest is " << secondlargest << endl;
	
	
	system("pause");
}