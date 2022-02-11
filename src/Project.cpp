#include "../inc/Graph.h"
#include <iostream>
#include<string>
#include <fstream>

#define MAX_BUILDINGS 13
#define HEAD_NODE 0

int main(int argc, char* argv[]){

	Graph< std::string > theGraph;

	std::ifstream my_file_buildings;
	my_file_buildings.open(argv[argc - 2]);
	std::string set_buildings[MAX_BUILDINGS];

	unsigned int i = 0;

	while(std::getline(my_file_buildings, set_buildings[i])){
		theGraph.add_vertex(set_buildings[i]);
		i++;
	}
	my_file_buildings.close();

	std::ifstream my_file_paths;
	my_file_paths.open(argv[argc - 1]);
	unsigned int orig, dest;
	float weight;

	while(my_file_paths>>orig>>dest>>weight)
		theGraph.add_edge((unsigned int) orig, (unsigned int) dest, (float) weight);

	my_file_paths.close();

	unsigned int start, end;

	display_buildings(start, end, set_buildings);

  theGraph.add_edge(HEAD_NODE, start, 0);
	// Print results:
	//std::cout << theGraph << std::endl;

	// Run Dijkstra's Algorithm
	theGraph = theGraph.MST(HEAD_NODE);

	//std::cout<< theGraph << std::endl;

	theGraph.Dijkstra(HEAD_NODE, end, set_buildings);

	return 0;

}
