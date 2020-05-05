#include <iostream>
#include <fstream>
using namespace::std;

// read in a C++ program from a cpp file, and put it to the array "program".
void load(char program[][200], int &numLines);

void deleteComments(char line[]); // if there is a single-line comment in "line", delete it.

void deleteStringConstants(char line[]); // if there are string constants in "line", delete them.

void deleteCharacterConstants(char line[]); // if there are character constants in "line", delete them.

// put all identifiers in "line" into identifiers[ numIdentifiers ].
void getIdentifiers(char line[], char identifiers[][32], int &numIdentifiers);

// if character is a letter, digit or underscore, then return true, otherwise return false.
bool legal(char character);

// print all non-number, non-keyword strings in "identifiers" into a text file.
void store(char identifiers[][32], int numIdentifiers);

bool isNumber(char string[]); // if "string" consists of digits only, then return true, otherwise return false.

bool isKeywords(char string[]); // if "string" is a keyword of C++, then return true, otherwise return false.

// if there is a nonnegtive integer i < pos such that identifiers[ pos ] is equal to identifiers[i],
// then return true; otherwise return false.
bool isDuplicate(char identifiers[][32], int pos);

const char keywords[][20] = { "auto", "break", "case", "char", "const", "continue", "default",
"define", "do", "double", "else", "enum", "extern", "float", "for",
"goto", "if", "int", "long", "register", "return", "short",
"signed", "sizeof", "static", "struct", "switch", "typedef",
"union", "unsigned", "void", "volatile", "while", "bool",
"catch", "class", "const_cast", "delete", "dynamic_cast",
"explicit", "false", "friend", "inline", "mutable", "namespace",
"new", "operator", "private", "protected", "public",
"reinterpret_cast", "static_cast", "template", "this", "throw",
"true", "try", "typeid", "typename", "using", "virtual", "include" };

int main()
{
	char program[1000][200];
	int numLines = 0;

	load(program, numLines); // reads in a C++ program from a cpp file, and put it to the array program.

	char identifiers[2000][32];
	int numIdentifiers = 0;

	for (int i = 0; i < numLines; i++)
	{
		deleteComments(program[i]); // if there is a single-line comment in program[ i ], delete it.
		deleteStringConstants(program[i]); // if there are string constants in program[ i ], delete them.
		deleteCharacterConstants(program[i]); // if there are character constants in program[ i ], delete them.
		if (strcmp(program[i], "") != 0)
			// put all identifiers in program[ i ] into identifiers[ numIdentifiers ].
			getIdentifiers(program[i], identifiers, numIdentifiers);
	}

	// print all non-number, non-keyword strings in "identifiers" into a text file.
	store(identifiers, numIdentifiers);
	system("pause");
}

void load(char program[][200], int &numLines)
{
	ifstream inClientFile("test.cpp", ios::in);

	if (!inClientFile)
	{
		cerr << "File can't be opend." << endl;
		exit(1);
	}
	
	int i = -1;
	while (!inClientFile.eof())
	{
		i++;
		inClientFile.getline(program[i],200);
		
	}

	numLines = i;
}

void deleteComments(char line[])
{
	int begin = 0;

	while (line[begin] != '\0' && (line[begin] != '/' || line[begin + 1] != '/'))
		begin++;

	line[begin] = '\0';

	return;
}

void deleteStringConstants(char line[])
{
	int begin = 0;
	int end;

	while (line[begin] != '\0')
	{
		while (line[begin] != '\0' && line[begin] != '"')
			begin++;

		if (line[begin] == '\0')
			break;

		end = begin + 1;

		if (line[end] == '\0')
			break;

		while (line[end] != '\0' && (line[end - 1] == '\\' || line[end] != '"'))
			end++;

		if (line[end] == '\0')
			break;

		for (int i = begin; i <= end; i++)
			line[i] = ' ';

		begin = end + 1;
	}
}

void deleteCharacterConstants(char line[])
{
	int being = 0;
	int end;
	while (line[being] != '\0')
	{
		while (line[being] != '\0' && line[being] != '"')
			being++;
		if (line[being] == '\0')
			break;
		end = being + 1;
		if (line[end] == '\0')
			break;
		while (line[end] != '\0' && (line[end - 1] == '\\' || line[end] != '"'))
			end++;
		if (line[end] == '\0')
			break;
		for (int i = being; i <= end; i++)
			line[i] = ' ';
		being = end + 1;
	}
}

void getIdentifiers(char line[], char identifiers[][32], int &numIdentifiers)
{
	
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (!legal(line[i]))
			line[i] = ' ';
	}

	int j = 0;

	while (1)
	{
		if (line[j] != ' '&&line[j] != '\0')
		{
			int k = j;
			while (line[k] != ' '&&line[k] != '\0')
				k++;
			for (int l = j, m = 0; l < k; l++, m++)
			{
				identifiers[numIdentifiers][m] = line[l];
				line[l] = ' ';
			}
			identifiers[numIdentifiers][k - j] = '\0';
			numIdentifiers++;
		}
		else if (line[j] == '\0')
			return;
		else
			j++;
	}
}

bool legal(char character)
{
	return (isalnum(character) || character == '_');
}

void store(char identifiers[][32], int numIdentifiers)
{
	ofstream outClientFile("test.txt", ios::out);
	if (!outClientFile)
	{
		cerr << "File can't be stored." << endl;
		exit(1);
	}
	for (int i = 0; i < numIdentifiers; i++) {
		if (!isNumber(identifiers[i]))
			break;
		if (!isKeywords(identifiers[i]))
			break;
		if (!isDuplicate (identifiers,i))
			break;
		outClientFile << identifiers[i] << endl;
	}

	cout << endl << endl;

	outClientFile.close();
}

bool isNumber(char string[])
{
	for (unsigned int i = 0; i < strlen(string); i++)
	if (!isdigit(string[i]))
		return false;

	return true;
}

bool isKeywords(char string[])
{
	const int numKeywords = sizeof(keywords) / 20;
	for (int i = 0; i < numKeywords; i++)
	if (strcmp(keywords[i], string) == 0)
		return true;

	return false;
}

bool isDuplicate(char identifiers[][32], int pos)
{
	for (int i = 0; i < pos; i++)
	if (strcmp(identifiers[i], identifiers[pos]) == 0)
		return true;

	return false;
}



