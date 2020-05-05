#include <iostream>
#include <stack>
using namespace std;



int main()
{
	stack <int> s;

	int n;

	while (cin >> n && n){

			int *input;
			input = new int[n];

			while (true){

				for (int i = 0; i < n; i++){
					cin >> input[i];
					if (!input[i])
						break;
				}
				if (!input[0])
				break;
			

				int count = 1, index = 0;
				s.push(1);
				while (index != n){
				
					if (count == n&&input[index] != s.top())
						index++;
						while (!s.empty() && input[index] == s.top()){
							s.pop();
							index++;
						}
							
					if (count != n)
						s.push(++count);
				}
				if (s.empty())
					cout << "Yes" << endl;
				else
					cout << "No" << endl;

				while (!s.empty())
					s.pop();	
			}
			delete []input;
			cout << endl;
	}
		system("pause");
}
