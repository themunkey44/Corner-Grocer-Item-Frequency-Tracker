#ifndef ITEMLIST_H
#define ITEMLIST_H
#include <iostream>
#include <string>
#include <map>
using namespace std;

class ItemList {
	private:
		map<string, int> items; // Map to store item names and their frequency.
		string nCharString(char c, int n) const; // Helper function to create a string with 'n' repetitions of character 'c'.
		string trimString(const string& str); // Helper function to remove whitespace from a string.
		unsigned int maxNameLength = 0; // Length of the longest item name.
	public:
		void AddItem(const string& itemName); // Adds an item or increments its frequency.
		void RemoveItem(const string& itemName); // Removes an item from the list (if it exists).
		int ItemFrequency(const string& itemName); // Returns the frequency of a specific item.
		unsigned int maxItemNameLength() const; // Returns the length of the longest item name.
		void DisplayItemList() const; // Displays all items in the list.
		void DisplayItemHistogram() const; // Displays a histogram of item frequencies.
		void WriteItemListToFile(const string& filename) const; // Writes the item list to a file.
		void GetItemsFromFile(const string& filename); // Reads items from a file and adds them to the list.
};

#endif // ITEMLIST_H