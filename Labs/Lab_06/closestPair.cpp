/*
 * Name: Jason Lin 
 * Date Submitted: 03/11/2024
 * Lab Section: 005
 * Assignment Name: Find Closest Pair of Points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct point
{
    double x;
    double y;
};
double closestPair(string filename);
int findSize(double xMax, double xMin, double yMax, double yMin, int totalPoints);
double findDist(double x1, double y1, double x2, double y2);

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/

// *** Finding B ***
// To find my bxb grid, I have decided to use the formula int b = sqrt(total_area * total_points) + 1
//    Where double total area = width * height
//        Where double width = (maximum x coordinate) - (minimum x coordinate)
//        Where double height = (maximum y coordinate) - (minimum y coordinate)
//    Where total_points is the total number of points from the file
// Justification:
//    We want approximently an proportional number of Points in each cell based on the total number of Points. 
//    By calculating the width and height based on the maximum and minimum value from the file, we find that we can scale that proprotionally by mutiplying its area with the total number of points. 
//    The addition of one makes the table size b to even number (this is based off preference). 
//    My inspiration for my formula was gathered here: https://devforum.roblox.com/t/how-to-use-spatial-hashing/2094402

double closestPair(string filename) {
  // Open the in-file stream and validate 
  ifstream stream(filename);
  if (!stream.is_open()) {
    cout << endl << "(!)Unable to open file " << filename << ".(!)" << endl;
  }
  // Get the number of lines in the file 
  unsigned int total_points = 0;
  stream >> total_points;

  // Gets the max/min of x/y
  double xMax, yMax, xMin, yMin, x, y;
  stream >> x >> y;
  xMax = xMin = x;
  yMax = yMin = y;
  for(unsigned int i = 0; i < total_points; i++) {
    stream >> x >> y;
    if (x > xMax) {
      xMax = x;
    }
    if (y > yMax) {
      yMax = y;
    }
    if (x < xMin) {
      xMin = x;
    }
    if (y < yMin) {
      yMin = y;
    }
  }

  // Resets stream to the beginning of the file
  stream.clear();
  stream.seekg(0, std::ios::beg);
 
//___________________________________________________________________________________//
  // Find and initialize the dimension of the table
  int b = findSize(xMax, xMin, yMax, yMin, total_points); // b should be sqrt(total_points)?
  vector<vector<vector<point> > > table(b, vector<vector<point> >(b));

  stream >> total_points;
  
  // Populate table by reading in the x and y values, finding their hash index, and populating the cell 
  for (unsigned int i = 0; i < total_points; i++) {
    // Reading in x and y, and initlizing the structure
    stream >> x >> y;
    point newPoint = {x, y};
    
    // Finding the hash value
    int hashX = x * b;
    int hashY = y * b;

    // Populating the table
    table[hashX][hashY].push_back(newPoint);
  } 

  // Closes file stream
  stream.close();
//___________________________________________________________________________________//
  
  // Sets min to the maximum finite double value so there is something to compare values with to find minimum distance
  double min = numeric_limits<double>::max(); // Maybe change this to a finite larger number, idk

  for (unsigned int i = 0; i < table.size(); i++) {
    for (unsigned int j = 0; j < table[i].size(); j++) {

      for (unsigned int k = 0; k < table[i][j].size(); k++) { 
        const point & currPoint = table[i][j][k];  
        // Compare with other points in home cell 
        for (unsigned int m = k + 1; m < table[i][j].size(); m++) { // <*> //
          // Ensures that the currPoint is not compared with the iterating point
          if ((currPoint.x == table[i][j][m].x) && (currPoint.y == table[i][j][m].y)) { 
            // do nothing  
          }
          else {
            double dist = findDist(currPoint.x, currPoint.y, table[i][j][m].x, table[i][j][m].y);
            if (dist < min) { min = dist; }
          }
        }
      
      
        // Compare with surrounding cells 
        for (unsigned int l = i - 1; l <= i + 1; l++) {
          if (l < 0 || l >= table.size()) { 
            //do nothing 
          }
          else {
            for (unsigned int m = j - 1; m <= j + 1; m++) {
              if (m < 0 || m >= table.size()) {
                // do nothing
              }
              else {
                for(unsigned int n = 0; n < table[l][m].size(); n++) { // <*> //
                  if ((currPoint.x == table[l][m][n].x) && (currPoint.y == table[l][m][n].y)) { 
                    // do nothing 
                  }
                  else {
                    double dist = findDist(currPoint.x, currPoint.y, table[l][m][n].x, table[l][m][n].y);
                    if (dist < min) { min = dist; }
                  }
                }
              }
            }
          }
        }        
      }

    }
  }
  return min;
}

// Function finds the returns the bxb dimension of the grid 
int findSize(double xMax, double xMin, double yMax, double yMin, int points) {
  double width = xMax - xMin;
  double height = yMax - yMin;
  double area = width * height;
 
  return sqrt(area * points) + 1;
}

// Function uses the distance formula to find the distance between two points
double findDist(double x1, double y1, double x2, double y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
