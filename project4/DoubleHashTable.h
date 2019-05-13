#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  j7hua
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

/*
	For the constructor of the DoubleHashTable, there are two different arrays, one is the actual hash
	table, which contains the key and the value; the second one is just having the state of each bins, and 
	they are OCCUPIED,EMPTY and DELETE. For the constructor, we don't care about the initial value for the hash
	table, but we have to initialize all the entries in the array_state to EMPTY.
*/

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}

}

/*
	Deconstructor of the DoubleHashTable, it will delete both arrays been used for the program.
*/
template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// enter your implementation here 
	delete[] array;
	delete[] array_state;
}

/*
	returns the numbers of entries in the hashtable by returning the count variable.
*/

template<typename T >
int DoubleHashTable<T >::size() const {
    // enter your implementation here 
	return count;
}

/*
	returns the maximum entries that can be insert into the hash table, which is the array_size from the start when initializing the size
	of the hashtable array.
*/
template<typename T >
int DoubleHashTable<T >::capacity() const {
    // enter your implementation here 
	return array_size;
}

/*
	returns true if the hash table is empty, or else return false; by checking the value of the variable count.
*/

template<typename T >
bool DoubleHashTable<T >::empty() const {
    // enter your implementation here 
    if(count == 0 ){
    	return true;
    }
    else{
    	return false;
    }
}

/*
	hash function 1, it will make sure the parameter is turned into/was an integer. And then mod it by the array_size, and if the value is negative,
	add array_size to it to be able to get the positive mod value, since c++ has a different mod function as we desired.
*/

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	// enter your implementation here 
	int new_obj = static_cast<int>(obj) % array_size;
	if(new_obj < 0){
		new_obj = new_obj+ array_size;
	}
	return new_obj;
}

/*
	hash function 2, it will make sure the parameter is turned into/was an integer. It will first divide it by the array_size, and then mod it by array_size.
	Then if the value turns out to be negative, it will add it by array_size. And if it's even, add one to make sure the second hash function returns a positive
	odd integer.
*/
template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	// enter your implementation here 
	int value = static_cast<int>(obj)/array_size % array_size;
	if(value < 0){
		value = value + array_size;
	}
	if(value%2 == 0){
		value++;
	}
	return value;
}

/*
	Check if the parameter value is inside the hash table. It will loop through the array with index = h1(obj) + i(number of iteration)*h2(obj),
	and if anytime in the loop, the array_state function at that position is EMPTY, which means no value had ever been stored there, then it will return
	false immediately. Or else it will loop through it by array_size times, and then return false. If the member is found in the array, returns true.
*/

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	// enter your implementation here 
	int index = h1(obj);
	for(int i=0;i<array_size;i++){
		if(index >= array_size){
			index -= array_size;
		}
		if(array_state[index]== EMPTY){
			return false;
		}
		else if (array_state[index] == OCCUPIED && array[index] == obj){
			return true;
		}
		index = index + h2(obj);
	}

	return false;
}

/*
	It will just return the value at the key-index (parameter integer).
*/
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    // enter your implementation here  
	return array[n];
}

/*
	insert the parameter value inside the hash table. It will loop through the array with index = h1(obj) + i(number of iteration)*h2(obj).
	First check if the number of elements in the hash table is same as the array_size, then we just throw an overflow to exit the function.
	Or else,if anytime in the loop, the array_state at the index is EMPTY or DELETED, then it can insert the value at that index, then return out of the function.
*/

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	 // enter your implementation here 	
	int index = h1(obj);
	if (count == array_size){
		throw overflow();
	}
	for(int i=0;i < array_size; i++){

		if(index >= array_size){
			index -=array_size;
		}
		if(array_state[index] == EMPTY || array_state[index] == DELETED){
			array[index] = obj;
			array_state[index] = OCCUPIED;
			count ++;
			return;
		}
		index = index + h2(obj);
	}
}

/*
	Check if the parameter value is inside the hash table. It will loop through the array with index = h1(obj) + i(number of iteration)*h2(obj),
	and if anytime in the loop, the array_state at that index is OCCUPIED and array at that index is the same as the parameter value, it will just update
	the array_state at that index to DELETED then exit the function; since we don't care the value at the index for the hashtable, we always use array_state as the reference of the 
	status of the hastable. And if it loops through every entries of the hastable and doesn't satisfy the condition, that means the value is not in 
	the hash table, and then return false to exit the function.
*/

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 // enter your implementation here
	int index = h1(obj);
	for (int i=0; i< array_size; i++){
		if(index >= array_size){
			index -= array_size;
		}
		if(array_state[index] == OCCUPIED && array[index] == obj){
			array_state[index] = DELETED;
			count --;
			return true;
		}
		index = index + h2(obj);
	}
	return false;
}

/*
	funciton will check reset the array_state, state every index to EMPTY.
*/
template<typename T >
void DoubleHashTable<T >::clear() {
	 // enter your implementation here 	
	for (int i =0; i< array_size; i++){
		array_state[i] = EMPTY;
	}
	count = 0;
}

/*
	Not used for my program.
*/

template<typename T >
void DoubleHashTable<T >::print() const {
      // enter your implementation here 	
	return;
}

#endif
