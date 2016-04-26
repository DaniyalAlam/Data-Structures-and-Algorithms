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

/**********************************************************
* YOU MUST MODIFY THIS FUNCTION IF YOU DID NOT IMPLEMENT
* Single_list.h IN PROJECT 1.  THIS REQUIRES YOU TO:
*   1.  Change which header file is is included.
*   2.  Change the type of the member variable 'list'.
*   3.  Update the ostream<< operator so that it prints
*       out the entries in your implementation.
**********************************************************/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_sentinel_list.h"
#include "Double_node.h"
#include "Exception.h"
#include <iostream>

/*
* Linked_stack
*
* Daniyal Alam
* 2015-03-01
*
* The purpose of this class is to implement a stack data strucure by using a doubly linked list of arrays.
* The doubly linked list from project 1 will be used to implement this.
*
* Member Variables:
*  static int const ARRAY_CAPACITY = 8;				The static array capacity of each array in every node. set to a const 8
*  Double_sentinel_list<Type *> list;				Pointer to this double sentinel list
*  int itop;										The index for the top of the stack
*  int stack_size;									The number of elements currently in the stack
*
*
* Member Functions (Accessors):
*   bool empty() const;					Checks to see if the stack is empty
*	int size() const;					Returns the size of the stack
*	int list_size() const;				Returns the size of the list
*
*	Type top() const;					Returns the element at the top of the stack
*
* Member Functions (Mutators):
*   void swap(Linked_stack &);					swaps this list with the list passed in as a parameter
*	Linked_stack &operator=(Linked_stack);		
*	void push(Type const &obj);					Push an element on top of the stack
*	Type pop();									Pop the top element from the stack
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
class Linked_stack {
private:
	static int const ARRAY_CAPACITY = 8;

	Double_sentinel_list<Type *> list;
	int itop;
	int stack_size;

public:
	Linked_stack();
	Linked_stack(Linked_stack const &);
	~Linked_stack();

	//accessors
	bool empty() const;
	int size() const;
	int list_size() const;

	Type top() const;

	//mutators
	void swap(Linked_stack &);
	Linked_stack &operator=(Linked_stack);
	void push(Type const &obj);
	Type pop();

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Linked_stack<T> const &);
};

//Class constructor. Initializes the size member variable to 0
template <typename Type>
Linked_stack<Type>::Linked_stack() :
stack_size(0) {
	// Empty constructor
}

//Class copy constructor. Creates a new double sentinel list stack and copies the arrays of the original
template <typename Type>
Linked_stack<Type>::Linked_stack(Linked_stack const &stack) :
itop(stack.itop),
stack_size(stack.stack_size) {
	Double_node<Type *> *temp = stack.list.head()->next();

	/*loop through the original, each time creating a new array of size array capacity 
	  and copying values of original array into new array and then pushing it onto the back of the stack*/
	while (temp->next() != nullptr){
		Type *newarray = new Type[ARRAY_CAPACITY];
		for (int i = 0; i < ARRAY_CAPACITY; ++i){
			newarray[i] = temp->retrieve()[i];
		}
		//Type  element = (temp->retrieve());
		list.push_back(newarray);
		temp = temp->next();
	}
}

//Class destructor. while its not empty, pop the front.
template <typename Type>
Linked_stack<Type>::~Linked_stack() {
	while (!empty()){
		pop();
	}

}


/*
* bool Linked_stack<Type>::empty() const
*
* Returns as a boolean wether the stack is empty or not
*
*
* Returns:
*  True if its empty, false otherwise
*/

template <typename Type>
bool Linked_stack<Type>::empty() const {
	return (stack_size == 0);
}

/*
* int Linked_stack<Type>::size() const
*
* Returns the number of objects in the linked stack.
*
*
* Returns:
*  The number of objects in the linked stack.
*/

template <typename Type>
int Linked_stack<Type>::size() const {

	return stack_size;
}

// Do not change this implementation

/*
* int Linked_stack<Type>::list_size() const
*
* Returns the actual size of the list. Not to be confused with the size of the stack.
*
*
* Returns:
*  The size of the list. Uses the size member function provided in the double_sentinel_list
*/

template <typename Type>
int Linked_stack<Type>::list_size() const {
	return list.size();
}

/*
* Type Linked_stack<Type>::top() const
*
* Returns the element at the top of the stack
*
* There is no top of the stack if it is empty, if so, throw and underflow exception
*
* Returns:
*  The element at the top of the stack
*/

template <typename Type>
Type Linked_stack<Type>::top() const {
	if (size() == 0){
		throw underflow();
	}

	return list.head()->next()->retrieve()[itop];
}

/*
* void Linked_stack<Type>::swap(Linked_stack<Type> &stack)
*
* Swaps this stack with the stack passed in by the parameter
*
*
* Returns:
*  Nothing
*/

template <typename Type>
void Linked_stack<Type>::swap(Linked_stack<Type> &stack) {
	std::swap(list, stack.list);
	std::swap(stack_size, stack.stack_size);
	std::swap(itop, stack.itop);
}

/*
* Linked_stack<Type> &Linked_stack<Type>::operator=(Linked_stack<Type> rhs)
*
* Defines the equal to operator
*
*
* Returns:
*  Nothing
*/

template <typename Type>
Linked_stack<Type> &Linked_stack<Type>::operator=(Linked_stack<Type> rhs) {
	swap(rhs);

	return *this;
}

/*
* void Linked_stack<Type>::push(Type const &obj)
*
*
* THe purpose of the push function is to push an element onto the top of the stack. It wont return anything.
*
*
*
* Parameters:
*  Type const &obj
*   Restricted to type Type. This is the address of the element that is to be added on the stack
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
void Linked_stack<Type>::push(Type const &obj) {
	//if its empty, create a new array, set itop to 0 or first element and push array onto the front.
	//then insert the passed parameter to itop index of the stack.
	if (list.empty()){
		Type *array = new Type[ARRAY_CAPACITY];
		list.push_front(array);
		itop = 0;
		list.head()->next()->retrieve()[itop] = obj;
	}
	//if the array is full, make a new one, set itop to 0, push onto the list front and insert the parameter
	else if (itop == 7){
		itop = 0;
		Type *array = new Type[ARRAY_CAPACITY];
		list.push_front(array);
		list.head()->next()->retrieve()[itop] = obj;
	}
	//not full or empty, then increase itop by one and insert the obj there.
	else{
		++itop;
		list.head()->next()->retrieve()[itop] = obj;
	}
	++stack_size;
}

/*
* Type Linked_stack<Type>::pop()
*
*
* The purpose of this function is to remove the element from the top of the stack. It will also return the element that was popped
*
* Preconditions:
*  Cant pop from an empty stack so throw an underflow exception if encountered
*
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
Type Linked_stack<Type>::pop() {
	Type element;
	if (list.empty()){
		throw underflow();
	}
	else

		//if the array is empty, then set element to be returned and itop = 0 and pop front. If not, just make it null
		//and decrement itop by 1.
		if (itop == 0){
			element = list.head()->next()->retrieve()[itop];
			itop = ARRAY_CAPACITY - 1;
			delete [] list.head()->next()->retrieve();
			list.pop_front();
		}
		else{
			element = list.head()->next()->retrieve()[itop];
			list.head()->next()->retrieve()[itop] = nullptr;
			--itop;
		}
		--stack_size;

	return element;
}

// You will be required to modify this function in order to accomodate
// your implementation of a singly linked list in Project 1.

template <typename T>
std::ostream &operator<<(std::ostream &out, Linked_stack<T> const &stack) {
	if (stack.list.size() == 0) {
		out << "->0";
	}
	else if (stack.list.size() == 1) {
		out << "->[ ";

		for (int i = 0; i <= stack.itop; ++i) {
			out << stack.list.front()[i] << " ";
		}

		out << "]->0";
	}
	else {
		out << "->";

		for (Double_node<T *> *ptr = stack.list.head()->next(); ptr->next() != nullptr; ptr = ptr->next()) {
			out << "[ ";

			if (ptr == stack.list.head()->next()) {
				for (int i = 0; i <= stack.itop; ++i) {
					out << ptr->retrieve()[i] << " ";
				}
			}
			else {
				for (int i = 0; i <= Linked_stack<T>::ARRAY_CAPACITY - 1; ++i) {
					out << ptr->retrieve()[i] << " ";
				}
			}

			out << "]->";
		}

		out << "0";
	}

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif

