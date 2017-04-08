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
void showPath(int gas,int location,int destination, Graph<T> &g, vector<int> &parkerinos){




	//g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
	/*for(unsigned int i = 0; i < g.getVertexSet().size(); i++){
		cout << g.getVertexSet().at(i)->getInfo().getId()	<< "<-";
		if(g.getVertexSet().at(i)->path != NULL)
		{
			cout << g.getVertexSet().at(i)->path->getInfo().getId();
		}
			cout << "|";
	}
*/
	int distance = 0;
	int bestDist;
	int bestInd;
	vector<T> path;
	path = g.getPath(g.getVertexSet().at(parkerinos.at(0))->getInfo(),g.getVertexSet().at(destination)->getInfo());
	cout << path->getInfo()->getId();

	//cout << "path:" << path.getId();
	/*
	for (unsigned int z = 1; z < path.size(); z++) {

		g.dijkstraShortestPath(g.getVertexSet().at(destination)->getInfo());
		bestDist = distance;
		bestInd = parkerinos.at(0);
		cout << "here";
		for (unsigned int p = 1; p < parkerinos.size(); p++){
			path = g.getPath(g.getVertexSet().at(destination)->getInfo(),g.getVertexSet().at(parkerinos.at(p))->getInfo()); //path between destination and first park
			for (unsigned int i = 1; i <= path.size(); i++){
				distance = path.at(i).;
				if (distance < bestDist){
					bestDist = distance;
					bestInd = parkerinos.at(i);
				}
			}
		}
	}
*/

	//cout << "The nearest park is " << bestInd;

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
	vector<int> parkerinos;
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
		for(unsigned int i = 0; i < parks.size(); i++){
			parkerinos.push_back(parks.at(i).getId());
		}
		showPath(gas, location, destination, g, parkerinos);
	}
}


