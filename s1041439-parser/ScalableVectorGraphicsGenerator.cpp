#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "ScalableVectorGraphicsGenerator.hpp"
#include <stack>
#include <queue>
using namespace std;
vector <struct Circuit> circuit;
ScalableVectorGraphicsGenerator artist;
int maxlev = 0;
int numOfInput = 0;

ScalableVectorGraphicsGenerator::ScalableVectorGraphicsGenerator()
: gateSize(50)
, canvasWidth(1000)
, canvasHeight(1000)
{
}

ScalableVectorGraphicsGenerator::~ScalableVectorGraphicsGenerator()
{
}

void ScalableVectorGraphicsGenerator::drawRectangle(int x, int y, int width, int height, std::string color)
{
	out << "\t<rect "
		<< "x=\"" << x << "\" "
		<< "y=\"" << y << "\" "
		<< "width=\"" << width << "\" "
		<< "height=\"" << height << "\" ";
	out << "fill=\""
		<< color
		<< "\" ";
	out << " />" << endl;
}

void ScalableVectorGraphicsGenerator::drawAND(int x, int y)
{
	out << "\t<path d=";
	out << "\"M "
		<< x << " " << y << " "
		<< x + gateSize << " " << y << " "
		<< "Q "
		<< x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
		<< x + gateSize << " " << y + gateSize << " "
		<< "L "
		<< x << " " << y + gateSize << " "
		<< "Z "
		<< "\" fill=\"red\" />";
	out << endl;
}

void ScalableVectorGraphicsGenerator::drawOR(int x, int y)
{
	out << "\t<path d=";
	out << "\"M "
		<< x << " " << y << " "
		<< x + gateSize << " " << y << " "
		<< "Q "
		<< x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
		<< x + gateSize << " " << y + gateSize << " "
		<< "L "
		<< x << " " << y + gateSize << " "
		<< "Q "
		<< x + gateSize / 2 << " " << y + gateSize / 2 << " "
		<< x << " " << y << " "
		<< "\" fill=\"yellow\" />";
	out << endl;
}

void ScalableVectorGraphicsGenerator::drawINV(int x, int y)
{
	out << "\t<path d=";
	out << "\"M "
		<< x << " " << y << " "
		<< "L "
		<< x + gateSize + gateSize / 4 << " " << y + gateSize / 2 << " "
		<< x << " " << y + gateSize << " "
		<< "Z "
		<< "\" fill=\"green\" />";
	out << endl;

	out << "\t<circle ";
	out << "cx=" << x + gateSize + gateSize / 4 << " "
		<< "cy=" << y + gateSize / 2 << " "
		<< "r=" << gateSize / 7 << " "
		<< "fill=\"green\" />";
	out << endl;
}

void ScalableVectorGraphicsGenerator::drawNAND(int x, int y)
{
	out << "\t<path d=";
	out << "\"M "
		<< x << " " << y << " "
		<< x + gateSize << " " << y << " "
		<< "Q "
		<< x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
		<< x + gateSize << " " << y + gateSize << " "
		<< "L "
		<< x << " " << y + gateSize << " "
		<< "Z "
		<< "\" fill=\"red\" />";
	out << endl;

	out << "\t<circle ";
	out << "cx=" << x + gateSize + gateSize / 3 << " "
		<< "cy=" << y + gateSize / 2 << " "
		<< "r=" << gateSize / 7 << " "
		<< "fill=\"red\" />";
	out << endl;
}

void ScalableVectorGraphicsGenerator::drawNOR(int x, int y)
{
	out << "\t<path d=";
	out << "\"M "
		<< x << " " << y << " "
		<< x + gateSize << " " << y << " "
		<< "Q "
		<< x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
		<< x + gateSize << " " << y + gateSize << " "
		<< "L "
		<< x << " " << y + gateSize << " "
		<< "Q "
		<< x + gateSize / 2 << " " << y + gateSize / 2 << " "
		<< x << " " << y << " "
		<< "\" fill=\"yellow\" />";
	out << endl;

	out << "\t<circle ";
	out << "cx=" << x + gateSize + gateSize / 3 << " "
		<< "cy=" << y + gateSize / 2 << " "
		<< "r=" << gateSize / 7 << " "
		<< "fill=\"yellow\" />";
	out << endl;
}

void ScalableVectorGraphicsGenerator::drawXNOR(int x, int y)
{
	out << "\t<path d=";
	out << "\"M "
		<< x + gateSize / 4 << " " << y << " "
		<< x + gateSize << " " << y << " "
		<< "Q "
		<< x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
		<< x + gateSize << " " << y + gateSize << " "
		<< "L "
		<< x + gateSize / 4 << " " << y + gateSize << " "
		<< "Q "
		<< x + gateSize / 2 + gateSize / 4 << " " << y + gateSize / 2 << " "
		<< x + gateSize / 4 << " " << y << " "
		<< "\" fill=\"blue\" />";
	out << endl;

	out << "\t<path d=";
	out << "\"M "
		<< x << " " << y << " "
		<< x + gateSize / 8 << " " << y << " "
		<< "Q "
		<< x + gateSize / 2 << " " << y + gateSize / 2 << " "
		<< x + gateSize / 8 << " " << y + gateSize << " "
		<< "L "
		<< x << " " << y + gateSize << " "
		<< "Q "
		<< x + gateSize / 2 << " " << y + gateSize / 2 << " "
		<< x << " " << y << " "
		<< "\" fill=\"blue\" />";
	out << endl;

	out << "\t<circle ";
	out << "cx=" << x + gateSize + gateSize / 3 << " "
		<< "cy=" << y + gateSize / 2 << " "
		<< "r=" << gateSize / 7 << " "
		<< "fill=\"blue\" />";
	out << endl;
}

void ScalableVectorGraphicsGenerator::drawXOR(int x, int y)
{
	out << "\t<path d=";
	out << "\"M "
		<< x + gateSize / 4 << " " << y << " "
		<< x + gateSize << " " << y << " "
		<< "Q "
		<< x + gateSize * 1.5 << " " << y + gateSize / 2 << " "
		<< x + gateSize << " " << y + gateSize << " "
		<< "L "
		<< x + gateSize / 4 << " " << y + gateSize << " "
		<< "Q "
		<< x + gateSize / 2 + gateSize / 4 << " " << y + gateSize / 2 << " "
		<< x + gateSize / 4 << " " << y << " "
		<< "\" fill=\"pink\" />";
	out << endl;

	out << "\t<path d=";
	out << "\"M "
		<< x << " " << y << " "
		<< x + gateSize / 8 << " " << y << " "
		<< "Q "
		<< x + gateSize / 2 << " " << y + gateSize / 2 << " "
		<< x + gateSize / 8 << " " << y + gateSize << " "
		<< "L "
		<< x << " " << y + gateSize << " "
		<< "Q "
		<< x + gateSize / 2 << " " << y + gateSize / 2 << " "
		<< x << " " << y << " "
		<< "\" fill=\"pink\" />";
	out << endl;
}

void ScalableVectorGraphicsGenerator::drawIOBox(int x, int y, int flag)
{
	if (flag == 0) {
		drawRectangle(x, y + gateSize / 4, gateSize, gateSize / 2, "Cyan");
	}
	else if (flag == 1){
		drawRectangle(x, y + gateSize / 4, gateSize, gateSize / 2, "Fuchsia");
	}
	else {
		drawRectangle(x, y + gateSize / 4, gateSize, gateSize / 2, "gray");
	}
}

void ScalableVectorGraphicsGenerator::drawPath(std::vector< int >& path)
{
	out << "\t<path d=";
	out << "\"M " << path[0] << " " << path[1] << " ";
	out << "L ";
	for (unsigned int i = 2; i < path.size(); ++i)
		out << path[i] << " ";
	out << "\" stroke=\"black\" />";
	out << endl;
}

void ScalableVectorGraphicsGenerator::drawText(int x, int y, std::string& text)
{
	out << "\t<text "
		<< "x=\"" << x + gateSize / 2 << "\" "
		<< "y=\"" << y + gateSize / 2 << "\" >"
		<< text << "</text>";
	out << endl;
}

void ScalableVectorGraphicsGenerator::SVGBegin(std::string filename, int width, int height)
{
	out.open(std::string(filename + ".html").c_str(), std::ios::out);
	out << "<svg "
		<< "width=\"" << width << "px\" "
		<< "height=\"" << height << "px\">" << endl;
	canvasWidth = width;
	canvasHeight = height;
}

void ScalableVectorGraphicsGenerator::SVGEnd()
{
	out << "</svg>" << endl;
	out.close();
}

void ScalableVectorGraphicsGenerator::setGateSize(int inSize)
{
	gateSize = inSize;
}

int ScalableVectorGraphicsGenerator::getGateSize()
{
	return gateSize;
}
struct Circuit
{
	string input1, input2, output[10];
	string name;
	string gate;
	int level;
	int x, y;
};

string strchrn(string dest, string src, char b, char e) {

	string m = strchr(src.c_str(), b) + 1;
	string n = strchr(src.c_str(), e);
	string dest_ = dest.c_str();
	int len = m.length() - n.length();
	dest_ = dest_.assign(m, 0, len);
	return dest_;

}
int row = 0, col = 0;
void paint(int num)
{
	if (circuit[num].level % 2 == 0)
		col += 50;

		if(maxlev != 0)
			row = circuit[num].level*(1000 / (maxlev+1));
		if (circuit[num].gate == "INPUT"){
			artist.drawIOBox(row, col, 0);
		}
		if (circuit[num].gate == "OUTPUT"){
			artist.drawIOBox(row, col, 2);
		}
		if (circuit[num].gate == "BUFF"){
			artist.drawIOBox(row, col, 1);
		}
		if (circuit[num].gate == "NOT"){
			artist.drawINV(row, col);
		}
		if (circuit[num].gate == "AND"){
			artist.drawAND(row, col);
		}
		if (circuit[num].gate == "NAND"){
			artist.drawNAND(row,col);
		}
		if (circuit[num].gate == "OR"){
			artist.drawOR(row, col);
		}
		if (circuit[num].gate == "NOR"){
			artist.drawNOR(row, col);
		}
		if (circuit[num].gate == "XOR"){
			artist.drawXOR(row, col);
		}
		if (circuit[num].gate == "XNOR"){
			artist.drawXNOR(row, col);
		}

		artist.drawText(row, col, circuit[num].name);
		circuit[num].x = row;
		circuit[num].y = col;

		if (circuit[num].level % 2 == 0)
			col -= 50;
}

bool adj[50][50] = { false };
bool visit[50];
stack<int> r_path;
queue<int> path[10];
int numOfpath = 0;
void DFS(int i)
{
	
	if (visit[i]) return;
	visit[i] = true;

	int j = 0;
	for (; j < circuit.size(); j++){
		if (adj[i][j])
			DFS(j);
	}
		r_path.push(i);
}

void traversal()
{
	for (int i = 0;  i < circuit.size(); i++)
		visit[i] = false;

	for (int i = 0; i < circuit.size(); i++){
		DFS(i);
		int lev = 0;
		while(!r_path.empty()){
			if (lev > maxlev)
				maxlev = lev;
			circuit[r_path.top()].level = lev;
			if (circuit[r_path.top()].output[0] == "\0")
				circuit[r_path.top()].level = maxlev;
			lev++;
			path[numOfpath].push(r_path.top());
			r_path.pop();
		}
		numOfpath++;
	}
}

int main()
{
	string fileName = "design_00 ";
	char line[50];
	string instruction[100];

	fstream inFile;
	inFile.open(fileName+".isc", ios::in);
	if (!inFile){
		cout << "Fail to open file. " << endl;
	}

	int index = 0;
	while (inFile.getline(line, sizeof(line), '\n')){
		if (line[0] != '\0'&&line[0] != '#'){
			instruction[index] = line;
			index++;
		}
	}

	inFile.close();

	
	for (int i = 0; i < index; i++){	//discriminate kinds of gates
		Circuit buffer;
		if (instruction[i][0] == 'I'){	//input
			buffer.gate = buffer.gate.assign(instruction[i], 0, 5);
			buffer.name = strchrn(buffer.name, instruction[i], '(', ')');
			circuit.push_back(buffer);
			numOfInput++;
		}
		else if (instruction[i][0] == 'O'){	//output
			buffer.gate = buffer.gate.assign(instruction[i], 0, 6);
			buffer.name = strchrn(buffer.name, instruction[i], '(', ')');
			circuit.push_back(buffer);
		}
		else{	//other gates
			string Output, Input1, Input2, Gate;
			bool isTwoInput = false;
			int length = 0;
			for (; length < instruction[i].length(); length++){
				if (instruction[i][length] == '=')
					Output = Output.assign(instruction[i], 0, length - 1);
				if (instruction[i][length] == ','){
					isTwoInput = true;
					break;
				}
			}
			if (isTwoInput){
				Input1 = strchrn(Input1, instruction[i], '(', ',');
				Input2 = strchrn(Input2, instruction[i], ',', ')');
				Input2 = Input2.assign(Input2, 1, Input2.length());
			}
			else
				Input1 = strchrn(Input1, instruction[i], '(', ')');

			Gate = strchrn(Gate, instruction[i], ' ', ')');
			Gate = strchrn(Gate, instruction[i], '=', '(');
			Gate = Gate.assign(Gate, 1, Gate.length());


			int j = 0;
			for (; j < circuit.size(); j++){
				if (Output == circuit[j].name){		//Output exist
					circuit[j].gate = Gate;
					int m = 0;
					for (; m < circuit.size(); m++){
						if (Input1 == circuit[m].name){		//Input exis
							break;
						}
					}
					if (m == circuit.size()){	//if the input not exist, creat it
						buffer.name = Input1;
						circuit.push_back(buffer);
					}
					circuit[j].input1 = Input1;
					for (int i = 0; i < 10; i++)
					if (circuit[m].output[i] == "\0"){
						circuit[m].output[i] = Output;
						break;
					}
					break;
				}
			}
			if (j == circuit.size()){	//Output doesn't exist
				buffer.name = Output;
				buffer.gate = Gate;
				buffer.input1 = Input1;
				circuit.push_back(buffer);
				int k = 0;
				for (; k < circuit.size(); k++){
					if (Input1 == circuit[k].name){		//Input exist
						break;
					}
				}
				if (k == circuit.size()){		//if Input not exist, creat it
					buffer.name = Input1;
					circuit.push_back(buffer);
				}
				circuit[j].input1 = Input1;
				for (int i = 0; i < 10; i++)
				if (circuit[k].output[i] == "\0"){
					circuit[k].output[i] = Output;
					break;
				}
			}
			if (isTwoInput){	//descriminate if Input2 exist
				int n = 0;
				for (; n < circuit.size(); n++){
					if (Input2 == circuit[n].name){		//Input exist
						break;
					}
				}
				if (n == circuit.size()){		//if Input not exist, creat it
					buffer.name = Input2;
					circuit.push_back(buffer);
				}
				for (int j = 0; j < circuit.size(); j++)
				if (Output == circuit[j].name)
					break;
				circuit[j].input2 = Input2;
				for (int i = 0; i < 10; i++)
				if (circuit[n].output[i] == "\0"){
					circuit[n].output[i] = Output;
					break;
				}
			}
		}
	}
	for (int i = 0; i < circuit.size(); i++)
		cout << "name:" << circuit[i].name << ", gate:" << circuit[i].gate
		<< ", Input1:" << circuit[i].input1 << ", Input2:" << circuit[i].input2
		<< ", Output[0]:" << circuit[i].output[0]
		<< ", Output[1]:" << circuit[i].output[1] << endl;

	for (int i = 0; i < circuit.size(); i++){
		for (int j = 0; j < circuit.size(); j++){
			for (int k = 0; k < 10; k++)
			if (circuit[i].output[k] == circuit[j].name)
			adj[i][j] = true;
		}
	}
	artist.SVGBegin(fileName, 1000, 1000);
	artist.setGateSize(50);
	traversal();
	
	for (int i = 0; i < numOfpath;i++){
		while (!path[i].empty()){
			paint(path[i].front());
			cout << path[i].front();
			path[i].pop();
		}
		col += (1000 / (numOfInput + 1));
		cout << endl;
	}
	vector <int> coordinate;
	for (int i = 0; i < circuit.size(); i++){
		coordinate.push_back(circuit[i].x + 50 / 2);
		coordinate.push_back(circuit[i].y + 50 / 2);
		if (circuit[i].input1 != "\0"){
			for (int j = 0; j < circuit.size();j++)
			if (circuit[j].name == circuit[i].input1){
				coordinate.push_back(circuit[j].x + 50 / 2);
				coordinate.push_back(circuit[j].y + 50 / 2);
			}
			artist.drawPath(coordinate);
		}
		coordinate.pop_back();
		coordinate.pop_back();
		if (circuit[i].input2 != "\0"){
			for (int j = 0; j < circuit.size(); j++)
			if (circuit[j].name == circuit[i].input2){
				coordinate.push_back(circuit[j].x + 50 / 2);
				coordinate.push_back(circuit[j].y + 50 / 2);
			}
			artist.drawPath(coordinate);
		}
		while (!coordinate.empty())
			coordinate.pop_back();
	}
	artist.SVGEnd();

	system("pause");
}