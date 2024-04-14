/*
 * Name: Jason Lin
 * Date Submitted:
 * Lab Section: 005
 * Assignment Name: Finding Groups Using Recursion
 */

#include "Grouping.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
//If the input parametere r matches with the current GridSquare then it is already part of a group
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

// Contructor reads content from file and store values in 2D vector groups
Grouping::Grouping(string fileName) {
	// Create reading from file stream 
	ifstream input(fileName);
	// Verify that the file can be opened, exit program if necessary 
	if (input.fail()) {
		cout << "Error reading from file!" << endl;
		exit(1);
	}
	
	// Character to hold the value read from file 
	char tempChar = '\0';
	// Loops through the entire input file, 10 rows and 10 columns
	for (unsigned int i = 0; i < 10; i ++) {
		for (unsigned int j = 0; j < 10; j++) {
			// Get the next character from the file and store it in tempChar
			input.get(tempChar);			
			// If tempChar is a newline character, keep getting the next character until a non-newline charcter 
			while (tempChar == '\n'){
				input.get(tempChar);
			}			
			// If the character read in a is a X, index at [i][j] is 1, else is 0
			if (tempChar == 'X') {
				grid [i][j] = 1;
			} 
			else {
				grid[i][j] = 0;
			}
		}
	}

	// We will now try to find the respective groups read from the file and organize the group into 2D vector groups
	for (unsigned int i = 0; i < 10; i++) {
		for (unsigned int j = 0; j < 10; j++) {
			if (grid[i][j] == 1) {
				// emplace_back() > push_back() for objects
				// Clearing the vector since it will be populated frequently
				oneGroup.clear();
				// Call recursive function findGroup to find all cells corresponding to that group
				findGroup(i, j);
				// oneGroup contains all coordinates of a group, we append oneGroup to our 2D vector groups
				// emplace_back(), constructs object directly in vector's memory, preferred over push_back()
				groups.emplace_back(oneGroup);
			}
		
		}
	}
}


void Grouping::findGroup(int row, int col) {
	// BASE CASE //
	// The row and column has gone out of bounds
	if (row < 0 || row > 9 || col < 0 || col > 9) {
		return;
	}
	// The cell is not a 'X' cell
	if (grid[row][col] != 1) {
		return;
	}
	
	// Append the GridSquare to current group
	oneGroup.emplace_back(GridSquare(row, col));

	// Set the current position to zero
	grid[row][col] = 0;

	// RECURSIVE STEP //
	findGroup(row + 1, col);
	findGroup(row - 1, col);
	findGroup(row, col + 1);
	findGroup(row, col - 1);
}

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(unsigned int g = 0; g < groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(unsigned int s = 0; s < groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}
