#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "DynArr.h"
#include "stack.h"
#include "PriorityQueue.h"
#include "MSTElem.h"
#include "LinearProbe.h"
#include <iostream>
#include <vector>
template<class T>
class Graph{

	private:

		std::vector< Vertex< T > > vertices;	// Adjacency List

	public:
		// Constructor
		Graph( ) : vertices() {}

		// Add a vertex prior to any edges
		void add_vertex( T vertexData ){

			Vertex<T> theVertex( vertexData );
			vertices.push_back( theVertex );
		}



		// Add Edge from Origin to Destination, with weight
		void add_edge(unsigned int origin, unsigned int destin, float weight ){
			if( origin < vertices.size() && destin < vertices.size() ){

				vertices[origin].add_edge( destin, weight );

			}
		}

		Graph<T> MST(unsigned int src){

					Graph<T> MSTGraph;

					// Set up the priority queue for the algorithm
					PriorityQueue< MSTElem > MST_PQ;

					// Use a Hash Table for the Frontier
					HashTable< unsigned int, bool > frontier;

					// Track the parents of the vertex
					unsigned int* parents = new unsigned int[ vertices.size() ];

					// Track the weights of the edges
					float* weights =  new float[ vertices.size() ];

					// Initialize the origin and push onto the Priority Queue
					MSTElem origin( src, 0 );
					MST_PQ.push( origin );

					// Set the origin on the frontier to true
					frontier.insert( {src, true} );

					// Set the parent's origin to -1 and weight to largest negative value
					parents[src] = -1;
					weights[src] = (float) -2147483648;

					for( unsigned int i = 0; i < vertices.size(); i++ ){
						if(i == src) continue;
						MSTElem temp( i, (float) 2147483647 );
						weights[i] = (float) 2147483647;
						MST_PQ.push( temp );
						frontier.insert( {i, true} );
					}

					while( !MST_PQ.empty() ){

						// Obtain the first element
						MSTElem currElem = MST_PQ.front();

						// Remove the first element
						MST_PQ.pop();

						// Set the current node in the frontier to false
						frontier[ currElem.index ] = false;

						// Go through all the outgoing edges of the vertex
						for( unsigned int i = 0; i < vertices[ currElem.index ].num_edges(); i++ ){

							// Get the current edge from MST current element's vertex
							Edge currEdge = vertices[ currElem.index ].get_edge( i );

							if( currEdge.weight < weights[ currEdge.destin ] && frontier[ currEdge.destin ] ){

								weights[ currEdge.destin ] = currEdge.weight;
								parents[ currEdge.destin ] = currElem.index;

								MSTElem pushElem( currEdge.destin, currEdge.weight);
								MST_PQ.push( pushElem );

							}
						}
					}

					for( unsigned int i = 0; i < vertices.size(); i++){

						MSTGraph.add_vertex( vertices[i].get_vertex_value() );
					}

					for( unsigned int i = 0; i < vertices.size(); i++){

						if( parents[i] != -1 ){

							MSTGraph.add_edge( parents[i], i, weights[i] );

						}
					}

					

					return MSTGraph;

				}

		// Dijkstra's Algorithm
	void Dijkstra( unsigned int origin, unsigned int destin, std::string arr[] ){


			if( origin >= vertices.size() || destin >= vertices.size() || vertices.size() == 0 ){

				std::cout << "Invalid Inputs" << std::endl;
				return;

			}

			/* Initialize the Elements */
			stack< unsigned int > theStack;
			std::vector< unsigned int > parents(vertices.size(), 0);
			std::vector< float > distance(vertices.size(), 0);
			stack< unsigned int > finalPath;

			bool found = false;

			/* Initialize the origin */
			theStack.push( origin );
			distance[origin] = (float) 0;
			parents[origin] = -1;

			if( destin == origin ){
				found = true;
			}

			if( !found ){

				/* Initialize all the distances after the origin */
				for( unsigned int iter = 1; iter < vertices.size(); iter++ ){
					// Make it the largest possible int
					distance[ iter ] = (float) 2147483647;
					// Set the parent to -1
					parents[ iter ] = -1;
				}

				/* Run the shortest path algorithm */
				while( !theStack.empty() ){

					// Get the top element of the stack and pop
					unsigned int index = theStack.top();
					theStack.pop();

					// Evaluate the edges from the vertex
					for(unsigned int iter = 0; iter < vertices[ index ].num_edges(); iter++ ){

						// Obtain the edge
						Edge tempEdge = vertices[ index ].get_edge( iter );

						// If the weight of the edge plus distance of the  distance is less than the destin weight
						if( distance[ index ] + tempEdge.weight < distance[ tempEdge.destin ] ) {

							// Update the distance
							distance[ tempEdge.destin ] = distance[ index ] + tempEdge.weight;

							// Update the parent of the destin
							parents[ tempEdge.destin ] = index;

							// Check if destin is the result;
							if( tempEdge.destin == destin && !found ){

								found = true;
							}

							theStack.push( tempEdge.destin );
						}
					}
				}
			}

			// Otherwise, go through the parents until we find the origin
			if( found ){

				unsigned int sentinel = destin;
				finalPath.push( sentinel );		// Push the desination onto the stack

				while( parents[sentinel] != -1 ){

					finalPath.push( parents[sentinel] );	// Push the parent onto the stack
					sentinel = parents[sentinel];			// Update the sentinel

				}

				// Stack contains the correct order
				std::cout << "The warmest path is through ";
				while( !finalPath.empty() ){

					std::cout << arr[finalPath.top()] << "-> ";
					finalPath.pop();
				}
				std::cout <<"arrived at destination"<< std::endl;
			}

		}

		// Overloaded Operator
		friend std::ostream& operator<<( std::ostream& output, const Graph<T>& theGraph ){

			for( unsigned int iter = 0; iter < theGraph.vertices.size(); iter++ ){

				output << iter << ": " << theGraph.vertices[ iter ] << std::endl;

			}

			return output;
		}
};


void display_buildings(unsigned int &start, unsigned int &end, std::string set_buildings[]){
	unsigned int i = 1;	

	while(set_buildings[i].size() > 1){
		std::cout<<i<<" "<<set_buildings[i]<<std::endl;
		i++;
		}

	std::cout<<"Enter number of building you're at: ";
	std::cin>>start;
	std::cout<<"Enter number of building you're going to: ";
	std::cin>>end;
}


#endif
