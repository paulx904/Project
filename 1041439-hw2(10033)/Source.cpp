#include <iostream>
#include <istream>
#include <string>
#include <string.h>
using namespace std;

int Ram[1000] = {};
int Register[10] = {};
int numOfinstructions = 0;
int numOfcases;

void execute(int index);

int main()
{
	string n;
	getline(cin, n);
	cin.ignore();

	numOfcases = stoi(n);
	int temp = numOfcases;

	while (numOfcases > 0){

		string string;
		int address = 0;
		memset(Register, 0, sizeof(Register));
		memset(Ram, 0, sizeof(Ram));

		while (getline(cin, string) && string!=""){
			Ram[address]=stoi(string);
			address++;
		}

		execute(0);

		if (numOfcases < temp)
			cout << endl;
		cout << numOfinstructions << endl;
		numOfcases--;
	}

	system("pause");
}

void execute(int index)
{
	numOfinstructions = 0;

	while (true){

		numOfinstructions++;

		int a = Ram[index] / 100;
		int b = (Ram[index] % 100) / 10;
		int c = Ram[index] % 10;

		switch (a){
		case 1:
			return;
			break;
		case 2:
			Register[b] = c;
			break;
		case 3:
			Register[b] += c;
			Register[b] %= 1000;
			break;
		case 4:
			Register[b] *= c;
			Register[b] %= 1000;
			break;
		case 5:
			Register[b] = Register[c];
			break;
		case 6:
			Register[b] += Register[c];
			Register[b] %= 1000;
			break;
		case 7:
			Register[b] *= Register[c];
			Register[b] %= 1000;
			break;
		case 8:
			Register[b] = Ram[Register[c]];
			break;
		case 9:
			Ram[Register[c]] = Register[b];
			break;
		case 0:
			if (Register[c] != 0){
				index = Register[b];
				continue;
			}
			break;
		}
		index++;
	}
}