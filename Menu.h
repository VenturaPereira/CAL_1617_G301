/*
 * Menu.cpp
 *
 *  Created on: 6 Apr 2017
 *      Author: vitor
 */

#include <iostream>
#include "Graph.h"
#include "Utilities.h"
using namespace std;

template<class T>
void showPath(int gas,int location,int destination, Graph<T> &g, vector<T> &parks){

	int distance = 0;
	int bestDist, bestInd;
	vector<T> path;


	//g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
	g.dijkstraShortestPath(g.getVertexSet().at(destination)->getInfo());

	path = g.getPath(parks[0],g.getVertexSet().at(destination)->getInfo());

	cout << "path:" << path.size();

	/*for (int z = 1; z < path.size(); z++)
		distance += g.edgeCost(path[z--].getId(),path[z].getId());

	bestDist = distance;
	bestInd = parks[0].getId();
	for (int p = 1; p < parks.size(); p++){
		path = g.getPath(g.getVertexSet().at(destination)->getInfo(),parks[p]); //path between destination and first park
		for (int i = 1; i <= path.size(); i++){
			distance += g.edgeCost(path[i--].getId(),path[i].getId());
			if (distance < bestDist){
				bestDist = distance;
				bestInd = parks[i].getId();
			}
		}
	}

	cout << bestInd;*/

	//g.dijkstraShortestPath((g.getVertexSet().at(i)->getInfo())); //for the locations

	//verificiar parque mais proximo do destino
	//verificar do inicio para o parque mais proximo

	//distance for one park



}

template<class T>
void showOptions(Graph<T> &g){
	for(unsigned int i =0; i < g.getVertexSet().size(); i++)
		if(g.getVertexSet()[i]->getInfo().getLabel() != "garage" && g.getVertexSet()[i]->getInfo().getLabel() != "crossroad" && g.getVertexSet()[i]->getInfo().getLabel() != "parking lot")
			cout << g.getVertexSet()[i]->getInfo().getId() << " " <<  g.getVertexSet()[i]->getInfo().getLabel() << " x: "<< g.getVertexSet()[i]->getInfo().getX() << " y: "<<  g.getVertexSet()[i]->getInfo().getY()<< "\n";
}

template<class T>
void menu(Graph<T> &g, vector<T> parks){
	int location, destination, gas;
	bool valid = false;
	while(!valid){
		cout << "Good day \n" << "Where are you?(choose the node id)\n";
		showOptions(g);
		cin >> location;
		cout << "Where are you headed?(choose the node id)\n";
		showOptions(g);
		cin >> destination;
		if (location != destination)
			valid = true;
		cout << "Do you wish to refill?\n1-Yes \n2-No \n";
		cin >> gas;
		showPath(gas, location, destination, g, parks);
	}
}


