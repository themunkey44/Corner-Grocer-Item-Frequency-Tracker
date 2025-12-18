#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "ItemList.h"
using namespace std;

/*
* Helper function to create a string with 'n' repetitions of character 'c'.
* param c The character to repeat.
* param n The number of times to repeat the character.
* return A string consisting of 'c' repeated 'n' times.
*/
string ItemList::nCharString(char c, int n) const {
	string charSting = ""; // Initialize an empty string.
	// Append character 'c' to the string 'n' times.
	for (int i = 0; i < n; i++) {
		charSting += c;
	}
	return charSting; // Return the constructed string.
}

/*
* Helper function to remove leading and trailing whitespace from a string.
* param str The input string.
* return The trimmed string without leading and trailing whitespace.
*/
string ItemList::trimString(const string& str) {
	string result;  // String to hold result without leading\trailing whitespace.

	// Find the first non-whitespace character
	size_t first = str.find_first_not_of(" \t\n\r\f\v");

	// If no non-whitespace character is found (string is all whitespace or empty)
	if (std::string::npos == first) {
		return ""; // Return an empty string
	}

	// Find the last non-whitespace character
	size_t last = str.find_last_not_of(" \t\n\r\f\v");

	// Extract the substring from the first non-whitespace to the last non-whitespace
	return str.substr(first, (last - first + 1));
}

/*
* Adds an item or increments its frequency.
* param itemName The name of the item to add.
*/
void ItemList::AddItem(const string& itemName) {
	items[itemName]++; // Increment the frequency of the item in the map.
	if (itemName.length() > maxNameLength) {
		maxNameLength = itemName.length(); // Update the length of the longest item name if necessary.
	}
}

/* 
* Removes an item from the list (if it exists).
* param itemName The name of the item to remove.
*/
void ItemList::RemoveItem(const string& itemName) {
	auto it = items.find(itemName); // Find the item in the map.
	// If the item exists, erase it from the map.
	if (it != items.end()) {
		items.erase(it);
	}
}

/*
* Returns the frequency of a specific item.
* param itemName The name of the item.
* return The frequency of the item.
*/
int ItemList::ItemFrequency(const string& itemName) {
	auto it = items.find(itemName); // Find the item in the map.
	// If the item exists, return its frequency.
	if (it != items.end()) {
		return it->second;
	}
	return 0;
}

/*
* Helper function to get the length of the longest item name.
* return The length of the longest item name.
*/
unsigned int ItemList::maxItemNameLength() const {
	return maxNameLength; // Return the length of the longest item name.
}

/*
* Displays all items in the list.
*/
void ItemList::DisplayItemList() const {
	cout << "Item List:" << endl;
	// Iterate through the map and display each item and its frequency.
	// NOTE: this is not aligned like the histogram as it looks better this way for a simple list.
	for (const auto& pair : items) {
		cout << pair.first << ": " << pair.second << endl; // Print item name and frequency.
	}
}

/*
* Displays a histogram of item frequencies.
* The histogram is represented using '*' characters.
*/
void ItemList::DisplayItemHistogram() const {
	cout << "Item Frequency Histogram:" << endl;
	// Iterate through the map and display each item with a histogram representation.
	// The histogram is created using '*' characters based on the frequency of each item.
	for (const auto& pair : items) {
		// Calculate spacing for alignment. This is needed to align the histogram properly.
		unsigned int spaceing = maxItemNameLength() - pair.first.length();

		cout << nCharString(' ', spaceing); // Print leading spaces for alignment.
		cout << pair.first << " | " << nCharString('*', pair.second) << endl; // Print item name and histogram.
	}
}

/*
* Writes the item list to a file.
* param filename The name of the file to write to.
*/
void ItemList::WriteItemListToFile(const string& filename) const {
	ofstream outFS;
	// Open the output file.
	outFS.open(filename);
	// Check if the file is open.
	if (outFS.is_open()) {
		// Write each item and its frequency to the file.
		for (const auto& pair : items) {
			// This condition could have been put in the while loop, but using a break statment is clearer and prevents writing incorrect data.
			if(!outFS.good()) {
				outFS.close(); // Close the file.
				// Throw exception if file writing fails. Handle in calling function.
				throw runtime_error("Error writing data to " + filename + ".");
			}
			outFS << pair.first << ": " << pair.second << endl;
		}
		outFS.close(); // Close the file.
	} 
	else {
		// Throw exception if file cannot be opened. Handle in calling function.
		throw runtime_error("Error: Could not open file " + filename + " for writing.");
	}
}

/*
* Reads items from a file and adds them to the list.
* param filename The name of the file to read from.
*/
void ItemList::GetItemsFromFile(const string& filename) {
	ifstream inFS;
	// Open the input file.
	inFS.open(filename);

	// Check if the file is open.
	if (inFS.is_open()) {
		string itemName;
		// Read each line from the file and add the item to the list.
		while (getline(inFS, itemName) || !inFS.eof()) {
			// This condition could have been put in the while loop, but using a break statment is clearer and prevents writing incorrect data.
			if (inFS.fail()) {
				inFS.close(); // Close the file.
				// Throw exception if file reading fails. Handle in calling function.
				throw runtime_error("Error writing data to " + filename + ".");
			}

			itemName = trimString(itemName); // Trim whitespace from the item name.

			if (itemName.empty()) {
				continue; // Skip empty lines.
			}
			AddItem(itemName); // Add item to the list.
		}
		inFS.close(); // Close the file.
	} 
	else {
		// Throw exception if file cannot be opened. Handle in calling function.
		throw runtime_error("Error: Could not open file " + filename + " for reading.");
	}
}
