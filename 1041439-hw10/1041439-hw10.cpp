#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

struct Date
{
	int year;
	int month;
	int day;
};

struct AvailableRooms
{
	Date date;
	int availableRooms[6]; // number of available rooms
};

int numRooms[6] = { 0, 9, 5, 3, 5, 4 };
int days[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void computeCurrentDate(Date &currentDate);

void loadAvailableRooms(AvailableRooms availableRooms[], int &numRecords);

void initializeAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords);

void adjustAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords);

// returns a value of 0, -1 or 1 if date1 is equal to, less than or greater than date2, respectively.
int compareDates(Date date1, Date date2);

void saveAvailableRooms(AvailableRooms availableRooms[], int numRecords);

int main()
{
	Date currentDate = {};

	computeCurrentDate(currentDate);

	AvailableRooms availableRooms[184] = {};
	int numRecords = 0;

	loadAvailableRooms(availableRooms, numRecords);

	if (numRecords == 0 || compareDates(availableRooms[numRecords].date, currentDate) == -1)
		initializeAvailableRooms(availableRooms, currentDate, numRecords);
	else if (compareDates(availableRooms[1].date, currentDate) == -1){
		adjustAvailableRooms(availableRooms, currentDate, numRecords);
	}
	cout << "The number of available rooms of each room type:\n\n";
	cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";
	for (int i = 1; i <= numRecords; i++)
		cout << availableRooms[i].date.year << "-"
		<< setw(2) << setfill('0') << availableRooms[i].date.month << "-"
		<< setw(2) << availableRooms[i].date.day
		<< setw(16) << setfill(' ') << availableRooms[i].availableRooms[1]
		<< setw(14) << availableRooms[i].availableRooms[2]
		<< setw(19) << availableRooms[i].availableRooms[3]
		<< setw(17) << availableRooms[i].availableRooms[4]
		<< setw(15) << availableRooms[i].availableRooms[5] << "\n";
		
	saveAvailableRooms(availableRooms, numRecords);

	system("pause");
}

void computeCurrentDate(Date &currentDate)
{
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s(&structuredTime, &rawTime);

	currentDate.year = structuredTime.tm_year + 1900;
	currentDate.month = structuredTime.tm_mon + 1;
	currentDate.day = structuredTime.tm_mday;

	cout << "The current date is " << currentDate.year << "-"
		<< setw(2) << setfill('0') << currentDate.month << "-"
		<< setw(2) << currentDate.day << endl << endl;
}

void loadAvailableRooms(AvailableRooms availableRooms[], int &numRecords)
{
	ifstream inFile("Available Rooms 2.dat", ios::binary);
	if (!inFile){
		cout << "The file couldn't be opend." << endl;
		exit(1);
	}

	numRecords = 1;
	while (!inFile.eof()){
		inFile.read(reinterpret_cast<char *>(&availableRooms[numRecords]), sizeof(AvailableRooms));
			numRecords++;
	}
	numRecords -= 2;
}

int compareDates(Date date1, Date date2)
{
	
	if (date1.year < date2.year)
		return -1;
	else if (date1.year > date2.year)
		return 1;
	else if (date1.month < date2.month)
		return -1;
	else if (date1.month > date2.month)
		return 1;
	else if (date1.day < date2.day)
		return -1;
	else if (date1.month > date2.month)
		return 1;
	else
		return 0;
}

void initializeAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords)
{
	
	numRecords = 0;

	while (numRecords != 180)
	{
		numRecords++;
		availableRooms[numRecords].date.year = currentDate.year; 
		availableRooms[numRecords].date.month = currentDate.month;  
		availableRooms[numRecords].date.day = currentDate.day; 
		

		currentDate.day++;
		if (currentDate.day > days[currentDate.month])
		{
			currentDate.month++;
			if (currentDate.month > 12)
			{
				currentDate.year++;
				currentDate.month = 1;
			}
			currentDate.day = 1;
		}
		for (int i = 1; i <= 5; i++)
		{
			availableRooms[numRecords].availableRooms[i] = numRooms[i];
		}
	}
	
}

void adjustAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords)
{
	int temp = 1;
	for (; temp < numRecords; temp++){
		if (currentDate.year == availableRooms[temp].date.year&&currentDate.month == availableRooms[temp].date.month&&currentDate.day == availableRooms[temp].date.day)
			break;
	}
	for (int j = 1; j <= 5; j++)
		availableRooms[1].availableRooms[j] = availableRooms[temp].availableRooms[j];

	availableRooms[1].date.year = currentDate.year;
	availableRooms[1].date.month = currentDate.month;
	availableRooms[1].date.day = currentDate.day;
	for (int i = 2; i <= numRecords; i++){
		if (availableRooms[i - 1].date.day + 1 <= days[availableRooms[i - 1].date.month]){
			availableRooms[i].date.day = availableRooms[i - 1].date.day + 1;
			availableRooms[i].date.month = availableRooms[i - 1].date.month;
			availableRooms[i].date.year = availableRooms[i - 1].date.year;
		}
		else if (availableRooms[i-1].date.month < 12){
			availableRooms[i].date.year = availableRooms[i - 1].date.year;
			availableRooms[i].date.month = availableRooms[i - 1].date.month + 1;
				availableRooms[i].date.day = 1;
			}
			else {
				availableRooms[i].date.year = availableRooms[i-1].date.year + 1;
				availableRooms[i].date.month = 1;
				availableRooms[i].date.day = 1;
			}
			
			for (int j = 1; j <= 5; j++){
				if (temp <= numRecords){
					availableRooms[i].availableRooms[j] = availableRooms[temp+1].availableRooms[j];
		
				}
				else
					availableRooms[i].availableRooms[j] = numRooms[j];
			}
			temp++;
		}

}

void saveAvailableRooms(AvailableRooms availableRooms[], int numRecords)
{
	ofstream outFile("Available Rooms.dat", ios::binary);

	if (!outFile) {
		cout << "The file couldn't be stored.";
		exit(1);
	}

	for (int i = 1; i <= numRecords; i++)
	{
		outFile.write(reinterpret_cast<const char *>(&availableRooms[i]), sizeof(AvailableRooms));
	}

	outFile.close();
}