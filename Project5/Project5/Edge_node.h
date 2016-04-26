/*
* Edge_node
*
* Daniyal Alam
* 2015-04-06
*
* Just a class that implements the node edge. It consist of two vertices and a weight.
* Everything that is needed for an edge is in here
*
* Member Variables:
*  int v1;				//first vertex
*  int v2;				//second vertex
*  double weight;		//weight of the edge
*
*
*
* Functions:      
*  Edge_node(int i, int j, double w) :
*   Constructor for the node class, initializes the vertices and weight
*
* Bugs:           // if applicable
* Todo:           // if applicable
* References:     // if applicable (very useful)
*/

class Edge_node{
public:
	int v1;
	int v2;
	double weight;


	Edge_node(int i, int j, double w) :
		v1(i), v2(j), weight(w){
		//empty constructor
	}

};