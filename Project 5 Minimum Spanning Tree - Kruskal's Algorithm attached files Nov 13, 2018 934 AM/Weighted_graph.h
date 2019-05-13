
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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

/*
	Added in edge struct, to keep track of the weight and the vertices that are linked
	to the edge.
*/

struct edge{ 
	double weight;
	int firstVertex;
	int secondVertex;
	bool flag;
};

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;
		int *degrees;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};


const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

/*
	Constructor of the Weighted_graph, it will make a graph with the size of the input
parameter n, it will also set variables to appropriate initial values. Also added an pointer
array of degrees which contains the degree of each nodes for return of the degree function.
It initializes all the entries in graph to be INF for a not connected graph.
*/
Weighted_graph::Weighted_graph(int n ) {
	if(n<0){
		throw illegal_argument();
	}
	graph = new double*[n];
	degrees = new int[n];
	num_edges = 0;
	num_nodes = n;

	for (int i =0;i<n;i++){
		graph[i] = new double[n];
		degrees[i] = 0;
	}

	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			graph[i][j] = INF;
		}
	}
}

/*
	Destructor of the Weighted_graph, it will delete all the memory allocated for the project.
*/
Weighted_graph::~Weighted_graph() {
	for (int i=0;i<num_nodes;i++){
		delete[] graph[i];
	}
	delete[] degrees;
	delete[] graph;
}

/*
	Returns the degrees of the node specified from the parameter.
*/
int Weighted_graph::degree(int u) const {
	if(u <0 || u>=num_nodes){
		throw illegal_argument();
	}
	else{
		return degrees[u];
	}
}
/*
	returns the number of edges connected of the whole graph.
*/
int Weighted_graph::edge_count() const {
	return num_edges;
}

/*
	erase_edge fucntion, it will check if there is an edge between the two nodes, and if there is,
	then it will initialize the graph back to the initial INF value, and then decreases the number of edges, and 
	then also decrements the degrees for both nodes. And if the parameters are not in range of the appropriate ranges, it
	will throw an illegal_argumemnt exception.
*/
bool Weighted_graph::erase_edge(int i, int j) {
	if(i<0||j<0||i>=num_nodes||j>=num_nodes){
		throw illegal_argument();
	}
	if(i==j){
		return true;
	}
	if(graph[i][j]!=INF && graph[j][i]!=INF){
		graph[i][j]=INF;
		graph[j][i]=INF;
		num_edges--;
		degrees[i]--;
		degrees[j]--;
	}
	else{
		return false;
	}
	return true;
}
/*
	clear_edge function will set all the entries in graph back to INF, and reset the num_edges value to 0.
*/

void Weighted_graph::clear_edges() {
	num_edges = 0;
	for (int i =0;i<num_nodes;i++){
		for (int j=0;j<num_nodes;j++){
			graph[i][j] = INF;
			graph[j][i] = INF;
			degrees[i] = 0;
			degrees[j] = 0;
		}
	}
	return;
}
/*
	insert_edge function will take 3 parameters, the two nodes that want to inser the edge between, and then the 
	weight for the edge. It will check if the parameters are in appropriate ranges, and also if the both nodes are 
	the same node, it will return false. Then it will check that if there is no edge between the two nodes, it will insert
	the node, and increments num_edges and degree of the nodes. And if there does exist an edge between the two nodes, it will
	update the edge.
*/

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	if(i==j && i<num_nodes && j<num_nodes){
		return false;
	}
	if(i<0||j<0||i>=num_nodes||j>=num_nodes||d<0){

		throw illegal_argument();
	}

	if(graph[i][j]==INF && graph[i][j]==INF){
		graph[i][j]=d;
		graph[j][i]=d;
		num_edges++;
		degrees[i]++;
		degrees[j]++;
	}
	else{
		graph[i][j]=d;
		graph[j][i]=d;
	}

	return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
	Disjoint_set sets = Disjoint_set(num_nodes);
	int counter =0;
	edge ** edges_track = new edge *[num_edges];
	/*
		edges_track array is used to store all the edges in the graph, and it contains the information
		for the weight of the edge, and the nodes that are connected by the edge.
	*/

	for (int i =0;i<num_nodes;i++){
		for(int j=0;j<num_nodes;j++){
			if(i > j){
				continue;
			}
			if(graph[i][j]!=INF){
				edges_track[counter] = new edge();
				edges_track[counter]->weight = graph[i][j];
				edges_track[counter]->firstVertex = i;
				edges_track[counter]->secondVertex = j;
				counter++;
			}
		}
	}
	/*
		Sort all the edges in ascending order to be able to apply Kruskal's algorithm.
	*/
	edge *key;
	int i, j;
	for (i=1;i< num_edges;i++){
		key = edges_track[i];
		j=i-1;
		while(j>=0 && edges_track[j]->weight > key->weight){
			edges_track[j+1] = edges_track[j];
			j=j-1;
		}
		edges_track[j+1] = key; 
	}

	/*
		loop through the edges from smallest to greatest, and checks if the disjoint set only has one set left, that
		means the tree is completed, exit immediately out of the loop. Or else it will start with the least valued edge,
		and then check if the two sets that contains each node are the same set or not, if not that means the edge is not 
		connected for both nodes, then it will union the both sets and
		also add the edge's weight to the totalWeight variable; increnments the number of edges (edge_counter).
	*/

	double totalWeight =0;
	int edge_counter = 0;
	for (int i=0; i< num_edges;i++){
		if(sets.num_sets() == 1){
			break;
		}
		if(sets.find_set(edges_track[i]->firstVertex) != sets.find_set(edges_track[i]->secondVertex)){
			sets.union_sets(edges_track[i]->firstVertex, edges_track[i]->secondVertex);
			totalWeight += edges_track[i]->weight;
		}
		edge_counter++;
	}
	/*
		free the memory of the edges_track after completing the MST to prevent memory leaks.
	*/

	for (int i=0;i<num_edges;i++){
		delete edges_track[i];
	}
	delete[] edges_track;
	/*
		returns the total weight of the tree and number of edges in it.
	*/
	return std::pair<double, int>( totalWeight, edge_counter );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif
