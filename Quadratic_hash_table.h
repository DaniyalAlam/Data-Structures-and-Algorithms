/*****************************************
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

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"


/*
* Quadratic_hash_table
*
* Muhammad Daniyal Alam
* 2015-03-22
*
* The purpose of this class is to implement a hash table data structure that relies
* on Quadratic probing the search for entries and insert them. It provides a fast way to 
* access, store and find objects. 
*
* Member Variables:
*	int count;					Member variable that keeps track of the number of objects in the hash table
*	int power;					Member variable that defines the power of 2 which determines the capacity of the hash table
*	int array_size;				Member variable that stores the capacity of the hash table (size of the array)
*	int mask;					Mask is capacity - 1, this is used in the hash function to do the bit modulo operator
*	int erased_count;			Member variables that hold the count of the erased bins since erased bins cant be included in normal count
*								and are needed for load factor calculations
*	Type *array;				Member variable that holds a pointer to the hash table array
*	bin_state_t *occupied;		Member variable that holds a pointer to the state of the bin. (Enum type, occupied, unnoccupied or erased)
*
*
* Member Functions (Accessors):
*	int size() const;						Returns the current number of elements in the hash table
*	int capacity() const;					Returns the capacity of the hash table (how many can be held in it)
*	double load_factor() const;				Returns the load factor of the hash table using erased and occupied bins
*	bool empty() const;						Checks to see wether the hash table is empty or not. True if it is.
*	bool member(Type const &) const;		Checks to see wether an element exists within the hash table or not. True if it does.
*	Type bin(int) const;					Returns the element that is in the bin passed in as the parameter
*	int hash(Type const &) const;			Calculates the hash value of the given object for use in probing
*
* Member Functions (Mutators):
*	void insert(Type const &);				Inserts an element into the hash table by using quadratic probing and increses count
*	bool erase(Type const &);				Erases an element from the hash table by setting bin state to erased
*	void clear();							Clears the entire hash table by setting each bin state to unoccupied
*
* Class Functions:            
*  Quadratic_hash_table(int = 5);					Constructor of the class (instantiates the array hash table and member variables)
*  ~Quadratic_hash_table();							Destructor of the class (deletes the memory allocated by hach table and enum type states
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
private:
	int count;
	int power;
	int array_size;
	int mask;
	int erased_count;
	Type *array;
	bin_state_t *occupied;

	int hash(Type const &) const;

public:
	Quadratic_hash_table(int = 5);
	~Quadratic_hash_table();
	int size() const;
	int capacity() const;
	double load_factor() const;
	bool empty() const;
	bool member(Type const &) const;
	Type bin(int) const;

	void print() const;

	void insert(Type const &);
	bool erase(Type const &);
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Quadratic_hash_table<T> const &);
};

/*
* Quadratic_hash_table<Type>::Quadratic_hash_table(int m)
*
*
* This is the constructor of the class. It initializes an array of size 2^parameter and sets the
* corresponding member variables. It also creates the bin states
*
*
* Parameters:
*  int m
*   The power of 2 that defines the size of the hash table created
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table(int m) :
count(0), power(m),
array_size(1 << power),
mask(array_size - 1),
array(new Type[array_size]),
occupied(new bin_state_t[array_size]) {

	//initialize all bins to bea ready to use (initial state UNOCCUPIED)
	for (int i = 0; i < array_size; ++i) {
		occupied[i] = UNOCCUPIED;
	}
	erased_count = 0;
}

/*
* Quadratic_hash_table<Type>::~Quadratic_hash_table()
*
* Deallocates the memory allocated by the hash table and bin state arrays
*
*
* Returns:
*  Nothing
*/

template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table(){
	delete[] array;
	delete[] occupied;
}


/*
* int Quadratic_hash_table<Type>::hash(Type const &obj) const
*
* Calculates the hash value of a given object and returns it. The hash value is used to probe through the hash table
* and is used for inserts, finds, and deletes
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The hash value of the parameter
*/

template <typename Type>
int Quadratic_hash_table<Type>::hash(Type const &obj) const{
	//bit modulo operator done with the mask
	return (int)obj & mask;
}

/*
* int Quadratic_hash_table<Type>::size() const
*
* Returns the number of objects in the hash table.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The number of objects in the hash table.
*/

template <typename Type>
int Quadratic_hash_table<Type>::size() const{
	return count;
}

/*
* int Quadratic_hash_table<Type>::capacity() const
*
* Returns the capacity of the hash table. How many elements are able to fit in the data structure
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The capacity of the array
*/

template <typename Type>
int Quadratic_hash_table<Type>::capacity() const{
	return array_size;
}

/*
* double Quadratic_hash_table<Type>::load_factor() const
*
* Calculates and returns the load factor of the hash table which is the ratio of the number of entries and the size of the hash table.
* Also takes into account both the occupied and erased bins by using a meber variable erased bins count.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  The load factor of the hash table
*/

template <typename Type>
double Quadratic_hash_table<Type>::load_factor() const{
	//because load factor is decimal, need to conert the integers to decimal in orger to avoid using integer division
	double double_size = static_cast<double>(size()) + static_cast<double>(erased_count);
	double double_capacity = static_cast<double>(capacity());
	
	return double_size/double_capacity;
}

/*
* bool Quadratic_hash_table<Type>::empty() const
*
* Checks to see wether the hash table is empty or not
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  True if it is empty, false otherwise
*/

template <typename Type>
bool Quadratic_hash_table<Type>::empty() const{
	return count == 0;
}

/*
* bool Quadratic_hash_table<Type>::member(Type const &obj)const
*
* Checks to see wether the parameter object is currently within the hash table or not.
* Does so by using quadratic probing as learned in class so that it actually checks all entries 
* and doesnt repeat entries before going through the entire list.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  True if the parameter exists and false otherwise
*/

template <typename Type>
bool Quadratic_hash_table<Type>::member(Type const &obj)const{
	//calculate the hash value
	int bin = hash(obj);

	//until you have searched the entier hash table, use quadratic probing to start at hashed value bin and 
	//search the hash table checking each time if it is unoccupied or if its occupied, to see if the values are the same.
	for (int i = 0; i < capacity(); ++i){
		bin = (bin + i) % capacity();

		if (occupied[bin] == UNOCCUPIED) //|| occupied[bin] == ERASED)
			return false;

		if (occupied[bin] == OCCUPIED && array[bin] == obj){
			return true;
		}
	}
	//worst case, has to go thru entire list and doesnt find it.
	return false;
}

/*
* Type Quadratic_hash_table<Type>::bin(int n) const
*
* Returns the object in the bin passed in by the parameter
******** Note due to the specifications on the project page, this is undefined for parameters past the range of the hash table
* No pre- or postconditions and no parameters.
*
* Returns:
*  The element in the parameter bin
*/

template <typename Type>
Type Quadratic_hash_table<Type>::bin(int n) const{
	return array[n];
}

template <typename Type>
void Quadratic_hash_table<Type>::print() const{

}

/*
* void Quadratic_hash_table<Type>::insert(Type const &obj)
*
*
* This function implements the hash table's insert functionality. It allows the user to insert objects into the hash table
* and it inserts the object using the quadratic probing method so as to avoind clusters as with linear probing. It returns nothing.
*
* Preconditions:
*  This funtion throws and underflow exception if the hash table is full. We are not worrying about resizing of the hash table
*  in this project.
*
* Postconditions:
*  Are there any conditions or restrictions on the class after
*  this function is executed?
*
* Parameters:
*  Type const &obj
*   This is the object that we are going to insert into the hash table
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
void Quadratic_hash_table<Type>::insert(Type const &obj){
	
	if (size() == capacity())
		throw overflow();

	if (member(obj)){
		return;
	}

	int bin = hash(obj);
	//use of quadratic probing to start at the hash value bin and search for the next available slot to insert the object into.
	for (int i = 0; i < capacity(); ++i){
		bin = (bin + i) % capacity();

		//can only insert if the bin is unoccupied or erased
		if (occupied[bin] == UNOCCUPIED || occupied[bin] == ERASED){
			array[bin] = obj;
			//seperate conditions for occupied and erased to keep track of normal count and erased count for LF calculations
			if (occupied[bin] == UNOCCUPIED)
				++count;

			if (occupied[bin] == ERASED){
				--erased_count;
				++count;
			}
			//after it is inserted, set to occupied to avoid overwriting
			occupied[bin] = OCCUPIED;
			return;
		}

	}

}

/*
* bool Quadratic_hash_table<Type>::erase(Type const &obj)
*
*
* The purpose of this function is to implement the erase functionality of the Hash table. It goes through the table
* using quadratic hashing and sets the bin containing the object to erased
*
* Preconditions:
*  NONE
*
* Postconditions:
*  NONE
*
* Parameters:
*  Type const &obj
*   The object that we are erasing
*
*  
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

template <typename Type>
bool Quadratic_hash_table<Type>::erase(Type const &obj){
	if (!member(obj))
		return false;
	
	int bin = hash(obj);

	//go through the table starting at hash value and when you find the object, set its bin state to ERASED and reset the count and erased
	//count
	for (int i = 0; i < capacity(); ++i){
		bin = (bin + i) % capacity();

		if (array[bin] == obj){
			occupied[bin] = ERASED;
			--count;
			++erased_count;
			return true;
		}
	}
	//worst case, likely wil never happen since if it is not in the table then member(obj) will return false and we will never
	//have to go through the list in the first place.
	return false;
}

/*
* void Quadratic_hash_table<Type>::clear()
*
* goes through the hash table in order M time and clears all the bins by setting their state to UNOCCUPIED
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  NOTHING
*/

template <typename Type>
void Quadratic_hash_table<Type>::clear(){
	for (int i = 0; i < capacity(); ++i){
		occupied[i] = UNOCCUPIED;
		count = 0;
		erased_count = 0;
	}
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Quadratic_hash_table<T> const &hash) {
	for (int i = 0; i < hash.capacity(); ++i) {
		if (hash.occupied[i] == UNOCCUPIED) {
			out << "- ";
		}
		else if (hash.occupied[i] == ERASED) {
			out << "x ";
		}
		else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
