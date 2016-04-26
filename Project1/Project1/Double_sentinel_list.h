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

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"


/*
* Double_sentinel_list
*
* Muhammad Daniyal Alam
* 2015-02-03
*
* The purpose of this class is to define a doubly linked list data structure.
* It provides the necessary instantiation and clean up, as well as member variables and functions
* related to the double linked list. Along with a constructor, there is a copy constructor which creates
* another double linked list that is identical to the one passed in.
*
* Member Variables:
*  double_node<Type> list_head        the head node of the list (originally pointing to null
*  double_node<Type> list_tail		  the tail node of the list (originally pointing to null
*  int list_size					  the size of the list (originally set to 0)
*
* Class Variables:            // static variables        <- comments about comments :-)
*  type variable        What this variable does.
*                       Any restrictions on its value.
*
* Class Constants:            // static const variables
*  type variable        What this constant does.
*
* Member Functions (Accessors):
int size() const;			returns the size of the list
bool empty() const;			returns wether the list is empty or not (true when empty)

Type front() const;			returns the element of the front node
Type back() const;			returns the element of the last node

Double_node<Type> *head() const;	returns the head node
Double_node<Type> *tail() const;	returns the tail node

int count(Type const &) const;.		returns the number of nodes that contain the passed parameter
*
* Member Functions (Mutators):
*  void swap(Double_sentinel_list &);									swaps the size, head, and tail of the passed list with this list
	Double_sentinel_list &operator=(Double_sentinel_list const &);		

	void push_front(Type const &);										insert a node at the front of the list
	void push_back(Type const &);										insert a node at the back of the list

	Type pop_front();													remove the front node of the list
	Type pop_back();													remove the back node of the list

	int erase(Type const &);											delete all nodes that contain the passed parameter
*
* Class Functions:            // static functions
*  type function_name( type param_1, ... )
*  One- or two-line summary of what this function does.
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
class Double_sentinel_list {
private:
	Double_node<Type> *list_head;
	Double_node<Type> *list_tail;
	int list_size;

public:
	Double_sentinel_list();
	Double_sentinel_list(Double_sentinel_list const &);
	~Double_sentinel_list();

	// Accessors

	int size() const;
	bool empty() const;

	Type front() const;
	Type back() const;

	Double_node<Type> *head() const;
	Double_node<Type> *tail() const;

	int count(Type const &) const;

	// Mutators

	void swap(Double_sentinel_list &);
	Double_sentinel_list &operator=(Double_sentinel_list const &);

	void push_front(Type const &);
	void push_back(Type const &);

	Type pop_front();
	Type pop_back();

	int erase(Type const &);

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Double_sentinel_list<T> const &);
};

//the contructor instantiates a doubly linked list by setting the head and tail pointers to point to the sentinel nodes which are new nodes
//that will be referred to as head and tail. They are instantiatied with an element of 0 and nullptr for previous and next nodes. The initial
//size is obviously set to 0 as well

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list() :
list_head(new Double_node<Type>(0, nullptr, nullptr)),
list_tail(new Double_node<Type>(0, nullptr, nullptr)),
list_size(0){
 
	//make the next pointer of head point to tail and vice versa
	list_tail->previous_node = head();
	list_head->next_node = tail();
	
}

//first part is the same as the costructor, we create a new instance of a doubly linked list and make the head and tail nodes to point
//to each other. Then we fill in the values copying them from the list that is given.
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> const &list) :
list_head(new Double_node<Type>(0, nullptr, nullptr)),
list_tail(new Double_node<Type>(0, nullptr, nullptr)),
list_size(0) {
	

	//create the new (copy) linked list
	list_tail->previous_node = head();
	list_head->next_node = tail();
	
	//create a temporary pointer pointing to the original list's first actual node
	Double_node<Type> *temp = list.head()->next();

	//populate the list with the values from original list. store in a variable and push back using the element. then incerement the temp pointer
	while (temp->next() != nullptr){
		//create a variable to store the retrieved element from original to aviod changing both list's values
		Type element = temp->retrieve();
		push_back(element);
		temp = temp->next();
	}

}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	
	//while in the loop, keep checking is the list is empty or not.
	while (!empty()){
		//if it is, pop the first node
		pop_front();
	}
	//once it is empty, we wil still have head and sentinel nodes so we need to delete them seperately.
	delete list_head;
	delete list_tail;

}

/*
* int Double_sentinel_list<Type>::size() const
*
* Returns the size of the linked list
*
* If it is empty, return size = 0
*
* Returns:
*  the size of the linked list
*/
template <typename Type>
int Double_sentinel_list<Type>::size() const {
	int size = 0;
	//if empty return 0
	if (empty()){
		return size;
	}
	//use i as a pointer that starts at the first actual node and iterate through incrementing by one each time
	for (Double_node<Type> *i = head()->next(); i->next() != nullptr; i = i->next()){
		size = size + 1;
	}
	return size;
}

/*
* bool Double_sentinel_list<Type>::empty() const
*
* Checks to see if the list is empty
*
* 
*
* Returns:
*  A boolean value. True is size is 0, and False if size != 0
*/

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	return (list_size == 0);
}

/*
* Type Double_sentinel_list<Type>::front() const
*
* Gives the element in the first node of the list
*
*If the list is empty, throw and underflow
*
* Returns:
*  the element in the first node
*/

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	if (empty()){
		throw underflow();
	}
	return head()->next()->retrieve();
}

/*
* Type Double_sentinel_list<Type>::back() const
*
* Gives the element in the last node of the list
*
* If it is empty, throw underflow
*
* Returns:
*  the element in the last node
*/
template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	if (empty()){
		throw underflow();
	}
	return tail()->previous()->retrieve();
}

/*
* Double_node<Type> *Double_sentinel_list<Type>::head() const
*
* Returns a pointer to the head of the list
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Returns a pointer to the head of the list
*/

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {

	return list_head;
}

/*
* Double_node<Type> *Double_sentinel_list<Type>::head() const
*
* Returns a pointer to the tail of the list
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Returns a pointer to the tail of the list
*/

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {

	return list_tail;
}

/*
* int Double_sentinel_list<Type>::count(Type const &obj) const 
*
* Counts the number of nodes in the list that have the same element as obj
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  the number of nodes that satisfy the above condition
*/

template <typename Type>
int Double_sentinel_list<Type>::count(Type const &obj) const {
	int count = 0;
	//use a temp pointer that starts head and checks every node to see if it is equal to the referenced obj. Then increments count by one
	for (Double_node<Type> *temp = list_head; temp != nullptr; temp = temp->next()){
		if (temp->retrieve() == obj){
			count = count + 1;
		}
	}
	return count;
}

/*
* void Double_sentinel_list<Type>::swap(Double_sentinel_list<Type> &list)
*
* swaps this list with the given list by resetting its size, head and null ptrs
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  nothing
*/

template <typename Type>
void Double_sentinel_list<Type>::swap(Double_sentinel_list<Type> &list) {
	std::swap(list_head, list.list_head);
	std::swap(list_tail, list.list_tail);
	std::swap(list_size, list.list_size);
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type> const &rhs) {
	Double_sentinel_list<Type> copy(rhs);

	swap(copy);

	return *this;
}

/*
* void Double_sentinel_list<Type>::push_front(Type const &obj)
*
* Inserts a node with the given element into the front of the list
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  nothing
*/

template <typename Type>
void Double_sentinel_list<Type>::push_front(Type const &obj) {

	//create a node with the passed obj as the element and adjust pointers to point to previous head and next head->next()
	Double_node<Type> *temp = new Double_node<Type>(obj, head(), head()->next());
	//adjusts the first node and head to point to the new node (its previous and next pointers)
	head()->next()->previous_node = temp;
	head()->next_node = temp;
	list_size++;

}

/*
* void Double_sentinel_list<Type>::push_back(Type const &obj)
*
* Inserts a node with the given element into the back of the list
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  nothing
*/

template <typename Type>
void Double_sentinel_list<Type>::push_back(Type const &obj) {
	//same as push_front() but this time, adds the new node to the back of the list, adjusting the tail and last node accordingly
	Double_node<Type> *temp = new Double_node<Type>(obj, tail()->previous(), tail());
	tail()->previous()->next_node = temp;
	tail()->previous_node = temp;
	list_size++;
}

/*
* Type Double_sentinel_list<Type>::pop_front()
*
* Deletes the front node of the list
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The element of the node that was deleted
*/

template <typename Type>
Type Double_sentinel_list<Type>::pop_front() {
	if (empty()){
		throw underflow();
	}
	//variable to store the value of the front node to be returned
	Type element = front();
	//create a temp pointer pointing to the node being delete. First the next and previous pointers of head and first node are adjusted and then
	//the node(temp) is deleted
	Double_node<Type> *temp = head()->next();
	head()->next_node = temp->next();
	temp->next()->previous_node = head();
	delete temp;
	list_size--;
	
	return element;
}


/*
* Type Double_sentinel_list<Type>::pop_back()
*
* Deletes the last node of the list
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  element of the node that was deleted
*/

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {
	if (empty()){
		throw underflow();
	}
	//same as pop_back() but now removing from the back of the list. the previous and next pointers of last node and tail are now adjusted
	//and the last node(temp) is deleted
	Type element = back();
	Double_node<Type> *temp = tail()->previous();
	tail()->previous_node = temp->previous();
	temp->previous()->next_node = tail();
	delete temp;
	list_size--;
	return element;
}


/*
* int Double_sentinel_list<Type>::erase(Type const &obj)
*
* 
*
* This function takes in a parameter which is an address to a value stored in memory. It then checks
* the entire list to see if there is a node that contains that same value. If it does, then it deletes that node
* and increments the count by 1. It returns the amount of nodes that were deleted.
*
* Preconditions:
* 
*
* Postconditions:
*  
*
* Parameters:
*  type const &obj
*   The address to the value that is to be deleted
*
*  
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/
template <typename Type>
int Double_sentinel_list<Type>::erase(Type const &obj) {
	
	int count = 0;
	//use a iterator pointer that starts off at first actual node and iterates through the list checking to see if the node's element is equal to
	//the obj
	Double_node<Type> *iterator = head()->next(); 
	while(iterator != tail()){
		
		//if it finds one, then we make another pointer to the node to be deleted, adjust the previous node's next pointer and next node's previous
		//pointer, and then delete the temp pointer. We then break out of the while loop because we have deleted the first occurrance of the object.
		//
		if (iterator->retrieve() == obj){
			Double_node<Type> *temp = iterator;
			iterator->previous()->next_node = iterator->next();
			iterator->next()->previous_node = iterator->previous();
			delete temp;
			count++;
			list_size--;
			break;
		}
	}
	return count;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<(std::ostream &out, Double_sentinel_list<T> const &list) {
	out << "head";

	for (Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next()) {
		if (ptr == list.head() || ptr == list.tail()) {
			out << "->S";
		}
		else {
			out << "->" << ptr->retrieve();
		}
	}

	out << "->0" << std::endl << "tail";

	for (Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous()) {
		if (ptr == list.head() || ptr == list.tail()) {
			out << "->S";
		}
		else {
			out << "->" << ptr->retrieve();
		}
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
