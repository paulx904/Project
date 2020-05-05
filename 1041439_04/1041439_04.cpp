#include <iostream>
#include <fstream>   
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>  
using namespace std;

bool checkExist(int frameSize, int frame[], int reference);
bool checkEmpty(int frameSize, int frame[]);
void FIFO(int frameSize, int reference[], int length);


int main(int argc, char *argv[])
{
	int frameSize = 0;
	int reference[2048];
	int length = -1;

	ifstream inFile(argv[1], ios::in);
	if (!inFile){
		cerr << "File can't be opend." << endl;
		exit(1);
	}
	else{
		while (!inFile.eof()){
			if (length == -1)
				inFile >> frameSize;
			else
				inFile >> reference[length];
			length++;
		}
	}
	if (frameSize < 2 || frameSize > 5){
		cerr << "File can't be opend." << endl;
		exit(1);
	}
	inFile.close();
	
	FIFO(frameSize, reference, length);

	system("pause");

}

bool checkExist(int frameSize, int frame[], int reference)
{
	for (int i = 0; i < frameSize; i++)		
		if (frame[i] == reference)
			return true;
	return false;
}

bool checkEmpty(int frameSize, int frame[])
{
	for (int i = 0; i < frameSize; i++)
	if (frame[i] == -1)
		return true;
	return false;
}

void FIFO(int frameSize, int reference[], int length)
{
	int *frame;
	frame = new int[frameSize];
	for (int i = 0; i < frameSize; i++)
		frame[i] = -1;
	int *order;
	order = new int[frameSize];
	bool exist = false;
	bool empty = true;
	bool change;
	int count = 0;
	
	cout << "FIFO ========== " << endl;
	for (int i = 0; i < length; i++){
		cout << reference[i] << ":";
		exist = checkExist(frameSize, frame, reference[i]);			//checek whether regerence[i] is in frame or not
		empty = checkEmpty(frameSize, frame);
		change = false;
		if (!exist){			//reference[i] doesn't exist in frame
			change = true;
			if (empty){				//frame is still have the room
				for (int j = 0; j < frameSize; j++)
					if (frame[j] == -1){
						frame[j] = reference[i];
						order[j] = i;
						break;
					}
			}
			else{			//frame doesn't have the room
				int firstIn = order[0], first = 0;
				for (int j = 1; j < frameSize; j++){
					if (order[j] < firstIn){
						firstIn = order[j];
						first = j;
					}
				}
				frame[first] = reference[i];
				order[first] = i;
			}
		}
		for (int index = 0; index < frameSize; index++){		//print
			cout << " ";
			if (frame[index] == -1)
				cout << "X";
			else
				cout << frame[index];
		}
		if (change){
			cout << " page fault ";
			count++;
		}
		cout << endl;
	}
	cout << "FIFO Total Page Fault: " << count << endl;
}
