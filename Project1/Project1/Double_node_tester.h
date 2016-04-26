/*************************************************
* Double_node_tester<Type>
* A class for testing nodes used in doubly linked lists.
*************************************************/

#ifndef DOUBLE_NODE_TESTER_H
#define DOUBLE_NODE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Double_node.h"

#include <iostream>

template <typename Type>
class Double_node_tester :public Tester< Double_node<Type> > {
	using Tester< Double_node<Type> >::object;
	using Tester< Double_node<Type> >::command;

public:
	Double_node_tester(Double_node<Type> *obj = nullptr) :Tester< Double_node<Type> >(obj) {
		// empty
	}

	void process();
};

/****************************************************
* void process()
*
* Process the current command.  For double nodes, these include:
*
*                 Member
*   Flag         Function         Tests if ...
*
*  Accessors
*
*   next          next()          the next pointer can be followed
*   next0         next()          the next pointer is 'nullptr'
*   previous      previous()      the previous pointer can be followed
*   previous0     previous()      the previous pointer is 'nullptr'
*   retrieve n    retrieve()      the stored value is n
****************************************************/

template <typename Type>
void Double_node_tester<Type>::process() {
	if (command == "next") {
		Double_node<Type> *actual_next = Double_node_tester<Type>::object->next();

		if (actual_next != nullptr) {
			object = actual_next;
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << ": Failure in next(): expecting to follow a non-null next pointer" << std::endl;
		}
	}
	else if (command == "next0") {
		if (object->next() == nullptr) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << ": Failure in next(): expecting a null (nullptr) next pointer" << std::endl;
		}
	}
	else if (command == "retrieve") {
		Type expected_value;
		std::cin >> expected_value;

		Type actual_value;
		actual_value = object->retrieve();

		if (expected_value == actual_value) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << ": Failure in retrieve(): expecting '" << expected_value <<
				"' but got '" << actual_value << "'" << std::endl;
		}
	}
	else if (command == "previous") {
		Double_node<Type> *actual_previous = Double_node_tester<Type>::object->previous();

		if (actual_previous != nullptr) {
			object = actual_previous;
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << ": Failure in previous(): expecting to follow a non-null previous pointer" << std::endl;
		}
	}
	else if (command == "previous0") {
		if (object->previous() == nullptr) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << ": Failure in previous(): expecting a null (nullptr) previous pointer" << std::endl;
		}
	}
	else if (command == "retrieve") {
		Type expected_value;
		std::cin >> expected_value;

		Type actual_value;
		actual_value = object->retrieve();

		if (expected_value == actual_value) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << ": Failure in retrieve(): expecting '" << expected_value <<
				"' but got '" << actual_value << "'" << std::endl;
		}
	}
	else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif
