/****************************************************
* Executable:  Double_sentinel_list_driver
*
* Create an instance of the Double_sentinel_list_tester<int>
* or Double_sentinel_list_tester<double> classes and call
* the member function run().
*
* The member function run() will interpret the
* input appropriately and exit when the interpreter
* receives either the command 'exit' or an
* end-of-file.
****************************************************/

#include <iostream>
#include <cstring>
#include "Double_sentinel_list_tester.h"

int main(int argc, char *argv[]) {
	if (argc > 2) {
		std::cerr << "Expecting at most one command-line argument" << std::endl;

		return -1;
	}

	std::cout << "Starting Test Run" << std::endl;

	if (argc == 1 || !std::strcmp(argv[1], "int")) {
		if (argc == 1) {
			std::cerr << "Expecting a command-line argument of either 'int' or 'double', but got none; using 'int' by default." << std::endl;
		}

		Double_sentinel_list_tester<int> tester;

		tester.run();
	}
	else if (!std::strcmp(argv[1], "double")) {
		Double_sentinel_list_tester<double> tester;

		tester.run();
	}

	std::cout << "Finishing Test Run" << std::endl;

	return 0;
}
