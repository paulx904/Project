#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string.h>
using namespace::std;

struct Date
{
	int year;
	int month;
	int day;
	int hour;
};

struct MemberRecord
{
	char accountNumber[24]; // account number
	char password[24];      // password
	char IDNumber[12];      // ID number
	char name[8];           // name
};

struct ReservationRecord
{
	char accountNumber[24]; // account number
	int branchCode;           // branch code
	Date date;                // reservation date
	int hour;                 // reservation hour
	int boxTypeCode;          // box type code
	int numCustomers;         // number of customers
};

char brancheNames[16][24] = { "", "Taipei Dunhua South", "Taipei SOGO", "Taipei Songjiang",
"Taipei Nanjing", "Taipei Linsen", "Taipei Zhonghua New",
"Banqiao Guanqian", "Yonghe Lehua", "Taoyuan Zhonghua",
"Zhongli Zhongyang", "Hsinchu Beida", "Taichung Ziyou",
"Chiayi Ren'ai", "Tainan Ximen", "Kaohsiung Zhonghua New" };

// input memberDetails from the file Members.dat
void loadMemberDetails(MemberRecord memberDetails[], int &numMembers);

// input reservations from the file Reservations.dat
void loadReservations(ReservationRecord reservations[], int &numReservations);

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

// login and display the submenu
void login(MemberRecord memberDetails[], int numMembers, ReservationRecord reservations[], int &numReservations);

// there exists a member with specified accountNumber and password
bool legal(char accountNumber[], char password[], MemberRecord memberDetails[], int &numMembers);

// add a new reservation for the member with specified account number
void reservation(char accountNumber[], ReservationRecord reservations[], int &numReservations);

// compute the current date
void compCurrentDate(Date &currentDate);

// compute 7 dates which is starting from the current date
void compAvailableDates(Date currentDate, Date availableDate[]);

// display all fields of reservation
void output(ReservationRecord reservation);

// display all reservations for the member with specified account number,
// then let the member to choose one of them to delete
void queryDelete(char accountNumber[], ReservationRecord reservations[], int &numReservations);

// add a new member
void registration(MemberRecord memberDetails[], int &numMembers);

// return true if IDNumber belongs to memberDetails
bool existingID(char IDNumber[], MemberRecord memberDetails[], int &numMembers);

// return true if accountNumber belongs to memberDetails
bool existingAccount(char accountNumber[], MemberRecord memberDetails[], int &numMembers);

// output all memberDetails into the file Members.dat
void saveMemberDetails(MemberRecord memberDetails[], int numMembers);

// output all reservations into the file Reservations.dat
void saveReservations(ReservationRecord reservations[], int numReservations);

int main()
{
	MemberRecord memberDetails[100] = {};     // member details for all members
	ReservationRecord reservations[100] = {}; // all reservations
	int numMembers = 0;      // number of members
	int numReservations = 0; // number of reservations 

	loadMemberDetails(memberDetails, numMembers);
	loadReservations(reservations, numReservations);

	cout << "Welcome to the Cashbox Party World!\n\n";

	int choice;

	while (true)
	{
		cout << "1 - Login\n";
		cout << "2 - Registration\n";
		cout << "3 - End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			login(memberDetails, numMembers, reservations, numReservations);
			break;

		case 2:
			registration(memberDetails, numMembers);
			break;

		case 3:
	
			saveMemberDetails(memberDetails, numMembers);//刪除註解
			saveReservations(reservations, numReservations);//刪除註解
			cout << "Thank you! Goodbye!\n\n";
			system("pause");
			return 0;

		default:
			cout << "\nIncorrect choice!\n";
			break;
		}
	}

	system("pause");
}

void login(MemberRecord memberDetails[], int numMembers, ReservationRecord reservations[], int &numReservations)
{
	char accountNumber[24] = "";
	char password[24] = "";

	do {
		cout << "Please enter your account number: ";
		cin >> accountNumber;
		cout << "Enter your password: ";
		cin >> password;

	} while (!legal(accountNumber, password, memberDetails, numMembers));
	
	

	cin.ignore();

	int choice;

	while (true)
	{
		cout << "\n1 - Make Reservation\n";
		cout << "2 - Reservation Enquiry/Canceling\n";
		cout << "3 - End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			reservation(accountNumber, reservations, numReservations);
			break;

		case 2:
			queryDelete(accountNumber, reservations, numReservations);//刪除註解
			break;

		case 3:
			return;

		default:
			cout << "\nIncorrect choice!\n";
			break;
		}
	}
}

bool legal(char accountNumber[], char password[], MemberRecord memberDetails[], int &numMembers)
{
	for (int i = 0; i <= numMembers; i++)
	if (strcmp(accountNumber, memberDetails[i].accountNumber) == 0 &&
		strcmp(password, memberDetails[i].password) == 0)
		return true;

	cout << "\nInvalid account number or password. Please try again.\n\n";
	return false;
}

/*
void compCurrentDate( Date &currentDate )
{
currentDate.year = 2015;
currentDate.month = 12;
currentDate.day = 28;
currentDate.hour = 12;
}
*/

/*
void compCurrentDate( Date &currentDate )
{
currentDate.year = 2016;
currentDate.month = 2;
currentDate.day = 26;
currentDate.hour = 23;
}
*/

/*
void compCurrentDate( Date &currentDate )
{
currentDate.year = 2015;
currentDate.month = 2;
currentDate.day = 26;
currentDate.hour = 23;
}
*/

void compCurrentDate(Date &currentDate)
{
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s(&structuredTime, &rawTime);

	currentDate.year = structuredTime.tm_year + 1900;
	currentDate.month = structuredTime.tm_mon + 1;
	currentDate.day = structuredTime.tm_mday;
	currentDate.hour = structuredTime.tm_hour;
}

void output(ReservationRecord reservation)
{
	char boxTypes[3][16] = { "", "Standard", "Party" };
	
	cout << setw(17) << reservation.accountNumber
		<< setw(26) << brancheNames[reservation.branchCode]
		<< setw(8) << reservation.date.year << '-'
		<< setw(2) << setfill('0') << reservation.date.month << '-'
		<< setw(2) << setfill('0') << reservation.date.day
		<< setw(8) << setfill(' ') << reservation.hour
		<< setw(13) << boxTypes[reservation.boxTypeCode]
		<< setw(19) << reservation.numCustomers << endl;
}

bool existingID(char IDNumber[], MemberRecord memberDetails[], int &numMembers)
{
	for (int i = 0; i < numMembers; i++)
	if (strcmp(IDNumber, memberDetails[i].IDNumber) == 0)
		return true;
	return false;
}

bool existingAccount(char accountNumber[], MemberRecord memberDetails[], int &numMembers)
{
	for (int i = 0; i < numMembers; i++)
	if (strcmp(accountNumber, memberDetails[i].accountNumber) == 0)
		return true;
	return false;
}

void loadMemberDetails(MemberRecord memberDetails[], int &numMembers)
{
	ifstream inFile_Members("Members.dat", ios::in | ios::binary);
	if (!inFile_Members){
		cout << "Load \"Members.dat\" error.";
		exit(1);
	}
	numMembers = -1;
	while (inFile_Members && !inFile_Members.eof()){
		numMembers++;
		//inFile_Members.getline(reinterpret_cast<char *> (&memberDetails[numMembers]), sizeof(MemberRecord));  //deleted
		inFile_Members.read(reinterpret_cast<char *> (&memberDetails[numMembers]), sizeof(MemberRecord)); //add
		cout << memberDetails[numMembers].accountNumber;
	}
	numMembers++;

	inFile_Members.close();

}

void loadReservations(ReservationRecord reservations[], int &numReservations)
{
	ifstream inFile_Reservations("Reservations.dat", ios::in | ios::binary);

	if (!inFile_Reservations){
		cout << "Load \"Reservations.dat\" error.";
		exit(1);
	}
	numReservations = -1;
	while (inFile_Reservations && !inFile_Reservations.eof()){
		numReservations++;
		//inFile_Reservations.getline(reinterpret_cast< char * > (&reservations[numReservations]), sizeof(ReservationRecord)); //deleted
		inFile_Reservations.read(reinterpret_cast< char * > (&reservations[numReservations]), sizeof(ReservationRecord)); //add
	}
	numReservations++;
	inFile_Reservations.close();

}

int inputAnInteger(int begin, int end)
{
	int choice;
	cin >> choice;
	if (choice<begin || choice>end)
		return -1;
	else
		return choice;

}

void registration(MemberRecord memberDetails[], int &numMembers)
{
	char accountnumber[24];
	char password[24];
	char ID[12];
	char name[8];
	cout << "Input your ID Number:";
	cin.getline(ID, 12);
	cin.clear();
	cin.getline(ID, 12);
	if (existingID(ID, memberDetails, numMembers) != 1){
		strcpy_s(memberDetails[numMembers].IDNumber, 12, ID);


		cin.clear();


		cout << "Input your Name:";
		cin.getline(name, 8);
		strcpy_s(memberDetails[numMembers].name, 8, name);

		cin.clear();

		cout << "Choose an account number:";
		cin.getline(accountnumber, 24);
		if (existingAccount(accountnumber, memberDetails, numMembers) != 1){
			strcpy_s(memberDetails[numMembers].accountNumber, 24, accountnumber);

			cin.clear();

			cout << "Choose a password:";
			cin.getline(password, 24);
			strcpy_s(memberDetails[numMembers].password, 24, password);

			cin.clear();

			cout << "Registration Completed!" << endl;

			//cout << ID << " " << name << " " << accountnumber << " " << password << endl; //deleted
		}
		else //add
		cout << "Account number \"" << accountnumber << "\" has been used!" << endl;
	}
	else //add
	cout << "You are already a member!" << endl;
}

void reservation(char accountNumber[], ReservationRecord reservations[], int &numReservations)
{
	strcpy_s(reservations[numReservations].accountNumber, accountNumber); //add
	int choice_branche;
	for (int i = 1; i <= 15; i++)
		cout << i << "." << brancheNames[i] << endl;

	do{
		cout << "Enter your choice(0 to end) :";
		cin >> choice_branche;
		if (choice_branche == 0) //add
			return;
	} while (choice_branche < 1 || choice_branche>15);
	reservations[numReservations].branchCode = choice_branche; //add

	Date availableDates[8] = {};
	Date currentDate = {};
	compAvailableDates(currentDate, availableDates);
	compCurrentDate(currentDate); //add

	int choice_days;

	do{
		cout << "Enter your choice (0 to end):";
		cin >> choice_days;
		if (choice_days == 0) //add
			return;
	} while (choice_days < 0 || choice_days > 7);

	
	int choice_hour;
	do{
		//if (availableDates[choice_days].year == currentDate.year && availableDates[choice_days].month == currentDate.month&&availableDates[choice_days].day == currentDate.day)) //deleted
		if (choice_days==1&&currentDate.hour!=23) //add
			cout << "Enter hour(" << currentDate.hour << "~23)" << endl; 
		else
			cout << "Enter hour (0~23):";

		cin >> choice_hour;
		reservations[numReservations].hour = choice_hour; //add
	} while (choice_hour < 0 || choice_hour > 23);
	
	reservations[numReservations].date.year = availableDates[choice_days].year;
	reservations[numReservations].date.month = availableDates[choice_days].month;
	reservations[numReservations].date.day = availableDates[choice_days].day;
	reservations[numReservations].date.hour = availableDates[choice_days].hour;

	int choice_customers;
	do{
		cout << "Enter the number of customers (1~30, 0 to end):";
		cin >> choice_customers;
		if (choice_customers == 0) //add
			return;
	} while (choice_customers < 1 || choice_customers>30);
	reservations[numReservations].numCustomers = choice_customers;
	
	//add
	cout << "1. Standard Room" << endl
		<< "2. Party Room" << endl << endl;
	
	int choice_boxtypes;
	do{
		cout << "Enter your choice(0 to end) :";
		cin >> choice_boxtypes;
		if (choice_boxtypes == 0)
			return;
	} while (choice_boxtypes < 1 || choice_boxtypes > 2);
	reservations[numReservations].boxTypeCode = choice_boxtypes;
	cout << "   Account Number                    Branch          Date    Hour    Room Type    No of Customers" << endl;
	output(reservations[numReservations]);
	//add
}

void compAvailableDates(Date currentDate, Date availableDates[])
{
	compCurrentDate(currentDate);
	cout << "The current hour is " << currentDate.year << "/" << currentDate.month << "/" << currentDate.day << ":" << currentDate.hour << endl;

	int dates[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if ((currentDate.year % 4 == 0 && currentDate.year % 100 != 0) || currentDate.year % 400 == 0)
		dates[2] = 29;
	if (((currentDate.year + 1) % 4 == 0 && (currentDate.year + 1) % 100 != 0) || (currentDate.year + 1) % 400 == 0)
		dates[2] = 29;
	


	cout << "Available days:" << endl;


	if (currentDate.hour  < 23){
		cout << 1 << "." << currentDate.year << "/" << currentDate.month << "/" << currentDate.day << endl;
		availableDates[1].year = currentDate.year;
		availableDates[1].month = currentDate.month;
		availableDates[1].day = currentDate.day;
		availableDates[1].hour = currentDate.hour;

	}
	else if (currentDate.day  < dates[currentDate.month]){
		cout << 1 << "." << currentDate.year << "/" << currentDate.month << "/" << currentDate.day + 1 << endl;
		availableDates[1].year = currentDate.year;
		availableDates[1].month = currentDate.month;
		availableDates[1].day = currentDate.day + 1;
	}
	else if (currentDate.month < 12){
		cout << 1 << "." << currentDate.year << "/" << currentDate.month + 1 << "/" << 1 << endl;
		availableDates[1].year = currentDate.year;
		availableDates[1].month = currentDate.month + 1;
		availableDates[1].day = 1;
	}
	else {
		cout << 1 << "." << currentDate.year + 1 << "/" << 1 << "/" << 1 << endl;
		availableDates[1].year = currentDate.year + 1;
		availableDates[1].month = 1;
		availableDates[1].day = 1;
	}

	for (int i = 2; i <= 7; i++){
		/*if (availableDates[i - 1].hour < 23){
			cout << i << "." << availableDates[i - 1].year << "/" << availableDates[i - 1].month << "/" << availableDates[i - 1].day + 1 << endl;
			availableDates[i].year = availableDates[i - 1].year;
			availableDates[i].month = availableDates[i - 1].month;
			availableDates[i].day = availableDates[i - 1].day + 1;
			availableDates[i].hour = availableDates[i - 1].hour;

		}*/ //deleted

		if (availableDates[i-1].day  < dates[availableDates[i-1].month]){
			availableDates[i].year = availableDates[i - 1].year;
			availableDates[i].month = availableDates[i - 1].month;
			availableDates[i].day = availableDates[i - 1].day + 1;
			availableDates[i].hour = availableDates[i - 1].hour;
			cout << i << "." << availableDates[i].year << "/" << availableDates[i].month << "/" << availableDates[i].day << endl;

		}
		else if (availableDates[i - 1].month < 12){
			availableDates[i].year = availableDates[i - 1].year;
			availableDates[i].month = availableDates[i - 1].month + 1;
			availableDates[i].day = 1;
			cout << i << "." << availableDates[i].year << "/" << availableDates[i].month << "/" << availableDates[i].day << endl;
		}
		else {
			availableDates[i].year = availableDates[i - 1].year + 1;
			availableDates[i].month = 1;
			availableDates[i].day = 1;
			cout << i << "." << availableDates[i].year << "/" << availableDates[i].month << "/" << availableDates[i].day << endl;
		}
	}


}

void saveMemberDetails(MemberRecord memberDetails[], int numMembers)
{
	
	ofstream OutFile_Members("Members.dat", ios::in | ios::binary);

	if (!OutFile_Members){
		cout << "Load \"Members.dat\" error.";
		exit(1);
	}
	for (int i = 0; i <= numMembers; i++)
		OutFile_Members.write(reinterpret_cast<char *> (&memberDetails[i]), sizeof(MemberRecord));
	
	OutFile_Members.close();
}

void saveReservations(ReservationRecord reservations[], int numReservations)
{
	ofstream OutFile_Reservations("Reservations.dat", ios::in | ios::binary);

	if (!OutFile_Reservations){
		cout << "Load \"Reservations.dat\" error.";
		exit(1);
	}

	for (int i = 0; i <= numReservations; i++)
		OutFile_Reservations.write(reinterpret_cast<char *> (&reservations[i]), sizeof(ReservationRecord));
	
	OutFile_Reservations.close();
}


// add
void queryDelete(char accountNumber[], ReservationRecord reservations[], int &numReservations)
{

	char boxTypes[3][16] = { "", "Standard", "Party" };
	cout << "   Account Number                   Branch          Date    Hour    Room Type    No of Customers" << endl;

	int temp = 0; 
	int list[30] = {};
	for (int i = 0; i < numReservations; i++){
		if (strcmp(accountNumber, reservations[i].accountNumber) == 0){
			temp++;
			list[temp] = i;
			cout << temp << "." << setw(17)
				<< reservations[i].accountNumber
				<< setw(26) << brancheNames[reservations[i].branchCode]
				<< setw(8) << reservations[i].date.year << '-'
				<< setw(2) << setfill('0') << reservations[i].date.month << '-'
				<< setw(2) << setfill('0') << reservations[i].date.day
				<< setw(8) << setfill(' ') << reservations[i].hour
				<< setw(13) << boxTypes[reservations[i].boxTypeCode]
				<< setw(19) << reservations[i].numCustomers << endl;
		}
	}

	int cancel;
	do{
		cout << "Choose a reservation to cancel (0: keep all reservations):";
		cin >> cancel;
		if (cancel == 0)
			return;
	} while (cancel < 1 || cancel>temp);
	
	reservations[list[cancel]].accountNumber[0] = NULL;
	reservations[list[cancel]].boxTypeCode = NULL;
	reservations[list[cancel]].branchCode = NULL;
	reservations[list[cancel]].date.year = NULL;
	reservations[list[cancel]].date.month = NULL;
	reservations[list[cancel]].date.hour = NULL;
	reservations[list[cancel]].hour = NULL;
	reservations[list[cancel]].numCustomers = NULL;
	saveReservations(reservations, list[cancel]);


}

//add