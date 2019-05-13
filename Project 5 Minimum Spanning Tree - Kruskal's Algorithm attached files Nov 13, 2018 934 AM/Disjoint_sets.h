
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};
/*
	Disjoint_set constructor, it intializes array of nodes and sets, and it head and the 
	tail of the set will be the node itself, because initially, there are n number of nodes and sets.
	The node's ptr_to_info will also points to its own set, and "next" will point to nullpointer, and 
	the content of the node will just be the location in the index from 0-numsets(which is same as its location
	in both set and node array).
*/

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	// initialize the sets	
	for (int i=0; i<initial_num_sets; i++){
		nodes[i] = new ll_entry();
		sets[i] = new set_info();
		sets[i]->head=nodes[i];
		sets[i]->tail=nodes[i];
		sets[i]->size = 1;
		nodes[i]->ptr_to_info=sets[i];
		nodes[i]->next=nullptr;
		nodes[i]->content = i;
	}
}

/*
	Destructor of the Disjoint_set, it will free all the memories assigned in the constructor.
*/

Disjoint_set::~Disjoint_set() {
	for (int i=0; i< initial_num_sets;i++){
		delete sets[i];
		delete nodes[i];
	}
	delete[] sets;
	delete[] nodes;
	// deallocate memory
}
/*
	find_set function will return the index of the first node inside the set that countains the node searching
	for. Which will be consistant to distinguish between sets.
*/
int Disjoint_set::find_set(int item) const{
	// should it be? return nodes[item]->ptr_to_info->head->content 
	return nodes[item]->ptr_to_info->head->content;
}
/*
	num_sets function will retruns the nunmber of sets left.
*/
int Disjoint_set::num_sets() const {
	return set_counter;
}

/*
	union_sets will combines two sets, it will points all the nodes in the smaller set point to the larger set,
	then set the tail node's next pointer points to the smaller set's head node, then it will set the tail of 
	the larger set to the tail node of the smaller set. It will decrement the set_counter.
*/

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;


	/* iterate through the shorter list and modify the pointers
	while (has not reached the end of set) {
		....
	}*/
	int new_size = nodes[ni1]->ptr_to_info->size + nodes[ni2]->ptr_to_info->size;
	ll_entry* small_node_loop = nodes[ni2]->ptr_to_info->head;
	set_info* smaller_set = nodes[ni2]->ptr_to_info;
	set_info* larger_set = nodes[ni1]->ptr_to_info;
	while(small_node_loop != nullptr){
		small_node_loop->ptr_to_info = larger_set;
		small_node_loop = small_node_loop->next; 
	}
	larger_set->size = new_size;
	larger_set->tail->next = smaller_set->head;
	larger_set->tail = smaller_set->tail;

	set_counter --;
	// do we need to modify anything else?
	

	// delete the set_info entry that no longer exists
	
	
}


#endif
