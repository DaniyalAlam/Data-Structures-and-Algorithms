/*****************************************
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
*    - DW HARDER for his disjoint set class which was used for kruskal's algorithm
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
#include "Edge_node.h"
#include <queue>
#include "Disjoint_sets.h"
#include <map>

using namespace Data_structures;

/*
* Weighted_graph
*
* Daniyal Alam
* 2015-04-06
*
* This clas is used to implement a weighted graph. It uses an adjacency matrix that is upper triangular in order to store
* the edges and nodes. Some functionality of this class includes finding the minimum spanning tree of the graph,
* Inserting and erasing edges, etc.
* It is also worth mentioning that the edge in this graph are NOT directed and have weights associated with them. As such, this
* is a non - directional weighted graph.
*
* Member Variables:
*  int nodes;						Holds the number of vertices in the graph
*  int edges;						Holds the number of edges currently in the graph
*  int array_capacity;				Capacity of vertex_array
*  int *degree_array;				Defines an array that holds the degree of each vertex
*  double **vertex_array;			pointer to an array of pointers... The first array's indexes represent the nodes and the 
									next arrays index hold the possible combinations that can have with that node while the element
									stored is the weight of the edge connecting the two vertices.
*
*  std::multimap<Edge_node, double, comp_edge> edge_node_map;				This is a multimap that is used to store the edges as they
*																			are added in, this is used for mst function
*
*
* Member Functions (Accessors):
*  int degree(int) const;
	This function simply returns the degree of a given node. This is what the degree array was used for
*
*  int edge_count() const;
	This function simply returns the amount of edges that are currently in the graph, this is what the edge member variable
	is used for.
*
*  std::pair<double, int> minimum_spanning_tree() const;
	This is the minimum spanning tree function, it uses the multimap that has the orderd edges and checks them one by one using 
	the disjoint set data structure to come up with the minimum spanning tree (Kruskals algorithm)
*
* Member Functions (Mutators):
*  bool insert_edge(int, int, double);
	This function inserts an edge into both the adjacency matrix as well as the multimap to ensure they are inserted in order.
	Also increases the degree to the two corresponding vertices and increase the # of edges if successful.
*
*  bool erase_edge(int, int);
	This function erases the edge that exists between two given vertices
*
*  void clear_edges();
	This function just removes all the edges from the graph
*
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     Douglas Wilhelm Harder's implementation of Disjoint set data structure was used
*/

class Weighted_graph {
private:
	static const double INF;

	/*
	* struct comp_edge
	*
	* Just a small struct to implement the comparison function required for the multimap. Since we are using the Edge_node
	* as the key, it is a custom object and so we need to define how the less than operator works. In this case we are 
	* comparing using the weights of the object Edge_node
	*
	* No pre- or postconditions and no parameters.
	*
	* Returns:
	*  True or false depending on the weight of the object Edge_node
	*/
	struct comp_edge
	{
		bool operator()(const Edge_node s1, const Edge_node s2) const
		{
			return s1.weight < s2.weight;
		}
	};
	// Do not implement these functions!
	// By making these private and not implementing them, any attempt
	// to make copies or assignments will result in errors
	Weighted_graph(Weighted_graph const &);
	Weighted_graph &operator=(Weighted_graph);

	int nodes;
	int edges;
	int array_capacity;				//Capacity of vertex_array
	int *degree_array;
	double **vertex_array;
	std::multimap<Edge_node, double, comp_edge> edge_node_map;

public:
	Weighted_graph(int = 10);
	~Weighted_graph();

	int degree(int) const;
	int edge_count() const;
	std::pair<double, int> minimum_spanning_tree() const;

	bool insert_edge(int, int, double);
	bool erase_edge(int, int);
	void clear_edges();

	// Friends

	friend std::ostream &operator<<(std::ostream &, Weighted_graph const &);
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

/*********************************************************************
*                                                                   *
*   *************************************************************   *
*   *                                                           *   *
*   *   Constructor and Destructor                              *   *
*   *                                                           *   *
*   *************************************************************   *
*                                                                   *
*********************************************************************/


/*
* Weighted_graph::Weighted_graph(int n):
*
*
* The constructor for Weighted_graph class. It initializes the appropriate member variables to the appropriate
* values. It then creates the adjacency matrix that is required to hold the edges and vertices. Since no edge
* currently exits, we set all edges to INF to indicate the edge doesnt exits
*
*
* Parameters:
*  int n
*   The number of vertices the user wants their graph to contain. This is also used for calculating
*   the size of the edge array because it tells us the maximum possible number of edges that can be inserted
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

//Vertex_array is the actual array that holds the pointers for every vertex. Ie index 0 is vertex 0, etc etc
//edge_matrix refers to the matrix pointed to by the pointers in the vertex array. This is used to get store the corresponding
//edge weights. Ie, if we create an edge from 2 to 4, then access the pointer in the 4th index of vertex_array and then move to 
//the 2nd index FROM WHERE THE 4th INDEX IS POINTING TO. Vertext_array[4][2] = w where w is the weight.
Weighted_graph::Weighted_graph(int n):
nodes(n), edges(0), array_capacity(n),
degree_array(new int[n]),
vertex_array(new double *[n]) {

	int edge_matrix_size = int(n*(n - 1) / 2);

	vertex_array[0] = nullptr;
	vertex_array[1] = new double[edge_matrix_size];

	//use the same loop to initialize both degree_array and vertex_array.
	//start from 0 and go to n, wehn it gets to 2, start initializing the pointers in vertex_array as well
	for (int i = 2; i < n; ++i){
		degree_array[i] = 0;
		if (i >= 2){
			vertex_array[i] = vertex_array[i - 1] + i - 1;			//pointer arithmetic
		}
	}
	//start from 0 up to the size of max possible edges and set everything to INF
	for (int i = 0; i < edge_matrix_size; ++i){
		vertex_array[1][i] = INF;
	}

}

/*
* Weighted_graph::~Weighted_graph()
*
* All the memory that was allocated by the constructor needs to be de allocated. this ensures that
* nothing remains taking up space in the memory.
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Nothing
*/

Weighted_graph::~Weighted_graph() {
	delete[] degree_array; 
	delete[] vertex_array[1];
	delete[] vertex_array;
}

/*********************************************************************
*                                                                   *
*   *************************************************************   *
*   *                                                           *   *
*   *   Accessors                                               *   *
*   *                                                           *   *
*   *************************************************************   *
*                                                                   *
*********************************************************************/


/*
* int Weighted_graph::degree(int i) const
*
* Returns the degree of a given vertex
*
* Handles the cases that are not allowed by itself by throwing ilegal argument exception.
*
* Returns:
*  Degree of a given vertex
*/

int Weighted_graph::degree(int i) const{
	if (i < 0 || i > array_capacity - 1){
		throw illegal_argument();
	}
	return degree_array[i];
}

int Weighted_graph::edge_count() const{
	return edges;
}

/*
* std::pair<double, int> Weighted_graph::minimum_spanning_tree() const
*
*
* Uses Kruskal's algorithm to return a minimum spanning tree of the current graph. It iterates through the already sorted 
* multimap and checks to see whether the edge's vertices create a cycle in the disjoint set DS. If not, it adds
* the weight to the cumulative weight.
*
* Preconditions:
*  NONE
*
* Postconditions:
*  NONE
*
* Parameters:
*  No parameters
*
* Returns:
*  A pair containing the cumulative weight of the resulting spanning tree and the number of edges that were tested
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     cplusplus.com
*/

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {

	Disjoint_sets myset(nodes);
	double cumulative_weight = 0;
	int mst_edges = 0;
	int tested_edges = 0;

	//loop through with an constant iterator (because its a constant function) from edge_node_map.begin() and stop at 
	//edge_node_map.end() each time incrementeing the amount of tested edges and only update the cumulative weight if
	//the edge does not create a cycle. (ie, 2 vertices are not already in the same set). When we reach edges = nodes-1 then break
	for (std::multimap<Edge_node, double>::const_iterator it = edge_node_map.begin(); it != edge_node_map.end(); ++it){
		++tested_edges;
		if (myset.find(it->first.v1) != myset.find(it->first.v2)){
			cumulative_weight = cumulative_weight + it->first.weight;
			myset.set_union(it->first.v1, it->first.v2);
			++mst_edges;
		}
		if (mst_edges == nodes - 1){
			break;
		}
	}

	return std::pair<double, int>(cumulative_weight, tested_edges);
}

/*********************************************************************
*                                                                   *
*   *************************************************************   *
*   *                                                           *   *
*   *   Mutators                                                *   *
*   *                                                           *   *
*   *************************************************************   *
*                                                                   *
*********************************************************************/


/*
* bool Weighted_graph::insert_edge(int i, int j, double d)
*
*
* Inserts an edge between the vertices given as parameters whith the weight given as a parameter. It also
* inserts it into the multimap while taking into account that fact that a replacement edge should first
* erase the edge from the multimap and then insert into it again with the updated weight. Also, because the
* way we defined our adjacency matrix, we would go out of bounds if we indexed with a smaller vertex before, so we need
* two separate cases for when v1 < v2 and v1 > v2. both do similar things.
*
* Preconditions:
*  i < 0 || j < 0 || i > array_capacity-1 || j > array_capacity - 1 || d <= 0
*  If any of the above conditions are met, throw an exception. or if the vertices are the same, do nothing.
*
* 
*
* Parameters:
*  int i
*   This is the first vertex
*		it cannot be greater than max vertices
*
*  int j
*   this is the second vertex
*		it cannot be greater than max vertices
*
*  double d
*	This is the weight of the edge to be added
*		weight cannot be negative
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:    cplusplus.com (multimaps)
*/

bool Weighted_graph::insert_edge(int i, int j, double d) {
	if (i < 0 || j < 0 || i > array_capacity-1 || j > array_capacity - 1 || d <= 0){
		throw illegal_argument();
	}
	if (i == j){
		return false;
	}


	degree_array[i] = degree_array[i] + 1;
	degree_array[j] = degree_array[j] + 1;

	//make sure the greater vertex is indexed first, then do the insertions
	if (i < j){

		//if edge already exists then need to replace the edge with new weight
		if (vertex_array[j][i] != INF){
			//find using old weight in map and set to new weight
			double old = vertex_array[j][i];

			//erase the old by finding it from adjacency matrix (I know using find is stupid but for some reason it increases runtime)
			edge_node_map.erase(edge_node_map.find(Edge_node(j, i, old)));

			//insert the new edge using insert.
			edge_node_map.insert(std::pair<Edge_node, double>(Edge_node(j, i, d), d));
			
			//insert it also into the main adjacency matrix graph
			vertex_array[j][i] = d;
			++edges;
			return true;
		}
		//else its INF then just add to map as well as edge array
		edge_node_map.insert(std::pair<Edge_node, double>(Edge_node(j, i, d), d));
		vertex_array[j][i] = d;
		++edges;
		return true;
	}
	else if (i > j){

		if (vertex_array[i][j] != INF){
			//find using old weight in map and set to new weight
			double old = vertex_array[i][j];

			//erase the old by finding it from adjacency matrix (I know using find is stupid but for some reason it increases runtime)
			edge_node_map.erase(edge_node_map.find(Edge_node(i, j, old)));

			//insert the new edge using insert.
			edge_node_map.insert(std::pair<Edge_node, double>(Edge_node(i, j, d), d));

			//insert it also into the main adjacency matrix graph
			vertex_array[i][j] = d;
			++edges;
			return true;
		}
		//else its INF then just add to map as well as edge array
		edge_node_map.insert(std::pair<Edge_node, double>(Edge_node(i, j, d), d));
		vertex_array[i][j] = d;
		++edges;
		return true;
	}

}

/*
* bool Weighted_graph::erase_edge(int i, int j)
*
* Erases the edge that are connecting the two vertices given by the parameter.
* does this in both the multimap and adjacency matrix and reassigns the values of member variables
* appropriately
*
* Pre-conditions
*	i < 0 || j < 0 || i > array_capacity - 1 || j > array_capacity - 1
*		If any of the above are true then throws an exception. And if i = j, then does nothing
*
*
* Parameters:
*	int i
*		This is the first vertex
*			It cannot be greater than max vertices
*
*	int j
*		this is the second vertex
*			It cannot be greater than max vertices
*
* Returns:
*  True or false depending on the success of the erase
*/

bool Weighted_graph::erase_edge(int i, int j) {

	if (i < 0 || j < 0 || i > array_capacity - 1 || j > array_capacity - 1){
		throw illegal_argument();
	}
	if (i == j){
		return true;
	}

	//make sure the greater vertex is indexed first. i<j or i>j seperately
	if (i < j){
		//if the edge exists, then erase it from everywhere and assign member variables appropriately
		if (vertex_array[j][i] != INF){
			degree_array[i] = degree_array[i] - 1;
			degree_array[j] = degree_array[j] - 1;
			edge_node_map.erase(edge_node_map.find(Edge_node(j, i, vertex_array[j][i])));
			vertex_array[j][i] = INF;
			--edges;
			return true;
		}
		//else it doesnt exist and return false.
		return false;
		
	}
	if (i > j){
		//if the edge exists, then erase it from everywhere and assign member variables appropriately
		if (vertex_array[i][j] != INF){
			degree_array[i] = degree_array[i] - 1;
			degree_array[j] = degree_array[j] - 1;
			edge_node_map.erase(edge_node_map.find(Edge_node(i, j, vertex_array[i][j])));
			vertex_array[i][j] = INF;
			--edges;
			return true;
		}
		//else it doesnt exist and return false
		return false;
	}
	

}

/*
* void Weighted_graph::clear_edges()
*
* Goes through the adjacency matrix and sets all the values to INF effectively removing all the edges in the map
* ALso calls clear on the multimap to erase everything.
* Also resets the # of edges and degrees of every vertex to 0
*
* No pre- or postconditions and no parameters.
*
* Returns:
*  Nothing
*/

void Weighted_graph::clear_edges(){
	for (int i = 0; i < int(array_capacity*(array_capacity - 1) / 2); ++i){
		vertex_array[1][i] = INF;
		if (i >= 0 && i <= nodes){
			degree_array[i] = 0;
		}
	}
	edge_node_map.clear();
	edges = 0;

}

std::ostream &operator<<(std::ostream &out, Weighted_graph const &graph) {
	// Your implementation

	return out;
}

#endif
