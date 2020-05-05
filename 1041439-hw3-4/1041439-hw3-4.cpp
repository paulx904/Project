#include <iostream>
using namespace std;

int main(){
	int number;
	int sum=0;
	cout << "Enter a positive integer :";
	cin >> number;
	cout << "Perfect numbers between 1 and "<<number<<" :"<<endl;

	for (int i = 1; i < number; i++){
		sum = 0;
		for (int j = 1; j < i; j++){	
			if (i%j == 0){
				sum += j;
			}
		}
			if (sum == i){
				cout << sum<<"="<<"1";
			for (int g = 1; g < sum; g++)
			if (sum % g == 0){
				if (g != 1)
					cout << "+" << g;
				}
			cout << endl;
			}

	}
	

	system("pause");
}