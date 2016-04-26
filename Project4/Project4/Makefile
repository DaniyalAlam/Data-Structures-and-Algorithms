CXX=g++
CPPFLAGS=-g -Wall -Werror
REMOVE=rm

GTEST_DIR=../gtest-1.7.0
GTEST_DIST_DIR=../gtest-dist
GTEST_MAIN=$(GTEST_DIST_DIR)/gtest_main.a
TESTFLAGS=-isystem $(GTEST_DIR)/include
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Add additional test files here
TESTS=Quadratic_hash_table_tests

main: Quadratic_hash_table_driver.cpp
	$(CXX) $^ $(CPPFLAGS) -o $@

Quadratic_hash_table_tests.o: Quadratic_hash_table.h Tests/Quadratic_hash_table_tests.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(TESTFLAGS) -c Tests/Quadratic_hash_table_tests.cpp

Quadratic_hash_table_tests: Quadratic_hash_table_tests.o $(GTEST_MAIN)
	$(CXX) $(CPPFLAGS) $(TESTFLAGS) -lpthread $^ -o $@
	
test: $(TESTS) main
	./main int < int.in.txt
	./Quadratic_hash_table_tests

clean:
	$(REMOVE) -f *.exe *.o $(TESTS) main
