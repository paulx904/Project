#include<iostream>
using namespace std;

int summingFactors(int i) {
	int sum;
	sum = 0;
	for (int j = 1; j < i; j++){
		if (i%j == 0){
			sum += j;
		}
	}
	return sum;
}

void display(int n, int m){
		cout << n << "=" << "1";
		for (int x = 2; x < n; x++){
			if (n%x == 0){
				cout << "+" << x;
			}
		}
		cout << endl;
		cout << m << "=" << "1";
		for (int y = 2; y < m; y++){
			if (m%y == 0){
				cout << "+" << y;
			}
		}
		cout << endl<<endl;

}

int main(){
	int number;
	int sum1;
	int sum2;
	cout << "Enter a positive integer :";
	cin >> number;
	cout << "Amicable pairs between 1 and " << number << ": " << endl << endl;
	for (int i = 1; i <= number; i++){
		sum1 = summingFactors(i);
		sum2 = summingFactors(sum1);
		if (i == sum2 && i < sum1)
			display(i, sum1);
	
	}

		
	
	
	system("pause");
}