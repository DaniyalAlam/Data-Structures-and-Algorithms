// Version 3.0

#include "../Quadratic_hash_table.h"
#include "../Exception.h"
#include "gtest/gtest.h"
#include <stdlib.h>
#include <cmath>

#ifndef nullptr
#define nullptr ((void*)0)
#endif

#define MAX(a,b) ((a<b)?b:a)
#define MIN(a,b) ((a<b)?a:b)

namespace {

// The fixture for testing class Double_node.
class QuadraticHashTableTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	QuadraticHashTableTest():
	// Should be something other than the default value
	default_power(4) {
        // You can do set up work for each test here
    }

	virtual ~QuadraticHashTableTest() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp() {
		test_table = new Quadratic_hash_table<int>(default_power);
	}

	virtual void TearDown() {
		delete test_table;
	}

	// Objects declared here can be used by all tests in the test case
	Quadratic_hash_table<int> *test_table;
	int default_power;
};

TEST_F(QuadraticHashTableTest, Constructor) {
	EXPECT_EQ(0, test_table->size());
	EXPECT_EQ(1 << default_power, test_table->capacity());
	EXPECT_EQ(0, test_table->load_factor());
	EXPECT_TRUE(test_table->empty());
}

TEST_F(QuadraticHashTableTest, InsertMethod) {
	EXPECT_TRUE(test_table->empty());
	EXPECT_EQ(0, test_table->size());
	
	int capacity = test_table->capacity();
	EXPECT_EQ(capacity, test_table->capacity()); // should not change
	
	// Going to go up to twice the capacity but skipping inserting every second value
	// Should result in many collisions and in the end the table should be full
	int max_value = capacity * 2;
	
	int inserted = 0;
	for (int i = 0; i < max_value; i += 2) {
		test_table->insert(i);
		inserted++;
		
		// should do nothing and all the assertions below should still pass
		if (i != max_value - 2) {
			ASSERT_NO_THROW(test_table->insert(i));
		}
		
		ASSERT_FALSE(test_table->empty());
		ASSERT_EQ(inserted, test_table->size());
		ASSERT_EQ(capacity, test_table->capacity()); // should not change
		// doubles are hard to test because of precision
		ASSERT_EQ((static_cast<double>(inserted)) / capacity, test_table->load_factor());
		
		// Can be O(i^2) so be careful with how big you let i be
		for (int j = 0; j <= i; j += 2) {
			ASSERT_TRUE(test_table->member(j));
		}
	}
	
	// should be at capacity
	EXPECT_FALSE(test_table->empty());
	EXPECT_EQ(capacity, test_table->size());
	EXPECT_EQ(capacity, test_table->capacity()); // should not change
	EXPECT_EQ(1, test_table->load_factor());
	EXPECT_THROW(test_table->insert(1111), overflow);
	
	// should NOT be able to "insert" something that is already there without error
	// This was clarified with Prof Harder. If it is full, always throw an error
	
	// All assertions should still be the same after the previous call to insert
	EXPECT_FALSE(test_table->empty());
	EXPECT_EQ(capacity, test_table->size());
	EXPECT_EQ(capacity, test_table->capacity()); // should not change
	EXPECT_EQ(1, test_table->load_factor());
	ASSERT_THROW(test_table->insert(0), overflow);
}

TEST_F(QuadraticHashTableTest, EraseMethod) {
	ASSERT_TRUE(test_table->empty());
	ASSERT_FALSE(test_table->erase(111111));
	
	int capacity = test_table->capacity();
	
	int max_value = capacity * 2;
	for (int i = 0; i < max_value; i += 2) {
		// trying not to test insert here
		test_table->insert(i);
	}
	
	// should be at capacity
	ASSERT_EQ(capacity, test_table->size());
	ASSERT_FALSE(test_table->empty());
	ASSERT_FALSE(test_table->erase(111111));
	
	EXPECT_EQ(capacity, test_table->capacity());
	EXPECT_EQ(1, test_table->load_factor());
	
	int items_left = capacity;
	for (int i = 0; i < max_value - 2; i += 2) {
		ASSERT_TRUE(test_table->erase(i));
		items_left--;
		
		// erasing the same item should not work
		ASSERT_FALSE(test_table->erase(i));
		
		ASSERT_FALSE(test_table->empty());
		ASSERT_EQ(items_left, test_table->size());
		ASSERT_EQ(capacity, test_table->capacity()); // should not change
		// doubles are hard to test because of precision
		//ASSERT_EQ((static_cast<double>(items_left)) / capacity, test_table->load_factor());
		ASSERT_EQ(1, test_table->load_factor());
	}
	
	ASSERT_TRUE(test_table->erase(max_value - 2));
	ASSERT_TRUE(test_table->empty());
	ASSERT_EQ(0, test_table->size());
	EXPECT_EQ(1, test_table->load_factor());
	ASSERT_EQ(capacity, test_table->capacity()); // should not change
	
	// Erasing something previously inserted should not work
	ASSERT_FALSE(test_table->erase(0));
}

TEST_F(QuadraticHashTableTest, MemberMethod) {
	ASSERT_FALSE(test_table->member(1));
	
	// This test attempts to insert several items into erased bins and then
	// check for membership
	
	int capacity = test_table->capacity();
	
	// This has to be negative to make sure that the hash function is implemented
	// properly (test should seg fault if not done right)
	int start_value = -capacity / 2;
	// cannot be capacity
	int end_value = capacity * 0.8;
	
	int value;
	for (int i = 0; i < end_value; i++) {
		value = start_value + i * capacity;
		ASSERT_NO_THROW(test_table->insert(value));
		
		for (int j = 0; j <= i; j++) {
			value = start_value + j * capacity;
			ASSERT_TRUE(test_table->member(value));
		}
		
		ASSERT_FALSE(test_table->member(capacity));
	}
	
	// Remove all the values
	for (int i = 0; i < end_value; i++) {
		value = start_value + i * capacity;
		ASSERT_TRUE(test_table->erase(value));
		ASSERT_FALSE(test_table->erase(value));
		
		// Make sure it is no longer a member
		ASSERT_FALSE(test_table->member(value));
		
		// check that the rest of the values still exist even though
		// the current one should be marked ERASED
		// Checking that the erase function correctly skips over ERASED values
		// and continues looking
		for (int j = i + 1; j < end_value; j++) {
			value = start_value + j * capacity;
			ASSERT_TRUE(test_table->member(value));
		}
	}
	
	ASSERT_TRUE(test_table->empty());
	ASSERT_EQ(0, test_table->size());
	//EXPECT_EQ(0, test_table->load_factor());
	ASSERT_EQ(capacity, test_table->capacity()); // should not change
	
	// Add them back again over the now ERASED bins
	// This time lets fill it up to capacity
	for (int i = 0; i < capacity; i++) {
		value = start_value + i * capacity;
		ASSERT_NO_THROW(test_table->insert(value));
		
		for (int j = 0; j <= i; j++) {
			value = start_value + j * capacity;
			ASSERT_TRUE(test_table->member(value));
		}
		
		ASSERT_FALSE(test_table->member(capacity));
	}
	
	EXPECT_FALSE(test_table->empty());
	EXPECT_EQ(capacity, test_table->size());
	EXPECT_EQ(capacity, test_table->capacity()); // should not change
	EXPECT_EQ(1, test_table->load_factor());
	ASSERT_THROW(test_table->insert(0), overflow);
}

// Thank you Chris for creating this test
TEST_F(QuadraticHashTableTest, LoadFactorMethod) {
	// Test should start with an empty table
	ASSERT_TRUE(test_table->empty());
	// There should also be no erased or occupied entries
	ASSERT_EQ(0, test_table->load_factor());
	
	int capacity = test_table->capacity();
	int inserted = 0;

	// Load half the table
	for (int i = 0; i < capacity; i += 2) {
		test_table->insert(i);
		inserted++;
		
		// Checking this every time because it should always be exactly right
		// Testing floating point precision always sucks though, so we might get bad results depending on the numbers divided
		ASSERT_EQ(static_cast<double>(inserted) / capacity, test_table->load_factor());
	}

	// the load factor should be based on only the inserted entries
	ASSERT_FALSE(test_table->empty());
	ASSERT_EQ(capacity / 2, test_table->size());
	ASSERT_EQ(static_cast<double>(inserted) / capacity, test_table->load_factor());
	// It is important to explicitly test our assumptions here in case something
	// goes wrong with the inserted count
	ASSERT_EQ(0.5, test_table->load_factor());

	// Erase 1/4 of the inserted entries
	for (int i = 0; i < capacity / 2; i += 2) {
		test_table->erase(i);
		inserted--;
	}

	// erasing should not have affected the load factor
	ASSERT_FALSE(test_table->empty());
	ASSERT_EQ(inserted, capacity / 4); // make sure our assumptions for this test hold
	ASSERT_EQ(capacity / 4, test_table->size());
	ASSERT_EQ(0.5, test_table->load_factor());

	// Erase the other 1/4 that was there
	for (int i = capacity / 2; i < capacity; i += 2) {
		test_table->erase(i);
		inserted--;
	}

	// check to make sure the list is empty
	// the load factor should still remain unchanged even though
	// the table is empty
	ASSERT_TRUE(test_table->empty());
	ASSERT_EQ(0, test_table->size());
	// Since we've filled and deleted half, the load factor should still be half
	ASSERT_EQ(0.5, test_table->load_factor());
	
	// Fill the list up again to half its capacity after erasing everything
	// The load factor should NOT change at all
	for (int i = 0; i < capacity / 2; i += 2) {
		test_table->insert(i);
		ASSERT_EQ(0.5, test_table->load_factor());
	}
}

TEST_F(QuadraticHashTableTest, ClearMethod) {
	int capacity = test_table->capacity();
	
	for (int i = 0; i < capacity; i++) {
		ASSERT_NO_THROW(test_table->insert(i));
	}
	
	EXPECT_FALSE(test_table->empty());
	EXPECT_EQ(capacity, test_table->size());
	EXPECT_EQ(capacity, test_table->capacity()); // should not change
	EXPECT_EQ(1, test_table->load_factor());
	ASSERT_THROW(test_table->insert(111111), overflow);
	
	test_table->clear();
	
	ASSERT_TRUE(test_table->empty());
	ASSERT_EQ(0, test_table->size());
	EXPECT_EQ(0, test_table->load_factor());
	ASSERT_EQ(capacity, test_table->capacity()); // should not change
	
	// make sure we can still insert since someone may have forgotten to
	// reset the occupied flags array
	for (int i = 0; i < capacity; i++) {
		ASSERT_NO_THROW(test_table->insert(i));
	}
	
	EXPECT_FALSE(test_table->empty());
	EXPECT_EQ(capacity, test_table->size());
	EXPECT_EQ(capacity, test_table->capacity()); // should not change
	EXPECT_EQ(1, test_table->load_factor());
	ASSERT_THROW(test_table->insert(1111111), overflow);
}

}	// namespace
