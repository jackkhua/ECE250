/*****************************************
 * Name: Jieke Hua
 * Student ID: 20721671
 * UW User ID:  j7hua
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////



/*
Constructor Double_sentinel_list() creates a list that has two sentinel nodes that point to each other
and the list_head and list_tail will points to those two nodes respectfully
It doesn't require any parameters
*/

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{

	Double_node *head_sentinel = new Double_node(Type(),nullptr);
	Double_node *tail_sentinel = new Double_node(Type(),nullptr);
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	list_head = head_sentinel;
	list_tail = tail_sentinel;


}


/*
Copy onstructor Double_sentinel_list() creates a list initially with two sentinel nodes point by the list_head and list_tail,
and then it will make the copy of all the nodes inside the list that is parsed in.(without the two sentinel nodes) By making an array
until it reaches the end sentinel node. Then it will link the copy nodes into the initial empty list i made earlier.

*/

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	Double_node *head_sentinel = new Double_node(Type(),nullptr,nullptr);
	Double_node *tail_sentinel = new Double_node(Type(),nullptr,nullptr);
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	list_head = head_sentinel;
	Double_node *list_head_trace = list_head;
	list_tail = tail_sentinel;
	Double_node *trace_list = list.list_head;
	Double_node *trace_list_tail = list.list_tail;
	while (trace_list->next_node != nullptr && trace_list->next_node != trace_list_tail){
		trace_list = trace_list->next_node;
		Double_node *temp_node = new Double_node(trace_list->node_value);
		list_head_trace->next_node = temp_node;
		temp_node->previous_node = list_head_trace;
		list_head_trace = list_head_trace->next_node;
		list_size++;
	}
	list_head_trace->next_node = list_tail;
	list_tail->previous_node = list_head_trace;
}


/*
Move constructor  Double_sentinel_list creates two sentinel nodes, and then the list_head and list_tail will be pointing
towards those two sentinel nodes. Then calling the swap funciton it will let all the list_head and list_tail points to
the beginning and the end of the parsed in list.
*/
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	Double_node *head_sentinel = new Double_node(Type(),nullptr,nullptr);
	Double_node *tail_sentinel = new Double_node(Type(),nullptr,nullptr);
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	list_head = head_sentinel;
	list_tail = tail_sentinel;
	swap(list);

}

/*
Deconstructor, it will deletes all the noeds in the list when it is called. It will loop through and deletes all the nodes
until the last sentinel node, and then it will delete the head sentinel node.
*/
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	while (list_head->next_node != nullptr){
		list_head = list_head->next_node;
		delete list_head->previous_node;
	}
	delete list_head;
}
/*
size function, when it's called, it will return the list_size of the current list in the class
*/
template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}
/*
empty function, it will check the list_size variable for the class, and if it's 0 (empty), then it will return true, or else it will
return false
*/
template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	if(list_size == 0){
		return true;
	}
	else{
		return false;
	}
}
/*
front function, this function will return the value for the first non-sentinel node.
It handles error when list_size is equal to 0(there isn't any node besides the sentinel nodes), then it will
throw an underflow error
*/
template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// Enter your implementation here
	if(list_size!=0){
		return list_head->next_node->node_value;
	}
	else{
		throw underflow();
	}
}

/*
back function, this function will return the value for the last non-sentinel node.
It handles error when list_size is equal to 0(there isn't any node besides the sentinel nodes), then it will
throw an underflow error
*/

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// Enter your implementation here
	if(list_size!=0){
		return list_tail->previous_node->node_value;
	}
	else{
		throw 
		underflow();
	}
}

/*
begin function, this function will return the first node that the head sentinel node is pointing too,
the assumption made for this function is that whenever this function is called, at least 
both sentinel nodes are pointing to each other by the pointer list_head and list_tail
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	// Enter your implementation here
	return list_head->next_node;
}

/*
end function, it will return the address of the list_tail, the assumption made was that list_tail
is pointing to the tail sentinel node
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	return list_tail;
}
/*
rbegin function, this function will return the address of the previous node that the tail sentinel node is pointing too,
the assumption made for this function is that whenever this function is called, at least 
both sentinel nodes are pointing to each other by the pointer list_head and list_tail
*/
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	return list_tail->previous_node;
}

/*
rend function, this function will return the address of the head sentinel node,
the assumption made for this function is that the list_head is pointing to the head sentinel node/
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	// Enter your implementation here
	return list_head;
}
/*
find funciton, this function will loop through the list, and it will compare each value of the node with the value from
the parameter. And the function will return the address of the first node that has the same value as the parameter. If none of 
the nodes in the list have the same value as the parameter, the function call the function end() to return the address of the 
tail sentinel node.
The parameter is used for comparing numbers in the list.
*/
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	// Enter your implementation here
	Double_node *list_head_trace = new Double_node();
	list_head_trace = list_head;
	while (list_head_trace->next_node != nullptr){
		if(list_head_trace->node_value==obj){
			return list_head_trace;
		}
		else{
			list_head_trace = list_head_trace->next_node;
		}
	}
	return end();
}

/*
count function, this function will loop through the list, and it will compare each value of the node with the value from the
parameter, then there will be a counter, it increments everytime there is a node's value matching the value of the parameter.
Then the function will return the numbers of matches.
The parameter is used for comparing numbers in the list.
*/
template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// Enter your implementation here
	Double_node *trace_list = list_head;
	int count = 0;
	while (trace_list->next_node != nullptr){
		trace_list = trace_list->next_node;
		if(trace_list->node_value==obj){
			count ++;
		}
	}
	return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}
/*
push_front mutator, this function creates a new double node with the value gave by the parameter, and it will push it
to the first node for the list by linking the next_nodes and previous_nodes of the head sentinel node and the previous next node.
The parameter is parsed in for the value of the new ndoe
The assumption made for this function is that the list_head and list_tail points to the head_sentinel node and tail_sentinel node.
*/
template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	Double_node* new_node = new Double_node(obj,list_head, list_head->next_node);
	Double_node* temp_node = list_head->next_node;
	temp_node->previous_node = new_node;
	list_head->next_node = new_node;
	list_size++;
}

/*
push_back mutator, this function creates a new double node with the value gave by the parameter, and it will push it
to the last node for the list by linking the next_nodes and previous_nodes of the tail sentinel node and the previous previous node.
The parameter is parsed in for the value of the new ndoe
The assumption made for this function is that the list_head and list_tail points to the head_sentinel node and tail_sentinel node.
*/

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	Double_node* new_node = new Double_node(obj, list_tail->previous_node, list_tail);
	Double_node* temp_node = list_tail->previous_node;
	temp_node->next_node = new_node;
	list_tail->previous_node = new_node;
	list_size++;
	// Enter your implementation here
}
/*
pop_front mutator, this function will delete the first node of the list
Handled error when list is empty
*/
template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// Enter your implementation here
	if(list_size==0){
		throw underflow();
	}
	Double_node* temp = list_head->next_node->next_node;
	temp->previous_node = list_head;
	delete list_head->next_node;
	list_head->next_node =temp;

	list_size--;
}
/*
pop_back mutator, this function will delete the last node of the list
Handled error when list is empty
*/
template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	if(list_size==0){
		throw underflow();
	}
	Double_node* temp = list_tail->previous_node->previous_node;
	temp->next_node=list_tail;
	delete list_tail->previous_node;
	list_tail->previous_node=temp;

	list_size--;
}
/*
erase mutator, this function will delete all the nodes with the same value as the parameter. And there will
be a counter for each nodes deleted and will be returned in the end.
The parameter is used for a flag for the value.
Assumption made for this function is that list_head and list_tail are pointing to the sentinel nodes.
*/
template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// Enter your implementation here
	Double_node *trace_list = list_head;
	int count = 0;
	while(trace_list->next_node != nullptr && trace_list->next_node != list_tail){
		trace_list = trace_list->next_node;
		if(trace_list->node_value==obj){
			Double_node *temp_next_node = trace_list->next_node;
			Double_node *temp_previous_node = trace_list ->previous_node;
			delete trace_list;
			temp_next_node->previous_node = temp_previous_node;
			temp_previous_node->next_node = temp_next_node;
			trace_list = temp_next_node;
			list_size--;
			count++;
		}

	}
	return count;
}

/*
Default constructor for the double node, it will create a double node.
If there are parameters passed in, it will assign it to the node's value, previous node and next node respectifully.
Assumption if there aren't any parameters passing in, then node value will just be default value of type, and two null pointers.
*/
template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	node_value = nv;
	previous_node = pn;
	next_node = nn;

}

/*
value function, this function will return the node value for the double node.
*/

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value; // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
