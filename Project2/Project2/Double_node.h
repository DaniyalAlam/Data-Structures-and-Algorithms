/*****************************************
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

#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"

template <typename Type>
class Double_list;

template <typename Type>
class Cyclic_double_list;

template <typename Type>
class Double_sentinel_list;

template <typename Type>
class Cyclic_double_sentinel_list;


/*
* Double_node
*
* Muhammad Daniyal Alam
* 2015-02-03
*
* This class is used to create a node that stores a value, a next pointer, and a previous pointer.
*
* Member Variables:
*   Type       element;				stores the element of the node
	Double_node *previous_node;		pointer to the previous node
	Double_node *next_node;			pointer to the next node
*
* Class Variables:            // static variables        <- comments about comments :-)
*  type variable        What this variable does.
*                       Any restrictions on its value.
*
* Class Constants:            // static const variables
*  type variable        What this constant does.
*
* Member Functions (Accessors):
* 	Type retrieve() const;				returns the element of this node
	Double_node *previous() const;		returns pointer to the previous node
	Double_node *next() const;			returns poiter to the next node
*
* Member Functions (Mutators):
*  type function_name( type param_1, ... )
*  One- or two-line summary of what this function does.
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
class Double_node {
private:
	Type       element;
	Double_node *previous_node;
	Double_node *next_node;

public:
	Double_node(Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr);

	Type retrieve() const;
	Double_node *previous() const;
	Double_node *next() const;

	friend class Double_list<Type>;
	friend class Cyclic_double_list<Type>;
	friend class Double_sentinel_list<Type>;
	friend class Cyclic_double_sentinel_list<Type>;

	// if ptr is a pointer to a Double_node<Type> object
	// in one of the friendly classes, you should:
	//    use   ptr->next_node   to modify it
	//    use   ptr->next()      to access it
};


//The constructor creates an instance of the double_node and instantiates the element, previous, and next node pointers
//that were passed in
template <typename Type>
Double_node<Type>::Double_node(Type const &e, Double_node<Type> *p, Double_node<Type> *n) :
element(e),
previous_node(p),
next_node(n) {
}

/*
* Type Double_node<Type>::retrieve() const
*
* Returns the element of this node
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Elemenet of the node
*/

template <typename Type>
Type Double_node<Type>::retrieve() const {
	// Just return the actual element in the node which was originally set in the constructor
	return element;
}

/*
* Double_node<Type> *Double_node<Type>::previous() const
*
* Returns a pointer to the previous node
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The previous node
*/

template <typename Type>
Double_node<Type> *Double_node<Type>::previous() const {
	// returning a pointer to the previous node
	return previous_node;
}

/*
* Double_node<Type> *Double_node<Type>::next() const
*
* Returns the next node
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The next node
*/

template <typename Type>
Double_node<Type> *Double_node<Type>::next() const {
	// returning a pointer to the next node
	return next_node;
}

#endif
