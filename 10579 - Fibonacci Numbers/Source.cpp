#include <iostream>
using namespace std;

#define MAX_SIZE 1000

void addition(int fib_1[], int fib_2[], int sum[], int &fib_1Size, int &fib_2Size, int &sumSize)
{

	sumSize = (fib_1Size >= fib_2Size) ? fib_1Size + 1 : fib_2Size + 1;

	for (int index = 0; index < fib_1Size || index < fib_2Size; index++)
		sum[index] = fib_1[index] + fib_2[index];
	for (int index = 0; index < fib_1Size || index < fib_2Size; index++)
	if (sum[index] > 9){
		sum[index] -= 10;
		sum[index + 1]++;
	}
	
	if (sum[sumSize-1] == 0)
		sumSize --;
	
}

int main()
{
	int n;

	while (cin >> n){

		int sum[MAX_SIZE] = { 0 }, fib_1[MAX_SIZE] = { 0 }, fib_2[MAX_SIZE] = { 0 };
		int sumSize = 1, fib_1Size = 1, fib_2Size = 1;
		fib_1[0] = 1; fib_2[0] = 0;

		if (n == 0)
			sum[0] = fib_2[0];

		else if (n == 1)
			sum[0] = fib_1[0];

		else{

			for (int temp = 2; temp <= n; temp++) {
				addition(fib_1, fib_2, sum, fib_1Size, fib_2Size, sumSize);
				for (int i = 0; i < fib_1Size; i++)
					fib_2[i] = fib_1[i];
				fib_2Size = fib_1Size;
				for (int i = 0; i < sumSize; i++)
					fib_1[i] = sum[i];
				fib_1Size = sumSize;
			}
		}
		for (int i = sumSize - 1; i >= 0; i--)
			cout << sum[i];
		cout << endl;
	}
	system("pause");
}