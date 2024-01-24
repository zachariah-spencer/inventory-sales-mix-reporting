// Zachariah Spencer : Programming Languages : Project 3 : 12-10-23
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Represents an individual produce item, contains it's name as well as the unumber of times it is purchased
class Item {
public:
	Item();
	Item(string name, int numTimesPurchased);

	void setName(string name);
	void setNumTimesPurchased(int num);
	string getName();
	int getNumTimesPurchased();

	void incrementPurchaseCount();

private:
	string name;
	int numTimesPurchased;
};

// default constructor
Item::Item() {
	this->name = "noname";
	this->numTimesPurchased = -1;
}

// primary constructor
Item::Item(string name, int numTimesPurchased) {
	this->name = name;
	this->numTimesPurchased = numTimesPurchased;
}

// mutator methods
void Item::setName(string name){
	this->name = name;
}

void Item::setNumTimesPurchased(int num) {
	this->numTimesPurchased = num;
}

// accessor methods
string Item::getName() {
	return name;
}

int Item::getNumTimesPurchased() {
	return numTimesPurchased;
}

// increases the number of times an item was purchased by 1
// params: none
// returns: none
void Item::incrementPurchaseCount() {
	numTimesPurchased = numTimesPurchased + 1;
}

// program starts here
int main() {

	ifstream inFS;
	ofstream outFS;
	string queryItem;
	string scannedItem;
	map<string, Item> itemsList; // a map with item names as keys and Item objects as values
	bool quit = false;

	// open input data file and check to make sure it opened
	inFS.open("TestInput.txt");
	if (!inFS.is_open()) {
		cout << "Could not open file TestInput.txt" << endl;
		return 1;
	}

	// read input data from text file, for each unique item, create an item object and map it
	while (!inFS.eof()) {
		string scannedItemName;
		
		inFS >> scannedItemName;

		// if an item is not unique, find the already mapped item and increment how many times it was purchased
		if (itemsList.count(scannedItemName) == 1) {
			itemsList.at(scannedItemName).incrementPurchaseCount();
		}
		else {
			itemsList.emplace(scannedItemName, Item(scannedItemName, 1));
		}
	}

	// close input data file
	inFS.close();

	// create backup data file and verify it was created and opened for writing successfully
	outFS.open("frequency.dat");
	if (!outFS.is_open()) {
		cout << "Could not create backup file frequency.dat" << endl;
		return 1;
	}

	// iterate through the newly generated map and distribute item purchase reporting data into the backup file
	for (map<string, Item>::iterator it = itemsList.begin(); it != itemsList.end(); ++it) {
		string key = it->first;
		Item value = it->second;
		outFS << value.getName() << " " << to_string(value.getNumTimesPurchased()) << endl;
	}

	// close backup data file
	outFS.close();

	// begin main program loop
	while (!quit) {
		int selection;
		cout << "****MAIN MENU****" << endl;
		cout << "1. Individual Item Search" << endl;
		cout << "2. Item Sales Report" << endl;
		cout << "3. Item Sales Histogram" << endl;
		cout << "4. Exit Program" << endl;

		cout << endl;
		cout << "Please make a menu selection: " << endl;
		cin >> selection;

		switch (selection) {
		case 1:
			// prompts the user for an item to search for
			cout << "****INDIVIDUAL ITEM SEARCH****" << endl;
			cout << "Input the item you wish to look for: " << endl;
			cin >> queryItem;

			// tells the user if that item has been sold before and if so, how many times it was sold
			if (itemsList.count(queryItem) == 1) {
				string itemName = itemsList.at(queryItem).getName();
				string itemTimesPurchased = to_string(itemsList.at(queryItem).getNumTimesPurchased());
				cout << endl;
				cout << itemName << ": " << itemTimesPurchased << " sold" << endl;
			}
			else {
				cout << "No item by that name has been sold." << endl;
			}
			
			cout << endl << endl;
			break; 
		case 2:
			// generates a list of every item sold at the store alongside how many times each item was sold
			cout << "****ITEM SALES REPORT****" << endl;

			for (map<string, Item>::iterator it = itemsList.begin(); it != itemsList.end(); ++it) {
				string key = it->first;
				Item value = it->second;
				cout << value.getName() << " " << to_string(value.getNumTimesPurchased()) << endl;
			}

			cout << endl << endl;
			break; 
		case 3:
			// generates a list of very item sold at the store alongside a histogram visualization of how many times each was sold
			cout << "****ITEM SALES HISTOGRAM****" << endl;
			for (map<string, Item>::iterator it = itemsList.begin(); it != itemsList.end(); ++it) {
				string key = it->first;
				Item value = it->second;
				cout << setw(15);
				cout << value.getName() << "   ";

				for (int i = 0; i < value.getNumTimesPurchased(); ++i) {
					cout << setw(0);
					cout << "* ";
				}

				cout << endl;
			}
			
			cout << endl << endl;
			break; 
		case 4:
			// exits program
			cout << "Exiting program..." << endl;
			quit = true;

			break; 
		default:
			cout << "That is not a valid selection, please try again..." << endl << endl << endl;

			break; 
		}
	}

	return 0;
}