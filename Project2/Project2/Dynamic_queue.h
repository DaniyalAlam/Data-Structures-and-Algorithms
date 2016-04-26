/*****************************************
* Instructions
*  - Replace 'uwuserid' with your uWaterloo User ID
*  - Select the current calendar term and enter the year
*  - List students with whom you had discussions and who helped you
*
* uWaterloo User ID:  m32alam@uwaterloo.ca
* Submitted for ECE 250
* Department of Electrical and Computer Engineering
* University of Waterloo
* Calender Term of Submission:  (Winter) 2015
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*
* The following is a list of uWaterloo User IDs of those students
* I had discussions with in preparing this project:
*    -
*
* The following is a list of uWaterloo User IDs of those students
* who helped me with this project (describe their help; e.g., debugging):
*    -
*****************************************/

#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "ece250.h"
#include "Exception.h"

/*
* Dynamic_queue
*
* Daniyal Alam
* 2015-03-01
*
* The purpose of this class is to create and maintain a queue data structure using and dynamic
* array. It has basic functionality of a queue structure, including functions such as enque, dequeue and clear.
*
* Member Variables:
*   int initial_capacity;			stores the initial capacity of the queue. This capacity does not change
*	int array_capacity;				stores the current capacity of queue or the size of the array. This can change if full
*	Type *array;					pointer to the data structure
*	int ihead;						index of the head of the queue, where the pops take place
*	int itail;						index of the tail of the queue, where the pushes take place
*	int entry_count;				stores the number of elements currently in the queue
*
*
* Member Functions (Accessors):
*   Type head() const;
*		returns the element at the head index
*	int size() const;
*		returns the number of elements in the queue
*	bool empty() const;
*		returns true if the queue is empty, false otherwise
*	int capacity() const;
*		returns the current size of the queue
*
* Member Functions (Mutators):
*   void swap(Dynamic_queue &);
*		swaps current queue with the passed in queue
*	Dynamic_queue &operator=(Dynamic_queue);
*	void enqueue(Type const &);
*		Inserts an element into the queue taking into account the first in first out structure and necessary precautions
*	Type dequeue();
*		Removes an element from the queue
*	void clear();
*		Resets the queue, reverting it back to its original size and emptiness
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
class Dynamic_queue {
private:
	//member variables
	int initial_capacity;
	int array_capacity;
	Type *array;
	int ihead;
	int itail;
	int entry_count;
	// other integer member variables, as necessary

public:
	Dynamic_queue(int = 10);
	Dynamic_queue(Dynamic_queue const &);
	~Dynamic_queue();

	//accessors
	Type head() const;
	int size() const;
	bool empty() const;
	int capacity() const;

	//mutators
	void swap(Dynamic_queue &);
	Dynamic_queue &operator=(Dynamic_queue);
	void enqueue(Type const &);
	Type dequeue();
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Dynamic_queue<T> const &);
};

//Class constructor, initializes the member variables. Empty constructor
template <typename Type>
Dynamic_queue<Type>::Dynamic_queue(int n) :
initial_capacity(std::max(n, 1)),
array_capacity(initial_capacity),
array(new Type[initial_capacity]),
ihead(0),
itail(initial_capacity - 1),
entry_count(0) {
	// Empty constructor
}

//creates a copy of the original array by making a new array and copying the values
template <typename Type>
Dynamic_queue<Type>::Dynamic_queue(Dynamic_queue const &queue) :
initial_capacity(queue.initial_capacity),
array_capacity(queue.array_capacity),
array(new Type[array_capacity]),
ihead(queue.ihead),
itail(queue.itail),
entry_count(queue.entry_count) {
	
	//loop through till the array capacity and copy each element into the new copy array.
	for (int i = 0; i < array_capacity; ++i){
		array[i] = queue.array[i];

	}
}

template <typename Type>
Dynamic_queue<Type>::~Dynamic_queue() {
	//delete the memory allocated by this array by calling delete[]
	delete[] array;
}

/*
* int Dynamic_queue<Type>::size() const
*
* Returns the number of objects in the linked list.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The number of objects in the queue.
*/
template <typename Type>
int Dynamic_queue<Type>::size() const {
	
	return entry_count;
}

/*
* int Dynamic_queue<Type>::capacity() const
*
* Returns the current size of the array, not the queue.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The array capacity, the current size
*/
template <typename Type>
int Dynamic_queue<Type>::capacity() const {

	//return the member variable that holds that size of the actual array, not the size of the queue. This is the #elements it can hold
	return array_capacity;
}

/*
* bool Dynamic_queue<Type>::empty() const
*
* Returns true if the queue is empty, false otherwise
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  true if the queue is empty, false otherwise
*/
template <typename Type>
bool Dynamic_queue<Type>::empty() const {
	if (entry_count == 0){
		return true;		//it is empty when there are no entries in the array
	}
	return false;			//not empty otherwise
}

/*
* Type Dynamic_queue<Type>::head() const
*
* Returns the element at the ihead index. Head of the queue
*
* Cannot be called on an empty queue. Throws exception if it is.
*
* Returns:
*  the element at the ihead index. Head of the queue
*/
template <typename Type>
Type Dynamic_queue<Type>::head() const {
	if (empty()){
		throw underflow();			//if the queue is empty, there is no head. So throw an exception.
	}
	return array[ihead];			//if not empty, return the element at the ihead index
}


/*
* void Dynamic_queue<Type>::swap(Dynamic_queue<Type> &queue)
*
* swaps this queue with the queue that is passed in as parameter.
*
* takes in a Dynamic_queue object to swap with.
*
* Returns:
*  nothing
*/
template <typename Type>
void Dynamic_queue<Type>::swap(Dynamic_queue<Type> &queue) {
	std::swap(initial_capacity, queue.initial_capacity);
	std::swap(array_capacity, queue.array_capacity);
	std::swap(array, queue.array);
	std::swap(ihead, queue.ihead);
	std::swap(itail, queue.itail);
	std::swap(entry_count, queue.entry_count);
}

template <typename Type>
Dynamic_queue<Type> &Dynamic_queue<Type>::operator=(Dynamic_queue<Type> rhs) {
	swap(rhs);

	return *this;
}

/*
* void Dynamic_queue<Type>::enqueue(Type const &obj)
*
*
* The Enqueue function inserts an element into the queue data structure. The element is inserted and the tail end of the queue.
* The element is given by parameter one which is the address of the element. There is nothing to return.
* 
*
* Preconditions:
*  NONE
*
* Postconditions:
*  Array needs to be resized if conditions are met
*
* Parameters:
*  type const &obj1
*   restricted to type. This is the element that needs to be pushed onto the queue
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/
template <typename Type>
void Dynamic_queue<Type>::enqueue(Type const &obj) {
	/*if we are inserting into a full array loop through the old array and copy all the elements into the new
	  array which is of size 2*the old array capacity*/
	if (entry_count == array_capacity){
		int prev_array_capacity = array_capacity;
		array_capacity *= 2;
		Type *arraynew = new Type[array_capacity];

		/*Normalization.*/

		//if the head>tail then from start of array to tail, copy over the elements into the new array
		if (ihead > itail){
			for (int i = 0; i <= itail; ++i){
				arraynew[i] = array[i];
			}

			//start from the end of both new and old arrays and start copying the elements to the end of the new array
			int j = array_capacity - 1;
			for (int i = prev_array_capacity - 1; i >= ihead; --i){
				arraynew[j] = array[i];
				--j;
			}
			ihead += prev_array_capacity;
		}

		//if ihead is less than itail, then just copy elements normally into new array
		if (ihead < itail){
			for (int i = 0; i < array_capacity; i++){
				arraynew[i] = array[i];
			}
		}
		delete [] array;
		array = arraynew;

	}
	++itail;
	//if itail=array capacity and the array is not full, then loop back to the beginning of the array and insert it there. CIRCULAR ARRAY
	if (itail == array_capacity){
		itail = 0;
	}
	array[itail] = obj;
	++entry_count;
}


/*
* Type Dynamic_queue<Type>::dequeue()
*
*
* The Dequeue function removes an element from the head of the queue. It has a return type of Type and it returns the element that was
* removed. It also makes sure the integrity of the queue remains the same.
*
* Preconditions:
*  We cannot remove and element from an empty queue. Thus, throw and underflow exception when encountered
*
* Postconditions:
*  Array needs to be resized if the conditions are met.
*
* Parameters:
*  NONE
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/
template <typename Type>
Type Dynamic_queue<Type>::dequeue() {
	if (empty()){
		throw underflow();
	}
	Type element = array[ihead];
	//array[ihead] = nullptr;
	++ihead;

	//if after popping, ihead is equal to array capacity, then set to 0 to keep circular array
	if (ihead == array_capacity){
		ihead = 0;
	}
	--entry_count;

	/*if the currect capacity is not equal to the initial capacity (ie youve made an increased capacity array when pushing) and
	  the number of elements is less than a quarter of the full capcity, then half the capacity of the array*/
	if (entry_count <= array_capacity/4 && array_capacity > initial_capacity){
		int capacity_old = array_capacity;
		array_capacity = array_capacity / 2;
		Type *arraynew = new Type[array_capacity];
		//if ihead is less than itail, then copy over making head 0 and tail equal to tail-head
		if (ihead < itail){
			for (int i = ihead; i <= itail; ++i){
				arraynew[i-ihead] = array[i];
			}
			Type *temp = array;
			array = arraynew;
			delete [] temp;
			itail = itail - ihead;
			ihead = 0;

		}
		//if head > tail then we need to copy over from 0 to tail normally and then backwards from capacity to ihead.
		//Then set ihead to be equal to the ihead - old capacity (larger array)
		if (ihead > itail){
			for (int i = 0; i <= itail; ++i){
				arraynew[i] = array[i];
			}
			int j = array_capacity - 1;
			for (int i = capacity_old - 1; i >= ihead; --i){
				arraynew[j] = array[i];
				--j;
			}
			Type *temp = array;
			array = arraynew;
			delete [] temp;
			ihead -= array_capacity;
		}
	}

	return element;
}

/*
* void Dynamic_queue<Type>::clear()
*
* Purpose of this class is to reset the queue to its original size and clear the elements.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Nothing
*/
template <typename Type>
void Dynamic_queue<Type>::clear() {
	//create a new clean array with initial capacity size and delete the old one after making this the new array
	Type *cleared_array = new Type[initial_capacity];
	Type *temp = array;
	array = cleared_array;
	delete [] temp;

	//reset the member variables on this instance's object
	array_capacity = initial_capacity;
	ihead = 0;
	itail = initial_capacity - 1;
	entry_count = 0;
}

// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator<<(std::ostream &out, Dynamic_queue<Type> const &queue) {
	// I don't know how you are implementing your queue so I cannot print it.
	// If you want, you can print whatever you want here and then call cout
	// in the driver.

	// Remember to redirect to out, e.g.,
	//      out << "Hello!";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
