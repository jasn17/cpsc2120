/* Jason Lin 
 * 02/11/2024
 * Queue Implementation Using Circular Array 
 * CPSC 2120
 */  
#include "IntegerArrayQueue.h"

// Return true if the queue is not full prior to enqueuing
// Return false if the queue is full prior ro enqueuing
bool IntegerArrayQueue::enqueue(int value)
{
	// Queue is full
	if ((back + 2) % size == front){
		return false;
	}
		array[(back + 1) % size] = value;
		back = (back + 1) % size;
	 	return true;
}

// Return a non-zero integer
// If empty, return 0
int IntegerArrayQueue::dequeue()
{
	// Queue is empty
	if ((back + 1) % size == front) {
		return 0;
	}
	else {
		int val = array[front];
		front = (front + 1) % size;
		return val;
	}
}
