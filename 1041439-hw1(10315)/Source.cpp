#include <iostream>
#include <algorithm>
#include <string>
#include<math.h>
#include<string>
#include<sstream>
using namespace std;


int judgeType(int player[5][2], int &cardScore);
void compare(int player1[5][2], int player2[5][2], int player1Type, int player2Type, int player1Scorem, int player2Score);
bool highCard(int player[5][2], int *score);
bool Pair(int player[5][2], int *score);
bool twoPairs(int player[5][2], int *score);
bool threeOfaKind(int player[5][2], int *score);
bool Straight(int player[5][2], int *score);
bool Flush(int player[5][2], int *score);
bool fullHouse(int player[5][2], int *score);
bool fourOfaKind(int player[5][2], int *score);
bool straightFlush(int player[5][2], int *score);


int main()
{
	string line, buffer;
	int b[5][2] = {};
	int w[5][2] = {};
	int black_score = 0, white_score = 0;
	int black_judgeType, white_judgeType;

	while (getline(cin, line)){       //輸入黑方牌組,並將大小花色數字化
		istringstream iss(line);
		for (int i = 0; i < 5; i++){
			iss >> buffer;
			if (buffer[0] == 'T')
				b[i][0] = 10;
			else if (buffer[0] == 'J')
				b[i][0] = 11;
			else if (buffer[0] == 'Q')
				b[i][0] = 12;
			else if (buffer[0] == 'K')
				b[i][0] = 13;
			else if (buffer[0] == 'A')
				b[i][0] = 14;
			else
				b[i][0] = buffer[0] - '0';
			b[i][1] = buffer[1];
		}

		for (int i = 0; i < 5; i++){   //輸入白方牌組,並將大小花色數字化
			iss >> buffer;
			if (buffer[0] == 'T')
				w[i][0] = 10;
			else if (buffer[0] == 'J')
				w[i][0] = 11;
			else if (buffer[0] == 'Q')
				w[i][0] = 12;
			else if (buffer[0] == 'K')
				w[i][0] = 13;
			else if (buffer[0] == 'A')
				w[i][0] = 14;
			else
				w[i][0] = buffer[0] - '0';
			w[i][1] = buffer[1];
		}

		for (int i = 0; i < 4; i++){           // 將牌組有小到大排序
			for (int j = i + 1; j < 5; j++){
				if (b[j][0] < b[i][0]){
					swap(b[j][0], b[i][0]);
					swap(b[j][1], b[i][1]);
				}
				if (w[j][0] < w[i][0]){
					swap(w[j][0], w[i][0]);
					swap(w[j][1], w[i][1]);
				}
			}
		}                                      //
		black_judgeType = judgeType(b, black_score); //判斷牌型
		white_judgeType = judgeType(w, white_score); //
		compare(b, w, black_judgeType, white_judgeType, black_score, white_score); //判斷輸贏
		cout << endl;

	}
	system("pause");
}

int judgeType(int player[5][2], int &cardScore)
{

	if (straightFlush(player, &cardScore))   // straightFlush為9
		return 9;
	else if (fourOfaKind(player, &cardScore))   // fourOfaKind為8
		return 8;
	else if (fullHouse(player, &cardScore))   // fullHouse為7
		return 7;
	else if (Flush(player, &cardScore))   // Flush為6
		return 6;
	else if (Straight(player, &cardScore))   // Straight為5
		return 5;
	else if (threeOfaKind(player, &cardScore))   // threeOfaKind為4
		return 4;
	else if (twoPairs(player, &cardScore))   // twoPairs為3
		return 3;
	else if (Pair(player, &cardScore))   // Pair為2
		return 2;
	else if (highCard(player, &cardScore))   // highCard為1
		return 1;
}

void compare(int player1[5][2], int player2[5][2], int player1Type, int player2Type, int player1Score, int player2Score)
{
	if (player1Type > player2Type)
		cout << "Black wins.";
	else if (player1Type < player2Type)
		cout << "White wins.";
	else{
		if (player1Score > player2Score) 
			cout << "Black wins.";
		else if (player1Score < player2Score)
			cout << "White wins.";
		else
			cout << "Tie.";
	}
}

bool straightFlush(int player[5][2], int *score)
{
	if (Straight(player, score) && Flush(player, score)){
		*score = player[4][0] * pow(10, 5) + player[3][0] * pow(10, 4) + player[2][0] * pow(10, 3)
			+ player[1][0] * pow(10, 2) + player[0][0] * 10;
		return true;
	}
	else
		return false;
}

bool fourOfaKind(int player[5][2], int *score)
{
	if (player[0][0] == player[1][0] && player[1][0] == player[2][0] && player[2][0] == player[3][0] && player[3][0] != player[4][0]){
		*score = player[0][0] * pow(10, 5);
		return true;
	}
	else if (player[0][0] != player[1][0] && player[1][0] == player[2][0] && player[2][0] == player[3][0] && player[3][0] == player[4][0]){
		*score = player[4][0] * pow(10, 5);
		return true;
	}
	else 
		return false;
}

bool fullHouse(int player[5][2], int *score)
{
	if (player[0][0] == player[1][0] && player[1][0] == player[2][0] && player[2][0] != player[3][0] && player[3][0] == player[4][0]){
		*score = player[0][0] * pow(10, 5);
		return true;
	}
	else if (player[0][0] == player[1][0] && player[1][0] != player[2][0] && player[2][0] == player[3][0] && player[3][0] == player[4][0]){
		*score = player[4][0] * pow(10, 5);
	return true;
}
	else
		return false;

}

bool Flush(int player[5][2], int *score)
{
	for (int i = 0; i < 4; i++){
		if (player[i][1] != player[i + 1][1])
			return false;
	}
	*score = player[4][0] * pow(10, 5) + player[3][0] * pow(10, 4) + player[2][0] * pow(10, 3)
		+ player[1][0] * pow(10, 2) + player[0][0] * 10;
	return true;

}

bool Straight(int player[5][2], int *score)
{
	for (int i = 0; i < 4; i++){
		if (player[i][0] != player[i + 1][0] - 1)
			return false;
	}
	*score = player[4][0] * pow(10, 5) + player[3][0] * pow(10, 4) + player[2][0] * pow(10, 3)
		+ player[1][0] * pow(10, 2) + player[0][0] * 10;
	return true;
}

bool threeOfaKind(int player[5][2], int *score)
{
	if (player[0][0] == player[1][0] && player[1][0] == player[2][0] && player[2][0] != player[3][0] && player[2][0] != player[4][0]){
		*score = player[0][0] * pow(10, 5);
		return true;
	}
	else if (player[0][0] != player[1][0] && player[1][0] == player[2][0] && player[2][0] == player[3][0] && player[3][0] != player[4][0]){
		*score = player[1][0] * pow(10, 5);
		return true;
	}
	else if (player[0][0] != player[2][0] && player[1][0] != player[2][0] && player[2][0] == player[3][0] && player[3][0] == player[4][0]){
		*score = player[4][0] * pow(10, 5);
		return true;
}
	else
		return false;
}

bool twoPairs(int player[5][2], int *score)
{
	if (player[0][0] == player[1][0] && player[1][0] != player[2][0] && player[2][0] == player[3][0] && player[3][0] != player[4][0]){
		*score = player[3][0] * pow(10, 5) + player[1][0] * pow(10, 4) + player[4][0] * pow(10, 3);
		return true;
	}
	else if (player[0][0] == player[1][0] && player[1][0] != player[2][0] && player[2][0] != player[3][0] && player[3][0] == player[4][0]){
		*score = player[4][0] * pow(10, 5) + player[1][0] * pow(10, 4) + player[2][0] * pow(10, 3);
		return true;
	}
	else if (player[0][0] != player[1][0] && player[1][0] == player[2][0] && player[2][0] != player[3][0] && player[3][0] == player[4][0]){
		*score = player[4][0] * pow(10, 5) + player[2][0] * pow(10, 4) + player[0][0] * pow(10, 3);
		return true;
}
	else
		return false;
}

bool Pair(int player[5][2], int *score)
{
	if (player[0][0] == player[1][0]){
		*score = player[1][0] * pow(10, 5) + player[4][0] * pow(10, 4) + player[3][0] * pow(10, 3) + player[2][0] * pow(10, 2);
		return true;
	}
	else if (player[1][0] == player[2][0]){
		*score = player[2][0] * pow(10, 5) + player[4][0] * pow(10, 4) + player[3][0] * pow(10, 3) + player[0][0] * pow(10, 2);
		return true;
	}
	else if (player[2][0] == player[3][0]){
		*score = player[3][0] * pow(10, 5) + player[4][0] * pow(10, 4) + player[1][0] * pow(10, 3) + player[0][0] * pow(10, 2);
		return true;
	}
	else if (player[3][0] == player[4][0]){
		*score = player[4][0] * pow(10, 5) + player[2][0] * pow(10, 4) + player[1][0] * pow(10, 3) + player[0][0] * pow(10, 2);
		return true;
	}
	else
		return false;

}

bool highCard(int player[5][2], int *score)
{
	*score = player[4][0] * pow(10, 5) + player[3][0] * pow(10, 4) + player[2][0] * pow(10, 3) + player[1][0] * pow(10, 2) + player[0][0] * 10;
	return true;
}
