#include <iostream>
#include <string>
using namespace std;

struct list {
	char data;
	struct list *link;
};

int main()
{
	string input;

	while (getline(cin, input) && input!=""){

		list *home = NULL, *now = NULL, *end = NULL;
		unsigned int index = 0;

		while (index < input.size()){    
			list *newNode;
			newNode = new list;

			if (index == 0){	//把home跟list指向首個list
				newNode->data = input[0];
				newNode->link = NULL;
				home = newNode;
				end = newNode;
			}
			else{
				if (input[index] != '[' && input[index] != ']'){	//當讀到非'['或非']'的字元，將list依序往下接
					newNode->data = input[index];
					newNode->link = NULL;
					end->link = newNode;
					end = newNode;
				}
				if (input[index] == '['){	//當讀到'['時，將home跟now設為當前的list
					newNode->data = input[index];
					newNode->link = home;
					home = newNode;
					now = newNode;
					index++;
					while (input[index] != '\0'){	

						if (input[index] == '['){
							break;
						}
						if (input[index] == ']')
							break;

						list *newNode;	//如果後面未再出現'['或']'，那就從home開始往下接直到整個string結束
						newNode = new list;
						if (input[index] != '[' && input[index] != ']'){
							newNode->data = input[index];
							newNode->link = now->link;
							now->link = newNode;
							now = newNode;
							index++;
						}
					}
					index--;
				}
				else if (input[index] == ']'){	//讀到']'時，將end設為當前的list
					newNode->data = input[index];
					newNode->link = NULL;
					end->link = newNode;
					end = newNode;
				}
			}
			index++;
		}
		for (now = home; now != end->link; now = now->link){
			if (now->data != '[' && now->data != ']')
			cout << now->data;
		}
		cout << endl;
	}
	system("pause");
}