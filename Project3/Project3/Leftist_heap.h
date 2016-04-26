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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include <queue>

/*
* Leftist_heap
*
* Muhammad Daniyal Alam
* 2015-03-10
*
* The purpose of this class is to define a Leftist heap datastructure. It implements functions such as push and pop
* to alter the structure of the heap. This will be a min heap. It also uses Leftist_node class to define the nodes
* that are withing the min heap.
*
* Member Variables:
*  Leftist_node<Type> *root_node;
	This is a pointer to this heap's root node. Used for doing operations such as pushing and popping as well as defining
	the start of this heap.

   int heap_size;
    This is a member variable that stores the current size of the heap. This is useful in determining the size of the heap.
*
* Class Variables:            // static variables        <- comments about comments :-)
*  type variable        What this variable does.
*                       Any restrictions on its value.
*
* Class Constants:            // static const variables
*  type variable        What this constant does.
*
* Member Functions (Accessors):
*  bool empty() const;
*	This function returns true or false depending on wether this heap is empty or not.
*
*  int size() const;
*	This function simply returns the member variable heap_size which is the size of the heap (number of elements in the heap)
*
*  int null_path_length() const;
*	This function returns the null path length of the heap. Essentially calling the npl function in Leftist_node on the root node
*
*  Type top() const;
*	Returns the element of the root node of this heap. Essentially the minimum element in the heap.
*
*  int count(Type const &) const;
*	Calls the count fucntion of the root node, it returns the number of nodes in this heap that have the same element as that
*	passed in by the parameter obj
*
* Member Functions (Mutators):
*  void push(Type const &);
*	This function creates a new node using the first parameter and pushes that node onto this heap
*
*  Type pop();
*	Removes the root node. Removing the minimum element of this heap and making the left subtree root node the new root node
*	Also returns the element of the node that was popped
*
*  void clear();
*	Calls the clear function of the Leftist_node on the root node. Basically deleting the memory allocated by this heap.
*
* Class Functions:            // static functions
*  Leftist_heap<Type>::Leftist_heap()
*	Initializes a new Leftist heap data structure. Initially setting size to 0 and root node to nullptr
*
*  Leftist_heap<Type>::Leftist_heap(Leftist_heap const &heap)
*	Creates a copy of the leftist heap passed in by the parameter. It uses a stack data structure to traverse through the tree using
*	a breadth first traversal. Push root node and while not empty, pop the node, push it onto the new heap and push its left and right
*	subtrees into the stack.
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
class Leftist_heap {
private:
	Leftist_node<Type> *root_node;
	int heap_size;

public:
	Leftist_heap();
	Leftist_heap(Leftist_heap const &);
	~Leftist_heap();

	void swap(Leftist_heap &heap);
	Leftist_heap &operator=(Leftist_heap);

	//Accessors
	bool empty() const;
	int size() const;
	int null_path_length() const;
	Type top() const;
	int count(Type const &) const;

	//Mutators
	void push(Type const &);
	Type pop();
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Leftist_heap<T> const &);
};

// some sample functions are given

/*
* Leftist_heap<Type>::Leftist_heap() :
root_node(nullptr),
heap_size(0)
*
*
* Just a copy constructor for the Leftist_heap class, it instantiates the root node to null ptr and size to 0, effectively 
* creating an instance of a Leftist Heap
*
* Preconditions:
*  None
*
* Postconditions:
*  None
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
Leftist_heap<Type>::Leftist_heap() :
root_node(nullptr),
heap_size(0) {
	// does nothing
}

/*
* Leftist_heap<Type>::Leftist_heap(Leftist_heap const &heap) :
root_node(nullptr),
heap_size(0)
*
*
* This is the copy constructor for the Leftist_heap class. Given the address of a heap as a parameter, it uses a queue from the stl and
* breadth first traversal to push each element onto a new heap created by this constructor. The traversal is done by firstly pushing
* the root node into the queue, then while the queue is not empty, pop the front of the queue, push the element onto this queue, and push
* the left and right subtrees onto the queue.
*
* Preconditions:
*  If the heap we are trying to make a copy of is null, it is not possible so we just return
*
* Postconditions:
*  None
*
* Parameters:
*  Leftist_heap const &heap
*   This is the heap that we need to make a copy of.
*
*  STL used!
* The data structure for a queue was used from the stl, it is defined as of being type Leftist_node *, so it holds
* pointers to the nodes that we are pushing and popping from the queue.
*
* Bugs:           // a couple here, first i was using a queue of type TYPE, quickly realized that was pointless since we need to access
						left and right subtrees of the objects that are being popped from the queue
					Also, I was not checking if the left and right subtrees are null or not, obviously accessing a nullptr would be useless 
					so I added if statements.
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
Leftist_heap<Type>::Leftist_heap(Leftist_heap const &heap) :
root_node(nullptr),
heap_size(0) {
	if (heap.root_node == nullptr){
		return;
	}
	std::queue<Leftist_node<Type> *> trav_queue;
	trav_queue.push(heap.root_node);
	while (!trav_queue.empty()){
		Leftist_node<Type> *tmp = trav_queue.front();
		this->push(tmp->retrieve());
		trav_queue.pop();
		if (tmp->left() != nullptr){
			trav_queue.push(tmp->left());
		}
		if (tmp->right() != nullptr){
			trav_queue.push(tmp->right());
		}
	}
	// Traverses through the argument heap and pushes the entries
	// into this heap--you may use whatever traversal you want
}

/*
* Leftist_heap<Type>::~Leftist_heap()
*
* Destructor for this object. It clears the memory allocated by this heap
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  nothing
*/

template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

/*
* void Leftist_heap<Type>::swap(Leftist_heap<Type> &heap)
*
* Essentially just uses the stl to swap the argument heap with this heap by swapping the pointer to root node and
* reassigning the size
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Nothing
*/

template <typename Type>
void Leftist_heap<Type>::swap(Leftist_heap<Type> &heap) {
	std::swap(root_node, heap.root_node);
	std::swap(heap_size, heap.heap_size);
}

/*
* Leftist_heap<Type> &Leftist_heap<Type>::operator=(Leftist_heap<Type> rhs)
*
* Defines the equal to operator for the Leftist heap
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  A pointer to this heap.
*/

template <typename Type>
Leftist_heap<Type> &Leftist_heap<Type>::operator=(Leftist_heap<Type> rhs) {
	swap(rhs);

	return *this;
}

// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
// 
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

/*
* bool Leftist_heap<Type>::empty() const
*
* Check to see wether this heap is empty or not. True if it is, false otherwise.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  True or false depending on wether the heap is empty or not.
*/

template <typename Type>
bool Leftist_heap<Type>::empty() const{
	if (heap_size == 0){
		return true;
	}
	return false;
}

/*
* int Leftist_heap<Type>::size() const
*
* Returns the number of nodes in the heap. The size of the heap
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Returns the number of nodes in the heap. The size of the heap
*/

template <typename Type>
int Leftist_heap<Type>::size() const{
	return heap_size;
}

/*
* int Leftist_heap<Type>::null_path_length() const
*
* Returns the null path length of the root node, which is esentially the null path length of the heap itself
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Returns the null path length of the root node, which is esentially the null path length of the heap itself
*/

template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
	return root_node->null_path_length();
}

/*
* int Leftist_heap<Type>::count(const Type &obj) const
*
* Returns the number of nodes in this heap that have the same element as the parameter obj.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The number of nodes that contain obj
*/

template <typename Type>
int Leftist_heap<Type>::count(const Type &obj) const{
	return root_node->count(obj);
}

/*
* Type Leftist_heap<Type>::top() const
*
* Returns the element of the root node, which is the top of the Leftist heap
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Element of the root node
*/

template <typename Type>
Type Leftist_heap<Type>::top() const{
	if (empty()){
		throw underflow();
	}
	return root_node->retrieve();
}

/*
* void Leftist_heap<Type>::push(const Type &obj)
*
*
* This function is used to push an element onto this heap. It effectively calls the push function defined in the node class on the
* root node of this heap. Thus, there is no need to resize or change npl, because the node class push function does it for us.
* This function just creates a new node with the element and pushes it onto the root node
*
* Preconditions:
*  NONE
*
* Postconditions:
*  NONE
*
* Parameters:
*  const Type &obj
*   This is the element that will be in the node created by the push function and added onto this heap
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
void Leftist_heap<Type>::push(const Type &obj){
	Leftist_node<Type> *new_node = new Leftist_node<Type>(obj);
	root_node->push(new_node, root_node);
	heap_size++;
}

/*
* Type Leftist_heap<Type>::pop()
*
*
* This function removes the minimum element (the root node) from the heap. After removing, it sets the new root node of this heap
* to be that of the root node of the left subtree. WIth this, the Leftist heap structure is kept in place. It also returns the element
* of the root node that was removed. This is the minimum current element in the heap.
*
* Preconditions:
*  We cant pop from a heap that is empty so throw an underflow when this occurs.
*
* Postconditions:
*  None
*
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
Type Leftist_heap<Type>::pop(){
	if (empty()){
		throw underflow();
	}
	Type min_element = root_node->retrieve();
	Leftist_node<Type> *old_root = root_node;
	root_node = root_node->left();
	root_node->push(old_root->right(), root_node);
	delete old_root;
	//old_root->right()->push(old_root->right(), root_node);
	heap_size--;
	return min_element;
}

/*
* void Leftist_heap<Type>::clear()
*
* This function just resets the entire leftist heap by deallocating the memory taken up by the heap and resetting the member variables
* of this heap. 
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  nothing
*/

template <typename Type>
void Leftist_heap<Type>::clear(){
	while (!empty()){
		root_node->clear();
		root_node = nullptr;
		heap_size = 0;
	}
}



// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<(std::ostream &out, Leftist_heap<T> const &heap) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
