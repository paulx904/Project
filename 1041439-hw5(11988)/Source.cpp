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

			if (index == 0){	//��home��list���V����list
				newNode->data = input[0];
				newNode->link = NULL;
				home = newNode;
				end = newNode;
			}
			else{
				if (input[index] != '[' && input[index] != ']'){	//��Ū��D'['�ΫD']'���r���A�Nlist�̧ǩ��U��
					newNode->data = input[index];
					newNode->link = NULL;
					end->link = newNode;
					end = newNode;
				}
				if (input[index] == '['){	//��Ū��'['�ɡA�Nhome��now�]����e��list
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

						list *newNode;	//�p�G�᭱���A�X�{'['��']'�A���N�qhome�}�l���U��������string����
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
				else if (input[index] == ']'){	//Ū��']'�ɡA�Nend�]����e��list
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