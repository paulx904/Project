#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
const int MAX_SIZE = 100;
string output[MAX_SIZE] = {};

void print(int i, int j, int **record,char *x, int index)
{
	if (i == 0 || j == 0)
		return;
	if (record[i][j] == 0)    // jump to左上方
	{
		print(i - 1, j - 1, record, x, index);
		output[0] += x[i];
		output[0] += " ";
	}
	else if (record[i][j] == 1)   // jump to 左方
		print(i, j - 1, record, x, index);
	else if (record[i][j] == 2)   // jump to 上方
		print(i - 1, j, record, x, index);
}

void main()
{
	char x[MAX_SIZE] = {};
	char y[MAX_SIZE] = {};
	int x_len = 1, y_len = 1;
	char name;

	string line;
	while (getline(cin, line))  //讀入x,y兩個序列
	{
		istringstream in(line);
		in >> name;
		if (name == 'X'){
			while (in >> x[x_len])
				x_len++;
		}
		else if (name == 'Y'){
			while (in >> y[y_len])
				y_len++;
		}
		
		if (x_len != 1 && y_len != 1)
			break;
	}

	int **map = new int *[x_len];    //建立圖表
	for (int i = 0; i < x_len; i++)
		map[i] = new int[y_len];

	int **record = new int *[x_len];    //建立紀錄LCT元素的二維陣列
	for (int i = 0; i < x_len; i++)
		record[i] = new int[y_len];

	for (int i = 0; i < x_len; i++)		//初始化陣列
		map[i][0] = 0;
	for (int j = 0; j < y_len; j++)
		map[0][j] = 0;

	for (int i = 1; i < x_len; i++){
		for (int j = 1; j < y_len; j++){
			if (x[i] == y[j]){
				map[i][j] = map[i - 1][j - 1] + 1;		//左上方
				record[i][j] = 0;
			}
			else{
				map[i][j] = max(map[i - 1][j],map[i][j - 1]);
				if (map[i][j] == map[i][j-1])	//左方
					record[i][j] = 1;
				else                            //上方
					record[i][j] = 2;
			}

		}
	}
	int index = 1;

	for (int i = 1; i < x_len; i++){            //verify the answer isn't repeat then print
		for (int j = 1; j < y_len; j++){
			if (map[i][j] == map[x_len - 1][y_len - 1]){
				print(i, j, record, x, index);
				for (int temp = 1; temp < MAX_SIZE; temp++){
					if (output[0] == output[temp])
						break;
					else if (temp == MAX_SIZE - 1){
						cout << output[0] << endl;
						output[index] = output[0];
						index++;
					}
				}
				output[0] = "";
			}
		}
	}

	for (int i = 0; i < x_len; i++)
		delete []map[i]; 
	delete[]map;

	for (int i = 0; i < x_len; i++)
		delete[]record[i];
	delete[]record;

	system("pause");
}
