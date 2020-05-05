#include <iostream>
using namespace std;

int main()
{
	int input[16], copy[16] = {};
	int map[16][4] = { { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 },     
					   { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 },
					   { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 },
					   { 2, 2, 2, 2 }, { 2, 2, 2, 2,}, { 2, 2, 2, 2 }, { 2, 2, 2, 2 } };

	int bits[16][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 0, 1, 1 }, { 0, 0, 1, 0 }, 
						{ 0, 1, 0, 0 }, { 0, 1, 0, 1 }, { 0, 1, 1, 1 }, { 0, 1, 1, 0 }, 
						{ 1, 1, 0, 0 }, { 1, 1, 0, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 0 }, 
						{ 1, 0, 0, 0 }, { 1, 0, 0, 1 }, { 1, 0, 1, 1 }, { 1, 0, 1, 0 } };

	int value = 0, terms = 0, cases = 0, temp = 0;
	cin >> cases;

	while (cases--){
		for (int i = 0; i < 16; i++){  //input
			cin >> input[i];
			copy[i] = input[i];
		}                              //

		for (int i = 0; i < 16; i++)   //全部為0或1的情況
		if (input[i] == 1)
			value++;
		if (value == 16){             
			cout << "#" << ++temp << endl
				<< "1" << endl;
			value = 0;
			continue;
		}
		if (value == 0){
			cout << "#" << ++temp << endl
				<< "0" << endl;
			continue;
		}                              //

		value = 0;

		for (int i = 0; i < 16; i++){
			if (input[i] == 1 && copy[i] == 1){
				for (int digit = 0; digit < 4; digit++){	   //8個為1的情況
					for (int j = 0; j < 16; j++){
						if (input[j] == 1 || input[j] == 2)
						if (bits[i][digit] == bits[j][digit])
							value++;
					}
					if (value == 8){
						for (int k = 0; k < 16; k++)
						if (bits[i][digit] == bits[k][digit])
							copy[k] = 0;
						map[terms][digit] = bits[i][digit];
						terms++;
						break;
					}
					value = 0;
				}
				if (value == 8){
					value = 0;
					continue;
				}
				value = 0;                                     //

				int best_digit = 0, best_digit_2 = 0, count = 0, max = 0;         //4個為1的情況
				for (int digit = 0; digit < 3; digit++){	                        
					for (int digit_2 = digit + 1; digit_2 < 4; digit_2++){
						for (int j = 0; j < 16; j++){
							if (input[j] == 1 || input[j] == 2)
							if (bits[i][digit] == bits[j][digit] && bits[i][digit_2] == bits[j][digit_2]){
								value++;
								if (copy[j] != 0)
									count++;
							}
						}
						if (value == 4 && count > max){
							max = count;
							count = 0;
							best_digit = digit;
							best_digit_2 = digit_2;
						}
						value = 0;
					}
				}
				if (max > 0){
					for (int k = 0; k < 16; k++)
					if (bits[i][best_digit] == bits[k][best_digit] && bits[i][best_digit_2] == bits[k][best_digit_2])
						copy[k] = 0;
					map[terms][best_digit] = bits[i][best_digit];
					map[terms][best_digit_2] = bits[i][best_digit_2];
					terms++;
					value = 0;
					continue;
				}
				value = 0;                                        //

				for (int digit = 0; digit < 4; digit++){          //2個為1的情況
					int digit_2 = (digit + 1) % 4;
					int digit_3 = (digit_2 + 1) % 4;
					for (int j = 0; j < 16; j++){
						if (input[j] == 1 || input[j] == 2)
						if (bits[i][digit] == bits[j][digit] && bits[i][digit_2] == bits[j][digit_2] && bits[i][digit_3] == bits[j][digit_3])
							value++;
					}
					if (value == 2){
						for (int k = 0; k < 16; k++)
						if (bits[i][digit] == bits[k][digit] && bits[i][digit_2] == bits[k][digit_2] && bits[i][digit_3] == bits[k][digit_3])
							copy[k] = 0;
						map[terms][digit] = bits[i][digit];
						map[terms][digit_2] = bits[i][digit_2];
						map[terms][digit_3] = bits[i][digit_3];
						terms++;
						break;
					}
					value = 0;
				}
				if (value == 2){
					value = 0;
					continue;
				}
				value = 0;                                       //

				copy[i] = 0;                                     //單獨為1的情況
				map[terms][0] = bits[i][0];
				map[terms][1] = bits[i][1];
				map[terms][2] = bits[i][2];
				map[terms][3] = bits[i][3];
				terms++;
				continue;                                        //
			}
		}
		cout << "#" << ++temp << endl;                           //output
		for (int i = 0; i < terms; i++){
			for (int j = 0; j < 4; j++)
				cout << map[i][j] << " ";
			cout << endl;
		}                 										 //
		terms = 0;
		for (int i = 0; i < 16; i++)                             //map初始化
		for (int j = 0; j < 4; j++)
			map[i][j] = 2;                                       //
	}
	system("pause");
}