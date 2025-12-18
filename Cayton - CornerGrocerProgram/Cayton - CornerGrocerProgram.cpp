/* 
* Program: Corner Grocer Item Frequency Tracker
* File: Cayton - CornerGrocerProgram.cpp
* Author: Jakob Cayton
* Date: 2025-12-09
* 
* Discription:
* This program implements a Corner Grocer Item Frequency Tracker,
* which reads a list of grocery items from an input file, counts the frequency
* of each item, and provides various functionalities through a menu-driven interface.
* The program allows users to search for the frequency of specific items,
* display the entire item list, and visualize item frequencies using a histogram.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "ItemList.h"
using namespace std;

// Function delarations.
void mainMenu(ItemList* itemList);
void printMenu();
void handleFileIO(ItemList* itemList);

/*
* Main function where program execution begins.
* Creates ItemList object, handles file I/O, and runs the main menu.
* return Exit status of the program.
*/
int main() {
	// Create ItemList object using smart pointer.
	auto itemList = std::make_unique<ItemList>();

	// Initial file handling (reading from file and writing backup).
	// This function will exit the program if output file writing fails.
	handleFileIO(itemList.get());

	// Run main menu for user interaction.
	mainMenu(itemList.get());

	cout << "Goodbye!" << endl; // Exit program message.
	return 0; // End of program success.
}

/*
* Handles file input and output operations.
* Exits program if output file writing fails.
* Loops until a valid input file is provided.
* param itemList Pointer to the ItemList object for managing items.
*/
void handleFileIO(ItemList* itemList) {
	// Input and output file names.
	string inputFile = "";
	const string OUTPUT_FILE = "frequency.dat";
	cout << "Enter the input file name: ";
	cin >> inputFile;

	// Get items from input file into item list (handles file reading and sorting internally).
	// Loop until a valid file is provided.
	while (true) {
		try {
			itemList->GetItemsFromFile(inputFile);
			break; // Exit loop if successful (no exception thrown).
		}
		catch (const exception& e) {
			cout << e.what() << endl; // Display error message.
			cout << "Please enter a valid input file name: ";
			cin >> inputFile;
		}
	}

	// Write sorted and formatted item list to output file.
	// If an error occurs, display message and EXIT program.
	try {
		itemList->WriteItemListToFile(OUTPUT_FILE);
	}
	catch (const exception& e) {
		cout << e.what() << endl; // Display error message.
		cout << "No backup file created. Exiting program." << endl;
		exit(1); // Exit program with error code.
	}
}

/* 
* Displays the main menu and handles user interaction.
* param itemList Pointer to the ItemList object for managing items.
*/
void mainMenu(ItemList* itemList) {
	char choice = '0'; // User menu choice. Char is used to handle invalid input.
	string itemName; // Item name for searching frequency.
	bool exitMenu = false; // Flag to control menu loop.
	// Loop until user chooses to exit.
	while (!exitMenu) {
		printMenu(); // Display menu options.
		cin >> choice; // Get user choice.
		cout << endl; // New line for better output formatting.
		switch (choice) {
		case '1': // Search for Frequency of Item
			cout << "Enter the item name to search for its frequency: ";
			cin >> itemName;
			cout << "Frequency of '" << itemName << "': " << itemList->ItemFrequency(itemName) << endl;
			break;
		case '2': // Display Item List
			itemList->DisplayItemList();
			break;
		case '3': // Display Item Frequency Histogram
			itemList->DisplayItemHistogram();
			break;
		case '4': // Exit program
			exitMenu = true; // Set flag to exit menu loop.
			break;
		default:
			cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
			break;
		}
		// Clear input buffer of additional chars.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

/*
* Prints the main menu options to the console.
*/
void printMenu() {
	cout << "\nMain Menu:" << endl;
	cout << "1. Search for Frequency of Item" << endl;
	cout << "2. Display Item List" << endl;
	cout << "3. Display Item Frequency Histogram" << endl;
	cout << "4. Exit" << endl;
	cout << "Enter your choice (1-4): ";
}
