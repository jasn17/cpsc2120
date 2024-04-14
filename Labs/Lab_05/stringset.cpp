/*
 * Name: Jason Lin 
 * Date Submitted:
 * Lab Section: 005
 * Assignment Name: Spell Checker Using a Hashtable
 */

#include "stringset.h"
	
Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

void Stringset::insert(string word)
{
	// There are no duplicates
	if (!(find(word))) {
		num_elems++;
		int insert_location = hash(word) % size;	
		table[insert_location].push_back(word);
	}
	else {
		cout << "This word already exists." << endl;
	}
}

bool Stringset::find(string word) const
{

}

void Stringset::remove(string word)
{
    //Implement this function
}

void Stringset::doubleSize() 
{
	if (num_elems == size) {
		// double the size of table
	}
}
