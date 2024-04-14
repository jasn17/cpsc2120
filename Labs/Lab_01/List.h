/*
 * Name: Jason Lin 
 * Date Submitted: 01/25/2023
 * Lab Section: 005
 * Assignment Name: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){
	mySize = 0;
	start = nullptr;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
	Node<T> * temp = start;
	while (start != nullptr) {
	       	start = start->next;
		delete temp;
		temp = start;
	}
}

//Return the size of this list
template <class T>
int List<T>::size(){
	return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
	if (mySize == 0) {
		return true;
	}
	else {
		return false;
	}
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){
	if (start != nullptr){	
		Node<T> * newNode = new Node<T>(value);
		// New node points at the prev first node
		newNode->next = start;
		// Set start as the new first node
		start = newNode;
	}
	else {
		Node<T> * newNode = new Node<T>(value);
		start = newNode;
		start->next = nullptr;
	}
	mySize++;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
	Node<T> * newNode = new Node<T>(value);
	if (start == nullptr) {
		start = newNode;
		start->next = nullptr;
	}
	else {
		Node<T> * curr = start;
		while(curr->next != nullptr) {
			curr = curr->next;
		}
		// Now curr is pointing at the last node
		curr->next = newNode;
		newNode->next = nullptr;
	}
	mySize++;
}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
	// Add newNode as the start
	if (j == 0) {
		insertStart(value);
	}
	else {
		Node<T> * newNode = new Node<T>(value);
		Node<T> * curr = start;
		for (int i = 1; i < j; i++) {
			curr = curr->next;
		}
		// Now curr is pointing at the node before the spot to be inserted
		// Link new node with the prev node's next node
		newNode->next = curr->next;
		// Link the node pointing before spot to be inserted to new node
		curr->next = newNode;
	}
	mySize++;
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){
	if (start != nullptr) {
		Node<T> * temp = start;
		start = start->next;
		delete temp;
		mySize--;
	}
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){
	if (start != nullptr) {
		if (start->next == nullptr) {
			removeStart();
		}
		else {
			Node<T> * curr = start;
			while (curr->next->next != nullptr) {
				curr = curr->next;
			}
			// Now curr is pointing at the node before the last node
			Node<T> * temp = curr->next;
			curr->next = nullptr;
			delete temp;
		}
		mySize--;
	}
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){
	if (j == 0) {
		removeStart();
		mySize--;
	}	
	else {
		Node<T> * curr = start;
		for (int i = 1; i < j; i++) {
			curr = curr->next;
		}
		// Now curr is pointing at the node before the node that is to be deleted
		Node<T> * temp = curr->next;
		// Now temp is pointed at the node to be deleted
		curr->next = temp->next;
		// Now curr is pointed to node the deleted node is pointing to
		delete temp;
		mySize--;
	}
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
	if (start != nullptr) {
		return start->value;
	}
	else {
		return T();
	}
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){
	if (start != nullptr) {
		Node<T> * curr = start;
		while (curr->next != nullptr) {
			curr = curr->next;	
		}
		// Now curr is pointing at the last node 
		return curr->value;
	}
	else {
		return T();
	}
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
//Start @ zero
template <class T>
T List<T>::getAt(int j){
	if (start != nullptr) {
		if (j == 1) {
			return start->value;
		}
		else {
			Node<T> * curr = start;
			for(int i = 0; i < j; i++) {
				curr = curr->next;  
			}
			// Now curr is pointing at the node of position j
			return curr->value;
		}
	}	
	else {	
		return T();
	}
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
//Start @ zero
template <class T>
int List<T>::find(T key){
	if (start != nullptr) {
		Node<T> * curr = start;
		int position = 0;
		// Iterate through entire linked list
		while (curr != nullptr) {
			if (curr->value == key) {
				return position;
			}
			// If the key is not found, increment position and point to the next node
			position++;
			curr = curr->next;
		}
		return -1;
	}
	else {
		return -1;
	}
}
