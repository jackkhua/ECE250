
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
 * Calender Term of Submission:  (Winter) 201N
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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

/*
	returns true if the node is pointing to null, else return false
*/
template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

/*
	returns the element (value of the node) stored for the node
*/
template <typename Type>
Type Leftist_node<Type>::retrieve() const{
	return element;
}

/*
	returns the left_tree pointer of the node
*/

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const{
	return left_tree;
}

/*
	returns the right_tree pointer of the node
*/
template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const{
	return right_tree;
}

/*
	Recursive function, base case would be if the node is pointing to null, then return with a value 0
	, and if the value of the node equals to the value parsed in, then it will add 1, then call the left&right nodes.
	It will recursively traverse through the tree
*/

template <typename Type>
int Leftist_node<Type>::count( Type const &obj ) const{
	if(this == nullptr){
		return 0;
	}
	else if(retrieve() == obj){
		return left_tree->count(obj) + right_tree->count(obj) + 1;
	}
	else{
		return left_tree->count(obj) + right_tree->count(obj);
	}
}


/*
	returns -1 if the node is pointing to null, else it will return the value of heap_null_path_length for the node
*/
template <typename Type>
int Leftist_node<Type>::null_path_length() const{
	if(this == nullptr){
		return -1;
	}
	else{
		return heap_null_path_length;
	}
}

/*
	Base case for the recursion function would be if the node thats trying to insert is pointing to null,
	or if the original root node is an empty tree, then the new node would be the root_node. Else if the node trying
	to insert has a larger value than the original node, it will push it to the right of the original node. it will
	update the heap_null_path_length. if the value for the node trying to insert has a smaller value than the original
	node, it will swap the new nodes with the original node and do the push.
*/

template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_node, Leftist_node *&point_node ){
	if(new_node == nullptr){
		return;
	}
	else if(point_node == nullptr){
		point_node = new_node;
		return;
	}
	else if(new_node->retrieve() >= point_node->retrieve()){
		point_node->right()->push(new_node,point_node->right_tree);
		if(point_node->left() == nullptr || point_node->right() == nullptr){
			heap_null_path_length = 0;
		}
		else{
			heap_null_path_length = 1 + std::min(point_node->left_tree->null_path_length(), point_node->right_tree->null_path_length());
		}
		if(point_node->left()->null_path_length() < point_node->right()->null_path_length()){
			std::swap(point_node->left_tree,point_node->right_tree);
		}
	}
	else{
		Leftist_node *copy = point_node;
		point_node = new_node;
		new_node->push(copy, point_node);
	}
}
/*
	if the node you are checking is pointing to null, then it will just return, since it's already cleared,
	or else it will call the clear funciton for the left & right node, after getting all the nodes called clear
	on the stack, then it will delete the node when it pops.
*/
template <typename Type>
void Leftist_node<Type>::clear(){
	if(this == nullptr){
		return;
	}
	else{
		this->left()->clear();
		this->right()->clear();
		delete(this);
	}
}
// You must implement everything

#endif
