/*
 * Name: Jason Lin 
 * Date Submitted: 02/18/24
 * Lab Section: 005
 * Assignment Name: Searching and Sorting 
 */

#pragma once

#include <vector>

template <class T>
int linearSearch(std::vector<T> data, T target){
	// Linear search
	for (unsigned int i = 0; i < data.size(); i++) {
		if(data[i] == target) {
			return i;
		} 
	}
	return -1;
}

// Assuming vector data is in ascending order
template <class T>
int binarySearch(std::vector<T> data, T target){
	int low = 0;
	int high = data.size() - 1;
	int mid = (low + high) / 2;

	// Loop continues until the low == high indicating the end of the search 
	while (low <= high) {
		// Return index of target if found
		if (data[mid] == target) {
			return mid;
		}	
		else {
			// Search right side of mid and update low and mid
			if (data[mid] < target) {
				low = mid + 1;
				mid = (low + high) /2;
			}
			// Search left side of mid and update high and mid
			else if (data[mid] > target) {
				high = mid - 1;
				mid = (low + high) /2;
			}	
		}
	}
	return -1;	
}
