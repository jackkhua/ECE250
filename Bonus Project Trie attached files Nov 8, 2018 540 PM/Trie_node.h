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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}
/*
	returns the pointer to the nth children, and if the children array is empty, return nullptr.
*/
Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

/*
	Member function will first convert every letter to lower case for consistant of the program. And it will also check if the
	children array is empty, it will just return false and exit. Then it will keep calling the function recursively until the last 
	letter of the word, if the letter doesn't exist in the array, then it will return false. If we get to the last word, then last letter's is_terminal variable 
	will determine to return true or false for the function.
*/

bool Trie_node::member( std::string const &str, int depth ) const {
	char currentCharacter = str[depth];
	currentCharacter = tolower(currentCharacter);
	int characterIndex;
	if(currentCharacter > 96 && currentCharacter < 123){
		characterIndex = currentCharacter - 97;
	}

	if(depth == str.size()){
		if(is_terminal){
			return true;
		}
		else{
			return false;
		}
	}

	if(children == nullptr){
		return false;
	}
	else if(children[characterIndex] == nullptr){
		return false;
	}
	else{
		return children[characterIndex] -> member(str, ++depth);
	}
}
/*
	insert function will check each character is a valid input of the word from each stacks from the recursive calls(we keep making the call until the depth is same as the word's length)
	, and if the node with the character doesn't exist, it will make a new node for the character. And if we get to the last character of the word, if the node's
	is_terminal value is true, then we are inserting a duplicated word, which returns false; if it's false, then make the is_terminal variable
	set to true and then return true. Because we succesfully inserted a new word to the tree.
*/

bool Trie_node::insert( std::string const &str, int depth ) {
	char currentCharacter = str[depth];
	currentCharacter = tolower(currentCharacter);
	int characterIndex;
	if(currentCharacter > 96 && currentCharacter < 123){
		characterIndex = currentCharacter - 97;
	}
	if(children==nullptr){
		children = new Trie_node*[CHARACTERS];
		for (int i=0;i<CHARACTERS;i++){
			children[i] = nullptr;
		}
	}
	if(depth==str.size()){
		if(is_terminal){
			return false;
		}
		else{
			is_terminal = true;
			return true;
		}
	}
	else{
		
		if(children[characterIndex] == nullptr){
			children[characterIndex] = new Trie_node();
		}
	}
	return children[characterIndex]->insert(str,++depth);
}
/*
	erase function will check each character is a valid input of the word from stacks from the recursive calls(we keep making the call until the depth is same as the word's length)
	, and from the stacks if any character is a nullptr or the whole node list is null pointer, simply return false. Then at the last character's iteration, if it
	doesn't have a children(a root node) and also it's at the end of the word we looking for (is_terminal = true), recursively, if the character doesn't have a children,
	and it's not the end of any word in the tree, we delete the node and make it point to null. Then return true if no condition returns false.
*/

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	char currentCharacter = str[depth];
	currentCharacter = tolower(currentCharacter);
	int characterIndex;
	if(currentCharacter > 96 && currentCharacter < 123){
		characterIndex = currentCharacter - 97;
	}

	if(depth == str.size()){
		if(!is_terminal){
			return false;
		}
		else{
			is_terminal = false;
			return true;
		}
	}
	

	if(children == nullptr||children[characterIndex]==nullptr){
		return false;
	}

	if(!children[characterIndex]->erase(str, ++depth, children[characterIndex])){
		return false;
	}

	Trie_node *flag_node = children[characterIndex];
	if(flag_node->children == nullptr && flag_node->is_terminal == false){
		delete flag_node;
		children[characterIndex] = nullptr;
	}

	return true;
}
/*
	clear all the sub-trees and then delete all the nodes got called, and then delete the called node itself.
*/

void Trie_node::clear() {
	if(children != nullptr)
	{		
		for(int i = 0; i < CHARACTERS; i++)
		{	
			if(children[i]){
				children[i]->clear();
			}
		}		
		delete[] children;
	}

	//Deletes this node
	delete this;
	return;

}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
