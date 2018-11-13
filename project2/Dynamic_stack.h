/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  j7hua@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2018
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

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

/*
Constrcutor of the Dynamic_stack, the function will make a dynamic array with the size of the parameter. and if the parameter
parsed in is a negative value, then the constructor will default everything to 1. Count variable is to trace the stack.
*/

Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
array_size( n ),
initial_size(n)
{
	if(n>=1){
		array = new int[array_size];
	}
	else{
		array_size = 1;
		initial_size = 1;
		array = new int[1];
	}

}

/*
Destructor of the Dynamic_stack, it deletes all the memories given to the dynamic array, and set the array_size back to 0.
*/
Dynamic_stack::~Dynamic_stack() {
	delete[] array;
	array_size = 0;
}

/*
top function will return the value of the element on top of the stack, and it throws an underflow error if the stack is empty.
*/

int Dynamic_stack::top() const {
	if(count==0){
		throw underflow();
	}
	else{
		return array[count-1];
	}
}

/*
size function will return the number of elements in the stack, which is stored in the count variable.
*/

int Dynamic_stack::size() const {
	return count;
}

/*
empty function will return true if the stack is empty, and will return false vice versa.
*/

bool Dynamic_stack::empty() const {
	if(count ==0){
		return true;
	}
	else{
		return false;
	}

}

/*
capacitor function will return the size of the dynamic stack memory
*/

int Dynamic_stack::capacity() const {
	return array_size;
}

/*
push mutator will first check if the number of elements in the stack, if the number of elements reach to the limit of the
dynamic array, then the program will create a new dynamic array double the size of the original. And then it will copy all the 
elements into the new array(also delete the old array). Then it will push another element which the value is equal to the parameter onto the stack.
Another case would be if the number of elements in the stack didn't reach the limit of the stack, then it will just add an 
element onto the stack contains the value of the parameter.
*/

void Dynamic_stack::push( int const &obj ) {
	if(count == array_size){
		array_size = array_size*2;
		int *new_array = new int[array_size];
		for (int i=0; i<count; i++){
			new_array[i] = array[i];
		}
		delete[] array;
		array = new_array;
		count ++;
		array[count-1] = obj;
	}
	else{
		array[count] = obj;
		count++;
	}
}

/*
pop mutator will first check if the stack is empty, if it is, then it will throw an underflow error. If the stack is not empty, then
it will return the value and also delete the element from the stack.
*/

int Dynamic_stack::pop() {
	if(count == 0){
		throw underflow();
	}
	else{
		int temp = array[count-1];
		array[count-1] =0;
		count--;
		return temp;
	}
}

/*
clear mutator will delete the dynamic array, and then make a new dynamic array of the initial size.
*/

void Dynamic_stack::clear() {
	delete[] array;
	array = new int [initial_size];
	array_size = initial_size;
	count = 0;
}
#endif
