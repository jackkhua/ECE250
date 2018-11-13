
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  j7hua@edu.uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2018
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

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}



template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}



// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?


/*
	returns true if the heap is empty, or else return false, just by checking heap_size
*/
template <typename Type>
bool Leftist_heap<Type>::empty() const{
	if(heap_size == 0){
		return true;
	}
	else{
		return false;
	}
}

/*
	return the size of the heap
*/

template <typename Type>
int Leftist_heap<Type>::size() const{
	if (empty()){
		return 0;
	}
	else{
		return heap_size;
	}
}

/*
	returns -1 if the root node is empty, or else it calls the null_path_length function to return the 
	value for the null_path_length
*/

template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
	if(root_node->empty()){
		return -1;
	}
	else{
		return root_node->null_path_length();
	}
}

/*
	throws an underflow error if the heap is empty, or it will return the value of the root_node
*/

template <typename Type>
Type Leftist_heap<Type>::top() const{
	if(heap_size == 0){
		throw underflow();
	}
	else{
		return root_node->retrieve();
	}
}

/*
	if the heap size is 0, then it will return 0, or it will call the count function in leftist_node.h
	and it will compare each node and add one to see a node with the same value as parsed in
*/
template <typename Type>
int Leftist_heap<Type>::count( Type const &obj) const{
	if(heap_size == 0){
		return 0;
	}
	else{
		return root_node->count(obj);
	}
}
/*
	It will make a new node contains the element value of the obj parsed in, and if the heap is empty
	then it will be the root_node. Else it will push it to the root_node by calling push funciton in the 
	Leftist_node.h
*/

template <typename Type>
void Leftist_heap<Type>::push( Type const &obj ){
	Leftist_node<Type> *new_node = new Leftist_node<Type>(obj);
	if(heap_size == 0){
		heap_size ++;
		root_node = new_node;
		return;
	}
	else{
		heap_size ++;
		root_node->push(new_node, root_node);
		return;
	}
}
/*
	Throws an underflow error if the heap is empty, or it will return the value of the root node, and then
	it will delete the root node, and try to conbine the original left_heap and right_heap by calling push 
	function in Leftist_node.h
*/
template <typename Type>
Type Leftist_heap<Type>::pop(){
	if(heap_size ==0){
		throw underflow();
	}
	else{
		heap_size -= 1;	
		Type return_value = root_node->retrieve();
		Leftist_node<Type> *reference_root_node = root_node;
		Leftist_node<Type> *new_right_node = root_node->right();
		root_node = root_node->left();
		delete reference_root_node;
		root_node->push(new_right_node, root_node);
		return return_value;
	}
}
/*
	calls the clear function in Leftist_node.h, and then set the heap variables to default 
	values for an empty heap
*/
template <typename Type>
void Leftist_heap<Type>::clear(){
	root_node->clear();
	root_node = nullptr;
	heap_size = 0;

}

#endif
