#include <iostream>
#include <iomanip>

using namespace std;
int main(){


	for (int i = 1; i <= 9; i++){
		for (int j = 2; j <= 5; j++){
			cout << j << "*" << i << "=" << setw(2) << j*i << "\t";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 1; i <= 9; i++){
		for (int j = 6; j <= 9; j++){
			cout << j << "*" << i << "=" << setw(2) << j*i << "\t";
		}
		cout << endl;
	}

	system("pause");
}
