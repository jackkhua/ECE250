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

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

/*
	Destructor for Trie, it will empty the whole tree and the pointer to the tree.
*/
Trie::~Trie() {
	if(root_node!= nullptr){
		clear();
	}
	delete root_node;
}

/*
	Return number of words in the tree by returning the variable trie_size value.
*/
int Trie::size() const {
	return trie_size;
}

/*
	Check if the tree is empty, if so, then return true, or else return false.
*/

bool Trie::empty() const {
	if(trie_size==0){
		return true;
	}
	else{
		return false;
	}
}
/*
	Returns the root_node pointer.
*/
Trie_node *Trie::root() const {
	return root_node;
}
/*
	first check if the inputs are legal (which is an english alphabet), then make sure to convert them into lower case (insist to
	be for the program), and then if the pointer to the root of the tree points to nullptr, returns false since the tree doesn't exist,
	else calls root_node's member function from the trie_node program with the word parse in, and the depth which is 0, since we just start
	from the beginning of the word.
*/
bool Trie::member( std::string const &str ) const {
	for (int i=0; i<str.size();i++){
		if(!(tolower(str[i])>96 && tolower(str[i])<123)){
			throw illegal_argument();
		}
	}
	if(root_node==nullptr){
		return false;
	}
	return root_node->member(str, 0);
}
/*
	Same as member function, first check if the string input is valid, then convert it to lower case. Then if the tree doesn't exist, make a root_node
	and, and then calls insert function from the Trie node program. And declare a flag to store the final return value from the function, and if inserted 
	successfully, then increment trie_size (number of words in the tree). And return the value of the flag.
*/
bool Trie::insert( std::string const &str ) {
	for (int i=0; i<str.size();i++){
		if(!(tolower(str[i])>96 && tolower(str[i])<123)){
			throw illegal_argument();
		}
	}

	if(root_node == nullptr){
		root_node= new Trie_node();
	}
	bool flag;
	flag = root_node->insert(str,0);
	if(flag){
		trie_size++;
	}
	return flag;
}
/*
	Same as insert function, first check if the string input is valid, then convert it to lower case. Then if the tree doesn't exist, return 
	false. Or else it will call the erase function from the Trie node program, and it store the return value in flag, then if flag is true, then
	decrement the value in trie_size, and then return the flag value.
*/
bool Trie::erase( std::string const &str ) {
	for (int i=0; i<str.size();i++){
		if(!(tolower(str[i])>96 && tolower(str[i])<123)){
			throw illegal_argument();
		}
	}

	if(root_node == nullptr){
		return false;
	}
	bool flag;
	flag =root_node->erase(str, 0, root_node);
	if(flag){
		trie_size--;
	}

	return flag;
}

/*
	set the trie_size to 0, and then delete all the nodes in the tree by calling clear function in Trie_node and then let root_node point to nullptr.
*/
void Trie::clear() {
	if(root_node != nullptr)
    {
        root_node -> clear();
        trie_size = 0;
    }
    root_node = nullptr;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {


	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
