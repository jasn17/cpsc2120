/*
 * Name: Jason Lin 
 * Date Submitted: 02/18/24
 * Lab Section: 005
 * Assignment Name: Searching and Sorting
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <utility>
#include <ctime>
using namespace std;

template <class T>
std::vector<T> merge(std::vector<T> left, std::vector<T> right) {
	vector<T> newVec;
	unsigned int leftSt = 0, rightSt = 0;

	// Loop compares the <leftSt> index from <left> to <rightSt> index from <right>
	// The lower value is pushed to <newVec> and the index is incremented
	// Loop ends when <leftSt> or <rightSt> iterates out of bounds
	while (leftSt < left.size() && rightSt < right.size()) {
		if (left[leftSt] <= right[rightSt]) {		
			newVec.push_back(left[leftSt++]);
		}
		else { 
			newVec.push_back(right[rightSt++]);
		}
	}

	// Any remaining element in left or right must be the largest of the two vectors
	// Add the remaining element
	
	while(leftSt < left.size()) {
		newVec.push_back(left[leftSt++]);
	}
	while(rightSt < right.size()) {
		newVec.push_back(right[rightSt++]);
	}

	// Return the merged vector
	return newVec;
}


template <class T>
std::vector<T> mergeSort(std::vector<T> lst){
	vector<T> left;
	vector<T> right;
	int max = lst.size();
	int mid = max / 2;
	
	// Base Case //
	if (lst.size() == 1) {
		return lst;
	}			
	else{
		// Clearing vectors before populating
		left.clear();
		right.clear();
		// Populating left half of the vector 
		for (int i = 0; i < mid ; i++) {
			left.push_back(lst[i]);
		}
		// Populating right half of the vector
		for (int i = mid; i < max; i++) {
			right.push_back(lst[i]);
		}
		
		// Recursive Call //
		left = mergeSort(left);
		right  = mergeSort(right);

		return merge(left, right);
	}
}
template <class T>
void quickSort(std::vector<T> & lst, int start, int end); 
template <class T>
int partition(std::vector<T> & lst, int start, int end, T p); 

template <class T>
std::vector<T> quickSort(std::vector<T> lst){
	// Proceed with sort if vector is not empty
	if (!lst.empty()) {
		quickSort(lst, 0, lst.size() - 1);
	}
	// Return sorted vector
	return lst;
	
}

template <class T> 
void quickSort(std::vector<T> & lst, int start, int end) {
	// Base case //
	if(start >= end) { return; }

	// Select middle pivot
	T p = lst[(start + end) / 2];
	//T p = rand() % (end - start + 1) + start; // Could not figure out how to make the random pivot work
	int index = partition(lst, start, end, p);

	// Recursive step //
	quickSort(lst, start, index - 1);
	quickSort(lst, index, end);
}

template <class T>
int partition(std::vector<T> & lst, int start, int end, T p) {
	int left = start, right = end;
	
	// Postitioning all element less than pivot to the left
	// greater than pivot to the right
	while(left <= right) {
		while(lst[left] < p) { left++; }
		while(lst[right] > p) { right--; }
		if (left <= right) {
			std::swap(lst[right], lst[left]);
			left++;
		       	right--;
		}
	}

	return left;
}

