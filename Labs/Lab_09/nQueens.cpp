/*
 * Name: Jason Lin 
 * Date Submitted: 04/14/2024
 * Lab Section: 005 
 * Assignment Name: Using Resursion to Solve nQueens Problem 
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#define CHECK(n) (n < 1) // Macro function that returns true if input n is less than 1

using namespace std;

int nQueens(int n);
bool solve(vector<vector<int> >  & board, int col, int n, int & permutations);
bool isSafe(vector<vector<int> >  & board, int testRow, int testCol, int n);
void print(vector<vector<int> > & board);

// Function recursively computes the total number of unique nQueens permutations of the nxn vector board and stores it in a integer. 
// Function expects board to be a nxn vector and n to be >=1
// Runtime complexity: O(n!)
// Space complexity: O(n^2)
bool solve(vector<vector<int> > & board, int col, int n, int & permutations) {
    // base case
  if (col == n) { 
    permutations += 1;
    return false; // return false to continue the recursion
  }

  for (int i = 0; i < n; i++) {
    if(isSafe(board, i, col, n)) {
      board[i][col] = 1;

      // Don't return if a valid placement is found
      solve(board, col + 1, n, permutations);

      board[i][col] = 0; // Backtrack
    }
  }
  //print(board);
  return false; // return false if no valid placement is found
}

// Functions checks if the position of the queen at coordinates (testRow, testCol) is safe from queen from previous rows
// Function returns true if the queen is safe and false otherwise
// Runtime complexity: O(n)
// Space complexity: O(1)
bool isSafe(vector<vector<int> > & board, int testRow, int testCol, int n) {
  int i, j; 
  // Checking if the queen at testRow, testCol can be attacked by any row
  for (i = 0; i < testCol; i++) {
    if (board[testRow][i]) { 
      return false;
    }
  }
  // Can be attacked by any columns 
  for (i = 0; i < testRow; i++) {
    if (board[i][testCol]) {
      return false;
    }
  }
  // Can be attacked by any diagonal
  for (i = testRow, j = testCol; i >= 0 && j >= 0; i--, j--) { 
    if (board[i][j]) {
      return false;
    }
  }
  // Can be attacked by any counter diagonal
  for (i = testRow, j = testCol; i < n && j >= 0; i++, j--) {
    if (board[i][j]) {
      return false;
    }
  }
  //cout << "test[" << testRow << "][" << testCol << "] is safe\n";
  return true;
}

// Function takes in n and creates a nxn board and attempt to solve the total number of ways queens can be organized on a nxn board where a queen exists on each row and no queen attacks each other
// Function calls solve() and isSafe() as helper functions
// Runtime complexity: O(n!) 
// Space complexity: O(n^2)
int nQueens(int n) {
  // Input n less than 1 is detected, impossible to make a board
  if (CHECK(n)) {
    return 0;
  }

  // Initialize the board to 0's. 
  vector<vector<int> > board(n, vector<int>(n, 0));
  int permutations = 0;

  solve(board, 0, n, permutations);

  board.clear();
  return permutations;
}
// Functions prints the 2D vector
// For testing purposes 
void print(vector<vector<int> > & board) {
    // *Print board*//
  for (vector<int> i : board) {
    cout << "{";
    for (int j : i) {
      cout << j << ", ";
    }
    cout << "}\n";
  }
}

/*int main()
{
    clock_t start = clock();
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    clock_t end = clock();

   double time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    cout << "Time executed: " << time << " seconds.\n";
    return 0;
}*/
