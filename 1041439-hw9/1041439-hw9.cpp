#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct AvailableRooms
{
	char date[12];
	unsigned int singleDayAvailRooms[6];
	// singleDayAvailRooms[0]: not used
	// singleDayAvailRooms[1]: the number of available superior rooms
	// singleDayAvailRooms[2]: the number of available deluxe rooms
	// singleDayAvailRooms[3]: the number of available deluxe twin rooms
	// singleDayAvailRooms[4]: the number of available superior suites
	// singleDayAvailRooms[5]: the number of available deluxe suites
};

void loadFromFile(AvailableRooms availableRooms[], int &numRecords);
void makeReservation(AvailableRooms availableRooms[], int numRecords);
void saveToFile(AvailableRooms availableRooms[], int numRecords);

int main()
{
	AvailableRooms availableRooms[200] = { { "", 0, 0, 0, 0, 0 } };

	int numRecords;

	loadFromFile(availableRooms, numRecords); // read all records of the file availableRooms.dat,
	// put them into the array availableRooms, and
	// disply them on the screen

	makeReservation(availableRooms, numRecords); // make a room reservation; the numbers of available rooms
	// of the reserved room type and dates shoule be adjust

	saveToFile(availableRooms, numRecords); // save the modified available rooms information into the file availableRooms.dat

	loadFromFile(availableRooms, numRecords);

	system("pause");
}

void loadFromFile(AvailableRooms availableRooms[], int &numRecords)
{
	ifstream inFile("availableRooms.dat", ios::binary);
	if (!inFile){
		cout << "The file couldn't be opend." << endl;
		exit(1);
	}

	numRecords = 0;
	while (!inFile.eof()){
		inFile.read(reinterpret_cast<char *>(&availableRooms[numRecords]), sizeof(AvailableRooms));
		numRecords++;
	}
	for (int i = 0; i < numRecords - 2; i++){
		cout << left << setw(10) << availableRooms[i].date;
		for (int j = 1; j < 6; j++){
			cout << " " << availableRooms[i].singleDayAvailRooms[j];
		}
		cout << endl;
	}
	cout << endl;


}

void makeReservation(AvailableRooms availableRooms[], int numRecords)
{
	char arrivalDate[12], departureDate[12];
	cout << "Please input the arrival date(yyyy - mm - dd) : ";
	cin >> arrivalDate;
	cout << endl;
	cout << "Please input the departure date(yyyy - mm - dd) : ";
	cin >> departureDate;

	cout << endl;

	cout << "Select Room Type:\n"
		<< "1. Superior Room\n"
		<< "2. Deluxe Room\n"
		<< "3. Deluxe Twin Room\n"
		<< "4. Superior Suite\n"
		<< "5. Deluxe Suite\n";

	int choice;
	do {
		cout << "? ";
		cin >> choice;
	} while ((choice < 1) || (choice > 5));
	cout << endl;

	int styleofroom;
	int amount;
	switch (choice)
	{
	case 1:
		styleofroom = 1;
		break;
	case 2:
		styleofroom = 2;
		break;
	case 3:
		styleofroom = 3;
		break;
	case 4:
		styleofroom = 4;
		break;
	case 5:
		styleofroom = 5;
		break;

	}
	cout << "How many rooms ?";
	cin >> amount;

	int checkinday;
	int checkoutday;
	int match = 0;
	for (int i = 0; i < numRecords - 2; i++){
		for (int j = 0; j < 12; j++){
			if (arrivalDate[j] == availableRooms[i].date[j])
				match++;
			if (match == 11){
				checkinday = i;
			}
		}
		match = 0;
	}
	for (int i = 0; i < numRecords - 2; i++){
		for (int j = 0; j < 12; j++){
			if (departureDate[j] == availableRooms[i].date[j])
				match++;
			if (match == 11){
				checkoutday = i;
			}
		}
		match = 0;
	}

	for (int i = checkinday; i <= checkoutday; i++)
		availableRooms[i].singleDayAvailRooms[styleofroom] -= amount;

}

void saveToFile(AvailableRooms availableRooms[], int numRecords)
{
	ofstream outFile("availableRooms.dat", ios::binary);

	if (!outFile) {
		cout << "The file couldn't be stored.";
		exit(1);
	}

	for (int i = 0; i < numRecords-2; i++)
	{
		outFile.write(reinterpret_cast<const char *>(&availableRooms[i]), sizeof(AvailableRooms));
	}

	outFile.close();
}