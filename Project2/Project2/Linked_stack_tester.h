/*************************************************
* Linked_stack_tester<Type>
* A class for testing linked stacks.
*
*************************************************/

#ifndef LINKD_STACK_TESTER_H
#define LINKD_STACK_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Linked_stack.h"

#include <iostream>

template <typename Type>
class Linked_stack_tester :public Tester< Linked_stack<Type> > {
	using Tester< Linked_stack<Type> >::object;
	using Tester< Linked_stack<Type> >::command;

public:
	Linked_stack_tester(Linked_stack<Type> *obj = nullptr) :Tester< Linked_stack<Type> >(obj) {
		// empty
	}

	void process();
};

/****************************************************
* void process()
*
* Process the current command.  For linked stacks, these include:
*
*  Accessors
*
*   size n          size            the size equals n
*   list_size n     list_size       the size of the linked list is n
*   empty b         empty           the result is the Boolean value b
*   top n           top             n is the top element in the stack
*   top!            top             the underflow exception is thrown
*
*  Mutators
*
*   push n          push            the element can be pushed onto the top (always succeeds)
*   pop n           pop             the top element can be popped and equals n
*   pop!            pop             the underflow exception is thrown
*
*  Others
*   cout            cout << list    print the list (for testing only)
*   assign          operator =      assign this list to a new list
*   summary                         prints the amount of memory allocated
*                                   minus the memory deallocated
*   details                         prints a detailed description of which
*                                   memory was allocated with details
*   !!                              use the previous command, e.g.  5 push 3
*                                                                   6 !! 7         // same as push 7
*   !n                              use the command used in line n  7 top 7
*                                                                   8 !7 9         // same as push 9
*
****************************************************/

template <typename Type>
void Linked_stack_tester<Type>::process() {
	if (command == "new") {
		object = new Linked_stack<Type>();
		std::cout << "Okay" << std::endl;
	}
	else if (command == "size") {
		// check if the size equals the next integer read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if (actual_size == expected_size) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in size(): expecting the value '" << expected_size << "' but got '" << actual_size << "'" << std::endl;
		}
	}
	else if (command == "list_size") {
		// check if the list size equals the next integer read

		int expected_list_size;

		std::cin >> expected_list_size;

		int actual_list_size = object->list_size();

		if (actual_list_size == expected_list_size) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in list_size(): expecting the value '" << expected_list_size << "' but got '" << actual_list_size << "'" << std::endl;
		}
	}
	else if (command == "empty") {
		// check if the empty status equals the next Boolean read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if (actual_empty == expected_empty) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in empty(): expecting the value '" << expected_empty << "' but got '" << actual_empty << "'" << std::endl;
		}
	}
	else if (command == "top") {
		// checks if the first object in the linked list equals the next object read

		Type expected_top;

		std::cin >> expected_top;

		Type actual_top = object->top();

		if (actual_top == expected_top) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in top(): expecting the value '" << expected_top << "' but got '" << actual_top << "'" << std::endl;
		}
	}
	else if (command == "top!") {
		// top of an empty list - catch an exception

		Type actual_top;

		try {
			actual_top = object->top();
			std::cout << "Failure in top(): expecting to catch an exception but got '" << actual_top << "'" << std::endl;
		}
		catch (underflow) {
			std::cout << "Okay" << std::endl;
		}
		catch (...) {
			std::cout << "Failure in top(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	}
	else if (command == "push") {
		// push the next object read to the top of the linked list

		Type n;

		std::cin >> n;

		object->push(n);
		std::cout << "Okay" << std::endl;
	}
	else if (command == "pop") {
		// pop the first object from the linked list

		Type expected_popped_element;

		std::cin >> expected_popped_element;

		Type actual_popped_element = object->pop();

		if (actual_popped_element == expected_popped_element) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in pop(): expecting the value '" << expected_popped_element << "' but got '" << actual_popped_element << "'" << std::endl;
		}
	}
	else if (command == "pop!") {
		// pop from an empty list - catch an exception

		Type actual_popped_element;

		try {
			actual_popped_element = object->pop();
			std::cout << "Failure in pop(): expecting to catch an exception but got '" << actual_popped_element << "'" << std::endl;
		}
		catch (underflow) {
			std::cout << "Okay" << std::endl;
		}
		catch (...) {
			std::cout << "Failure in pop(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	}
	else if (command == "assign") {
		Linked_stack<Type> *new_object = new Linked_stack<Type>();

		*new_object = *object;

		std::cout << "Okay" << std::endl;

		Linked_stack_tester<Type> tester(new_object);

		tester.run();
	}
	else if (command == "cout") {
		std::cout << *object << std::endl;
	}
	else {
		std::cout << command << "Command not found." << std::endl;
	}
}

#endif

