#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stack>
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

char infix[1000], postfix[1000];
int priority(char c);
void trans(char infix[], char buffer[]);
int isOperation(char c);
double calcPostfix(char postfix[]);

int main(){
	int testcase;

	cin >> testcase;
	cin.ignore();

	while (testcase--) {
		cin.getline(infix, sizeof(infix));
		trans(infix, postfix);
		cout << fixed << setprecision(2) << calcPostfix(postfix) << endl;
	}

	system("pause");
}

int priority(char c) {
	switch (c) {
	case '(':return 0;
	case '+': case '-':return 1;
	case '*': case '/':return 2;
	}
	return -1;
}
void trans(char infix[], char buffer[]) {
	int len = strlen(infix);
	char *ptr = buffer;
	stack<char> op;
	*ptr = '\0';
	for (int i = 0; i < len; i++) {
		if (infix[i] == ' ')	
			continue;
		if (infix[i] >= '0' && infix[i] <= '9' || (infix[i] == '-' && infix[i + 1] >= '0' && infix[i + 1] <= '9')) {
			while (infix[i] >= '0' && infix[i] <= '9' || (infix[i] == '-' && infix[i + 1] >= '0' && infix[i + 1] <= '9') || infix[i] == '.') {
				sprintf(ptr, "%c", infix[i]);
				i++;
				while (*ptr)
					ptr++;
			}
			sprintf(ptr, " ");
			while (*ptr)   
				ptr++;
			i--;
		}
		else {
			if (infix[i] == ')') {
				while (!op.empty() && op.top() != '(') {
					sprintf(ptr, "%c ", op.top()), op.pop();
					while (*ptr) ptr++;
				}
				op.pop();
			}
			else {
				if (infix[i] != '(')
				while (!op.empty() && priority(op.top()) >= priority(infix[i])) {
					sprintf(ptr, "%c ", op.top());
					op.pop();
					while (*ptr) 
						ptr++;
				}
				op.push(infix[i]);
			}
		}
	}
	while (!op.empty()) {
		sprintf(ptr, "%c ", op.top());
		op.pop();
		while (*ptr)
			ptr++;
	}
}
int isOperation(char c) {
	switch (c) {
	case '(':return 1;
	case '+': case '-':return 1;
	case '*': case '/':return 1;
	}
	return 0;
}
double calcPostfix(char postfix[]) {
	stringstream sin(postfix);
	string token;
	stack<double> stk;
	double a, b, c;
	while (sin >> token) {
		if (token.length() == 1 && isOperation(token[0])) {
			b = stk.top(), stk.pop();
			a = stk.top(), stk.pop();
			switch (token[0]) {
			case '+': a = a + b; break;
			case '-': a = a - b; break;
			case '*': a = a*b; break;
			case '/': a = a / b; break;
			}
			stk.push(a);
		}
		else {
			stringstream cc(token);
			cc >> c;
			stk.push(c);
		}
	}
	return stk.top();
}



