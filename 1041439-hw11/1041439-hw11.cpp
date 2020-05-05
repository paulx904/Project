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

struct ReservationInfo
{
	char id[12];
	char name[12];
	char mobile[12];
	int roomType;
	int numRooms;
	Date checkInDate;
	Date checkOutDate;
};

struct AvailableRooms
{
	Date date;
	int availableRooms[6]; // number of available rooms
};

int roomRate[6] = { 0, 5390, 6270, 6270, 6820, 8470 };
int numRooms[6] = { 0, 9, 5, 3, 5, 4 };
char roomTypeName[6][20] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room", "Superior Suite", "Deluxe Suite" };
int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int sumOfday;

int enterChoice();
void makeReservation();
void display(ReservationInfo reservation, time_t numNights);
void computeCurrentDate(Date &currentDate);
void inputDates(Date currentDate, Date &checkInDate, Date &checkOutDate);
void loadAvailableRooms(AvailableRooms availableRooms[], int &numRecords);
void initializeAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords);
void adjustAvailableRooms(AvailableRooms availableRooms[], Date currentDate, int &numRecords);
int compareDates(Date date1, Date date2);
void displayDate(Date date);
bool legal(char id[]);
void saveReservationInfo(ReservationInfo reservation);
void saveAvailableRooms(AvailableRooms availableRooms[], int numRecords);
void ReservationInquiry();

int main()
{
	cout << "Evergreen Laurel Hotel Online Reservation System\n";

	int choice;

	while ((choice = enterChoice()) != 3)
	{
		switch (choice)
		{
		case 1:
			makeReservation();
			break;
		case 2:
			ReservationInquiry();
			break;
		default:
			cerr << "\nInput Error!" << endl;
		}
	}

	cout << endl;

	system("pause");
}

int enterChoice()
{
	cout << "\nInput your choice¡G\n"
		<< "1. Making Reservation\n"
		<< "2. Reservation Inquiry\n"
		<< "3. end program\n? ";

	int menuChoice;
	cin >> menuChoice;
	return menuChoice;
}

void makeReservation()
{
	ReservationInfo reservation;
	Date currentDate = {};
	AvailableRooms availableRooms[184] = {};

	computeCurrentDate(currentDate);
	inputDates(currentDate, reservation.checkInDate, reservation.checkOutDate);

	int numRecords = 0;

	loadAvailableRooms(availableRooms, numRecords);
	
	if (numRecords == 0 || compareDates(availableRooms[numRecords].date, currentDate) == -1)
		initializeAvailableRooms(availableRooms, currentDate, numRecords);
	else if (compareDates(availableRooms[1].date, currentDate) == -1){
		adjustAvailableRooms(availableRooms, currentDate, numRecords);
	}
	cout << "The number of available rooms of each room type:\n\n";
	cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";
	
	for (int i = 1; i < numRecords; i++){
		if (reservation.checkInDate.year == availableRooms[i].date.year&&
			reservation.checkInDate.month == availableRooms[i].date.month&&
			reservation.checkInDate.day == availableRooms[i].date.day){
			do{
				
				sumOfday++;
				cout << availableRooms[i].date.year << "-"
					<< setw(2) << setfill('0') << availableRooms[i].date.month << "-"
					<< setw(2) << availableRooms[i].date.day
					<< setw(16) << setfill(' ') << availableRooms[i].availableRooms[1]
					<< setw(14) << availableRooms[i].availableRooms[2]
					<< setw(19) << availableRooms[i].availableRooms[3]
					<< setw(17) << availableRooms[i].availableRooms[4]
					<< setw(15) << availableRooms[i].availableRooms[5] << "\n";
				i++;
			} while (reservation.checkOutDate.year != availableRooms[i].date.year ||
				reservation.checkOutDate.month != availableRooms[i].date.month ||
				reservation.checkOutDate.day != availableRooms[i].date.day);
			break;
		}
		
	}


	do
	{
		cout << "Select Room Type¡G\n";
		cout << "1. Superior Room\n2. Deluxe Room\n3. Deluxe Twin Room\n4. Superior Suite\n5. Deluxe Suite\n?";
		cin >> reservation.roomType;
	} while (reservation.roomType < 1 || reservation.roomType > 6);

	do{
		cout << "Number of rooms(" << numRooms[reservation.roomType] << " rooms available) : ";
		cin >> reservation.numRooms;
	} while (reservation.numRooms <= 0 || reservation.numRooms > numRooms[reservation.roomType]);

	do{
		cout << "ID Number:";
		cin >> reservation.id;
	} while (!legal(reservation.id));

	cout << "Name: ";
	cin >> reservation.name;
	cout << "Mobile Phone¡G";
	cin >> reservation.mobile;

	cout << "Your reservations :\n\n";
	cout << "Name     Fare               Mobile          Room type   Number of rooms    Check in date           Check out date\n";
	cout << reservation.name
		<< setw(8) << sumOfday*roomRate[reservation.roomType] * reservation.numRooms
		<< setw(20) << reservation.mobile
		<< setw(16) << reservation.roomType
		<< setw(12) << reservation.numRooms
		<< setw(22) << reservation.checkInDate.year << " - " << reservation.checkInDate.month << " - " << reservation.checkInDate.day
		<< setw(14) << reservation.checkOutDate.year << " - " << reservation.checkOutDate.month << " - " << reservation.checkOutDate.day;

	for (int i = 1; i < numRecords; i++){
		if (reservation.checkInDate.year == availableRooms[i].date.year&&
			reservation.checkInDate.month == availableRooms[i].date.month&&
			reservation.checkInDate.day == availableRooms[i].date.day){
			do{
				availableRooms[i].availableRooms[reservation.roomType] -= reservation.numRooms;
				i++;
			} while (reservation.checkOutDate.year != availableRooms[i].date.year ||
				reservation.checkOutDate.month != availableRooms[i].date.month ||
				reservation.checkOutDate.day != availableRooms[i].date.day);
			break;
		}

	}


	saveReservationInfo(reservation);
	saveAvailableRooms(availableRooms, numRecords);
}


void computeCurrentDate(Date &currentDate)
{
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s(&structuredTime, &rawTime);

	currentDate.year = structuredTime.tm_year + 1900;
	currentDate.month = structuredTime.tm_mon + 1;
	currentDate.day = structuredTime.tm_mday;
}

void inputDates(Date currentDate, Date &checkInDate, Date &checkOutDate)
{
	int choice;
	cout << "\nPlease Input Check In Date\n\n";
	do
	{
		cout << "Month :\n";
		for (int i = 1; i <= 6; i++){
			if (currentDate.month + i - 1 <= 12)
				cout << i << "." << currentDate.year << "-" << currentDate.month + i - 1 << endl;
			else
				cout << i << "." << currentDate.year + 1 << "-" << currentDate.month + i - 13 << endl;
		}
		cout << "?";
		cin >> choice;

		switch (choice)
		{
		case 1:
			checkInDate.month = currentDate.month;
			checkInDate.year = currentDate.year;
			break;
		case 2:
			if (currentDate.month + 1 <= 12){
				checkInDate.month = currentDate.month + 1;
				checkInDate.year = currentDate.year;
			}
			else{
				checkInDate.month = 1;
				checkInDate.year = currentDate.year + 1;
			}
			break;
		case 3:
			if (currentDate.month + 2 <= 12){
				checkInDate.month = currentDate.month + 2;
				checkInDate.year = currentDate.year;
			}
			else{
				checkInDate.month = currentDate.month + 2 - 12;
				checkInDate.year = currentDate.year + 1;
			}
			break;
		case 4:
			if (currentDate.month + 3 <= 12){
				checkInDate.month = currentDate.month + 3;
				checkInDate.year = currentDate.year;
			}
			else{
				checkInDate.month = currentDate.month + 3 - 12;
				checkInDate.year = currentDate.year + 1;
			}
			break;
		case 5:
			if (currentDate.month + 4 <= 12){
				checkInDate.month = currentDate.month + 4;
				checkInDate.year = currentDate.year;
			}
			else{
				checkInDate.month = currentDate.month + 4 - 12;
				checkInDate.year = currentDate.year + 1;
			}
			break;
		case 6:
			if (currentDate.month + 5 <= 12){
				checkInDate.month = currentDate.month + 5;
				checkInDate.year = currentDate.year;
			}
			else{
				checkInDate.month = currentDate.month + 5 - 12;
				checkInDate.year = currentDate.year + 1;
			}
			break;

		}
	} while (choice < 1|| choice > 6);

	cout << endl;

	if (currentDate.month == checkInDate.month){
		do{
			cout << "Day (" << currentDate.day << " ~ " << days[currentDate.month] << ") :\n";
			cin >> choice;
		} while (choice < currentDate.day || choice > days[currentDate.month]);
	}
	else{
		do{
			cout << "Day (1 ~ " << days[checkInDate.month] << ") :\n";
			cin >> choice;
		} while (choice <  1 || choice > days[checkInDate.month]);
	}
	
	checkInDate.day = choice;

	cout << "\nPlease Input Check Out Date\n\n";
	do
	{
		cout << "Month :\n";
		for (int i = 1; i <= 6; i++){
			if (currentDate.month + i - 1 <= 12)
				cout << i << "." << currentDate.year << "-" << currentDate.month + i - 1 << endl;
			else
				cout << i << "." << currentDate.year + 1 << "-" << currentDate.month + i - 13 << endl;
		}
		cout << "?";
		cin >> choice;

		switch (choice)
		{
		case 1:
			checkOutDate.month = currentDate.month;
			checkOutDate.year = currentDate.year;
			break;
		case 2:
			if (currentDate.month + 1 <= 12){
				checkOutDate.month = currentDate.month + 1;
				checkOutDate.year = currentDate.year;
			}
			else{
				checkOutDate.month = 1;
				checkOutDate.year = currentDate.year + 1;
			}
			break;
		case 3:
			if (currentDate.month + 2 <= 12){
				checkOutDate.month = currentDate.month + 2;
				checkOutDate.year = currentDate.year;
			}
			else{
				checkOutDate.month = currentDate.month + 2 - 12;
				checkOutDate.year = currentDate.year + 1;
			}
			break;
		case 4:
			if (currentDate.month + 3 <= 12){
				checkOutDate.month = currentDate.month + 3 ;
				checkOutDate.year = currentDate.year;
			}
			else{
				checkOutDate.month = currentDate.month + 3 - 12;
				checkOutDate.year = currentDate.year + 1;
			}
			break;
		case 5:
			if (currentDate.month + 4 <= 12){
				checkOutDate.month = currentDate.month + 4;
				checkOutDate.year = currentDate.year;
			}
			else{
				checkOutDate.month = currentDate.month + 4 - 12;
				checkOutDate.year = currentDate.year + 1;
			}
			break;
		case 6:
			if (currentDate.month + 5 <= 12){
				checkOutDate.month = currentDate.month + 5;
				checkOutDate.year = currentDate.year;
			}
			else{
				checkOutDate.month = currentDate.month + 5 - 12;
				checkOutDate.year = currentDate.year + 1;
			}
			break;

		}
	} while (choice < 1 || choice > 6);

	cout << endl;

	if (checkOutDate.month == checkInDate.month){
		if (checkInDate.day != days[checkInDate.month])
		do{
			cout << "Day (" << checkInDate.day + 1 << " ~ " << days[checkOutDate.month] << ") :\n";
			cin >> choice;
		} while (choice < checkInDate.day || choice > days[checkOutDate.month]);
		else
		do{
			cout << "Day (" << checkInDate.day << " ~ " << days[checkOutDate.month] << ") :\n";
			cin >> choice;
		} while (choice!=checkInDate.day);
	}
	else{
		do{
			cout << "Day (1 ~ " << days[checkOutDate.month] << ") :\n";
			cin >> choice;
		} while (choice <  1 || choice > days[checkOutDate.month]);
	}

	checkOutDate.day = choice;

	cout << "Check in date : " << checkInDate.year << " - " << checkInDate.month << " - " << checkInDate.day << endl
		<< "Check out date : " << checkOutDate.year << " - " << checkOutDate.month << " - " << checkOutDate.day << endl;
		
}

void loadAvailableRooms(AvailableRooms availableRooms[], int &numRecords)
{
	ifstream inFile("Available Rooms.dat", ios::binary);
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
		else if (availableRooms[i - 1].date.month < 12){
			availableRooms[i].date.year = availableRooms[i - 1].date.year;
			availableRooms[i].date.month = availableRooms[i - 1].date.month + 1;
			availableRooms[i].date.day = 1;
		}
		else {
			availableRooms[i].date.year = availableRooms[i - 1].date.year + 1;
			availableRooms[i].date.month = 1;
			availableRooms[i].date.day = 1;
		}

		for (int j = 1; j <= 5; j++){
			if (temp <= numRecords){
				availableRooms[i].availableRooms[j] = availableRooms[temp + 1].availableRooms[j];

			}
			else
				availableRooms[i].availableRooms[j] = numRooms[j];
		}
		temp++;
	}
}

void saveReservationInfo(ReservationInfo reservation)
{
	ofstream outFile("Reservations.dat", ios::binary);
	
	if (!outFile) {
		cout << "The file couldn't be stored.";
		exit(1);
	}

	outFile.write(reinterpret_cast<const char *>(&reservation), sizeof(ReservationInfo));
	outFile.close();

}

bool legal(char id[])
{
	if (strlen(id) != 10)
		return false;


	for (int i = 2; i < 10; i++){
		if (id[i] != '0' && id[i] != '1' && id[i] != '2' && id[i] != '3' && id[i] != '4' &&
			id[i] != '5' && id[i] != '6' && id[i] != '7' && id[i] != '8' && id[i] != '9')
			return false;
	}

	if (id[1] != '1' && id[1] != '2')
		return false;
	
	if (id[0] != 'a' && id[0] != 'b' && id[0] != 'c' && id[0] != 'd' && id[0] != 'e' && id[0] != 'f'
		&& id[0] != 'g' && id[0] != 'h' && id[0] != 'i' && id[0] != 'j' && id[0] != 'k' && id[0] != 'l' && id[0] != 'm'
		&& id[0] != 'n' && id[0] != 'o' && id[0] != 'p' && id[0] != 'q' && id[0] != 'r' && id[0] != 's' && id[0] != 't'
		&& id[0] != 'u' && id[0] != 'v' && id[0] != 'w' && id[0] != 'x' && id[0] != 'y' && id[0] != 'z')
	return false;

	else
		return true;

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

void ReservationInquiry()
{
	ReservationInfo reservation;

	char id[10];
	cout << "nter Your ID Number¡G";
	cin >> id;
		
	ifstream inFile("Reservations.dat", ios::binary);
	while (!inFile.eof())
		inFile.read(reinterpret_cast<char *>(&reservation), sizeof(ReservationInfo));
	
	cout << "Your reservations :\n\n";
	cout << "Name     Fare               Mobile          Room type   Number of rooms    Check in date           Check out date\n";
	cout << reservation.name
		<< setw(8) << sumOfday*roomRate[reservation.roomType] * reservation.numRooms
		<< setw(20) << reservation.mobile
		<< setw(16) << reservation.roomType
		<< setw(12) << reservation.numRooms
		<< setw(22) << reservation.checkInDate.year << " - " << reservation.checkInDate.month << " - " << reservation.checkInDate.day
		<< setw(14) << reservation.checkOutDate.year << " - " << reservation.checkOutDate.month << " - " << reservation.checkOutDate.day;
}
 