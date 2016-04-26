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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

/*
* Leftist_node
*
* Muhammad Daniyal Alam
* 2015-10-3
*
* This class defines the nodes that are used in Leftist_heap. The object is a node
* that contains an element, as well as pointers to it's left and right subtrees, Initially null.
* There is also a heap_null_path_length associated with the node depending on its left and right
* subtrees.
*
* Member Variables:
*  Type element;					Memeber variable to store the element in the node.
   Leftist_node *left_tree;			Member variable that holds a pointer to the left sub tree. Initially null
   Leftist_node *right_tree;		Member variable that holds a pointer to the right sub tree. Initially null
   int heap_null_path_length;		Stores the null path length of the node. It is determined and updated by the push function
*
* Class Variables:            // static variables       
*  type variable        What this variable does.
*                       Any restrictions on its value.
*
* Class Constants:            // static const variables
*  type variable        What this constant does.
*
* Member Functions (Accessors):
*  Type retrieve() const;
*	Returns the element of this node
*	
*  bool empty() const;
*	Returns true if root_node is nullptr (empty), false otherwise
*
*  Leftist_node *left() const;
*	Returns a pointer to the left subtree of this node
*
*	Leftist_node *right() const;
*	Returns a pointer to the right sub tree of this node
*
*	int null_path_length() const;
*	Returns the null path length of this node depending on its left and right subtrees.
*
* Member Functions (Mutators):
*  int count(Type const &) const;
	Returns the number of nodes within this node's subtrees that contain the element obj passed into the function

	void push(Leftist_node *, Leftist_node *&);
	Using recursion, pushes the new_heap (first parameter) onto the right subtree of the heap referenced by the second parameter.

	void clear();
	Recursively calls clear on the left and right subtrees of the node, effectively deleting every node and thus clearing the node and its
	subtrees.
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/


template <typename Type>
class Leftist_node {
private:
	Type element;
	Leftist_node *left_tree;
	Leftist_node *right_tree;
	int heap_null_path_length;

public:
	Leftist_node(Type const &);

	//Accessors
	Type retrieve() const;
	bool empty() const;
	Leftist_node *left() const;
	Leftist_node *right() const;
	int null_path_length() const;

	//Mutators
	int count(Type const &) const;
	void push(Leftist_node *, Leftist_node *&);
	void clear();
};

/*
* Leftist_node<Type>::Leftist_node(Type const &obj) :
element(obj),
left_tree(nullptr),
right_tree(nullptr),
heap_null_path_length(0)
*
*
* This is the constructor for the Leftist_node class. It takes in an element obj of type Type and creates a node
* whose element is obj and initializes the left and right subtrees to be null and the npl to be 0.
*
* Preconditions:
*  obj needs to be of type Type
*
*
* Parameters:
*  Type const &obj
*   This is the object that will be the element of the node that is created.
*
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
Leftist_node<Type>::Leftist_node(Type const &obj) :
element(obj),
left_tree(nullptr),
right_tree(nullptr),
heap_null_path_length(0) {
	// does nothing
}

// You may need this

/*
* bool Leftist_node<Type>::empty() const
*
* Returns true or false depending on wether the node/heap is empty or not.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  True or false if its empty or full respectively
*/

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return (this == nullptr);
}

// You must implement everything

/*
* Type Leftist_node<Type>::retrieve() const
*
* Returns the element of the node
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The element in this node
*/
template <typename Type>
Type Leftist_node<Type>::retrieve() const{
	return element;
}

/*
* Leftist_node<Type> *Leftist_node<Type>::left()
*
* Returns a pointer to the left subtree of this node.
*
* The left subtree cannot be changed outside this class hence the const
*
* Returns:
*  A pointer to the left subtree of this node.
*/
template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const{
	return left_tree;
}

/*
* Leftist_node<Type> *Leftist_node<Type>::right()
*
* Returns a pointer to the right subtree of this node.
*
* The right subtree cannot be changed outside this calss hence the const
*
* Returns:
*  A pointer to the right subtree of this node.
*/
template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const{
	return right_tree;
}

/*
* int Leftist_node<Type>::null_path_length() const
*
* Returns the null path length member variable which stores the null path length of this node and its subtrees
*
* If its empty, then the heap has a null path length of -1
*
* Returns:
*  the null path length member variable which stores the null path length of this node and its subtrees
*/
template <typename Type>
int Leftist_node<Type>::null_path_length() const{
	if (empty()){
		return -1;
	}
	return heap_null_path_length;
}

/*
* int Leftist_node<Type>::count(const Type &obj) const
*
*
* The count function uses the method of recursion to continuously call count on this node's left and right subtrees.
* The purpose of the count function is to count the number of nodes in this heap that have their element equal to that passed
* in by the parameter (obj).
*
* Preconditions:
*  If the heap is empty, it just returns 0 because there are no elements in the heap
*  If the root node contains an element that is greater than that of count, then it just returns 0 because 
*  the heap is a min heap and so all of the sub tree elements will have an element greater than obj.
*
* Postconditions:
*  None
*
* Parameters:
*  const Type &obj
*   This is the object that the function needs to find in the heap.
*
* 
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/
template <typename Type>
int Leftist_node<Type>::count(const Type &obj) const{
	if (empty()){
		return 0;
	}
	if (element > obj){
		return 0;
	}
	else{
		if (element == obj){
			return (1 + (left()->count(obj) + right()->count(obj)));
		}
		else{
			return (left()->count(obj) + right()->count(obj));
		}
	}


}

/*
* void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this)
*
*
* The purpose of this function is to implement the push function. Given a new heap (first parameter) and a pointer to this heap (second par)
* it effectively pushes the new heap onto the heap pointed to by the second parameter. It takes into account the edge cases and before 
* pushing, checks to see wether the root nodes of the two heaps are in order according to the min heap data structure.
* This will also update the heap null path length and swap the subtrees of the resulting heap in order to maintain the LEFTIST HEAP 
* data structure.
*
* Preconditions:
*  If the heap being added is null, then there is nothing to do, thus return
*
* Postconditions:
*  NONE
*
* Parameters:
*  Leftist_node *new_heap
*   This is a pointer to the heap that is to be pushed onto the heap pointed to by the second parameter.
*		It must be of type Leftist_node *
*
*  Leftist_node *&ptr_to_this
*   This is the pointer to the heap that the new heap is being push onto.
*		It must be of type Leftist_node *&
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/


template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this){
	if (new_heap == nullptr){
		return;
	}
	if (ptr_to_this == nullptr){
		ptr_to_this = new_heap;
		return;
	}
	if (ptr_to_this->retrieve() <= new_heap->retrieve()){
		right_tree->push(new_heap, right_tree);
		heap_null_path_length = std::min(1 + left()->null_path_length(), 1 + right()->null_path_length());
		if (left()->null_path_length() < right()->null_path_length()){
			Leftist_node *tmp = right_tree;
			right_tree = left_tree;
			left_tree = tmp;
		}
	}
	else{
		ptr_to_this = new_heap;
		new_heap->push(this, new_heap);
	}
}

/*
* void Leftist_node<Type>::clear()
*
* This function clears the entire heap/(node and subtrees). Checking to see if the left and right subtrees are empty,
* it calls clear on them if not and deletes the memory allocated by the nodes.
*
* If the node/(heap and subtrees) are already empty, then we do nothing and just return 
*
* Returns:
*  Nothing
*/

template <typename Type>
void Leftist_node<Type>::clear(){
	if (empty()){
		return;
	}
	if (left() != nullptr){
		left_tree->clear();
	}
	if (right() != nullptr){
		right_tree->clear();
	}
	delete this;
}
#endif
