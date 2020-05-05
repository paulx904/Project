#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
	stack <char> ship[1000];
	string container;
	int count = 1, cases = 1;
	bool equal = false;

	while (getline(cin, container)){

		if (container == "end")
			break;

		ship[count].push(container[0]);

		for (int i = 1; i < container.size(); i++){
			for (int j = 1; j <= count; j++){
				if (container[i] - '0' <= ship[j].top()-'0'){
					ship[j].push(container[i]);
					equal = true;
					break;
				}
			}
			if (!equal)
				ship[++count].push(container[i]);
			equal = false;
		}
		cout << "Case " << cases++ << ": " << count << endl;
		count = 1;
	}
	system("pause");
}
	

	

	
