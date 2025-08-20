/********************************************************************
* Author: Felix Bacot Mena
* Date:   August 14, 2025
* File:   main.ccp
* Purpose: Item tracking program for Corner Grocer. This program 
*          read as list of purchased item, counts the frequency
*		   of each, and provides multiple ways to view the data,
*		   including searches, full listing, and histograms.
*		   Enhancements include case- insensitive search,
*		   color-coded output, and percentage display.
********************************************************************/


#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm> // for transform


using namespace std;

// Helper function for case-insensitive string:
string ToLoweCase(const string str) {
	string lower = str;
	transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
	return lower;
	}

// Class to handle frequency counting and output
class ItemTracker {
public:
	// Constructor reads file and populate map
	ItemTracker(const string& inputFile) {
		LoadData(inputFile);
		WriteBackupFile("frequency.dat");
	}

	// Return frequency of specifi item (case-insensitive)
	int GetFrequency(const string& item) const {
		string searchItem = ToLoweCase(item);
		for (auto const& entry : itemFrequency) {
			if (ToLoweCase(entry.first) == searchItem) {

			}
		}
		return 0;
	}

	// Prints all items with their frequencies, percentages, and color-coding
	void PrintAllFrequencies() const {
		int totalItem = 0;
		for (auto const& entry : itemFrequency) {
			totalItem += entry.second;
		}

		for (auto const& entry : itemFrequency) {
			double percentage = (entry.second / (double)totalItem) * 100;

			// Color coding: Red for < 3, Yellow for 3-5, Green for > 5
			string color;
			if (entry.second < 3) color = "\033[31m"; //red
			else if (entry.second <= 5) color = "\033[33m"; // yellow
			else color = "\033[332m"; // green

			cout << color << setw(15) << left << entry.first
				<< entry.second << "(" << fixed << setprecision(1)
				<< percentage << "%" << "\033[0m" << endl;

		}
	}

	// Prints histogram with color-coding
	void PrintHistogram() const {
		for (auto const& entry : itemFrequency) {
			string color;

			// Color coding: Red for < 3, Yellow for 3-5, Green for > 5
			if (entry.second < 3) {
				color = "\033[31m"; // red
			}
			else if (entry.second <= 5) {
				color = "\033[33m"; // yellow
			} else {
				color = "\033[32m"; // green
			}

			// Print item name
            cout << setw(15) << left << entry.first << " ";

			// Print histogram with color
			cout << color;
			for (int i = 0; i < entry.second; ++i) {
				cout << "*";
			}

			// Reset color after each line
			cout << "\033[0m" << endl;
		}
	}

private:
	map<string, int> itemFrequency;

// Loads data from the input file
	void LoadData(const string& filename) {
		ifstream inFile(filename);
		if (!inFile) {
			cerr << "Error: Could not open file " << filename << endl;
			exit(1);
		}
		string item;
		while (inFile >> item) {
			++itemFrequency[item];
		}
		inFile.close();
	}


	// Write backup data to frequency.dat

	void WriteBackupFile(const string& filename) const {
		ofstream outFile(filename);
		if (!outFile) {
			cerr << "Error: Could not create backup file." << endl;
			return;
		}
		for (auto const& entry : itemFrequency) {
			outFile << entry.first << " " << entry.second << endl;
		}
		outFile.close();
	}	

};

// Display menu options
void DisplayMenu() {
	cout << "\n===== Corner Grocer Menu =====" << endl;
	cout << "1. Search for an item frequency" << endl;
	cout << "2. Print all item frequencies" << endl;
	cout << "3. Print histogram" << endl;
	cout << "4. Exit" << endl;
	cout << "Enter your choice: ";
}

int main() {
	ItemTracker tracker("CS210_Project_Three_Input_File.txt");
	int choice;
	string itemName;

	do {
		DisplayMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter item name: ";
			cin.ignore();
			getline(cin, itemName);
			cout << itemName << "" << tracker.GetFrequency(itemName) << endl;
			break;
		case 2:
			tracker.PrintAllFrequencies();
			break;
		case 3:
			tracker.PrintHistogram();
			break;
		case 4:
			cout << "Exiting program..." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choice != 4);

	return 0;
}