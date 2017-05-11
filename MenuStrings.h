/*
 * MenuStrings.h
 *
 *  Created on: 4 May 2017
 *      Author: vitor
 */

#ifndef MENUSTRINGS_H_
#define MENUSTRINGS_H_

#include <iostream>
#include <algorithm>
#include "Graph.h"

template <class T>
void exact(Graph<T> &g, string d, string s);
template <class T>
void approximate(Graph<T> &g, vector<T> &parks, string d, string s);

template <class T>
void menuStrings(Graph<T> &g, vector<T> &parks){
	string street, district;
	cout << "What is the district you're searching for?\n";
	getline(cin,district);

	cout << "What is the street you're searching for?\n";
	getline(cin,street);

	int choice2;
	cout << "Do you want to search for the street using Exact Search or Approximate Search?\n";
	cout << "0->Exact Search\n"; cout << "1->Approximate Search\n";

	cin >> choice2;
	if (choice2 == 0){
		exact(g, district, street);}
	else
		approximate(g, parks, district, street);
}

template <class T>
void exact(Graph<T> &g, string d, string s) {
	cout << "coiso";
}


template <class T>
void approximate(Graph<T> &g, vector<T> &parks, string d, string s){

	//search district d

	//if not found, return district and nearest streets to destination
	//if found, search for street
	int distance = 0;
	bool found = false;
	//int halfSize = s.size()  + 2; //tolerance
	for (int i = 0; i < g.getVertexSet().size(); i++){
		if (found)
			break;
		for (int j = 0; j < g.getVertexSet()[i]->getAdj().size(); j++){

			cout << "edgeName: " <<  g.getVertexSet()[i]->getAdj()[j].getName() << endl;
			cout << "string: " << s << endl;
			distance = getEditDistanceOT(s, g.getVertexSet()[i]->getAdj()[j].getName());
			cout << "distance: " << distance << endl;
			if (distance <= 3){
				VertexInfo v1 = g.getVertexSet()[i]->getInfo();
				VertexInfo v2 = g.getVertexSet()[i]->getAdj()[j].getDest()->getInfo();
				cout << "Street found! These are the locations that connect it:\n";
				cout << "From " <<  v1.getLabel() << " to " << v2.getLabel() << endl;
				//show on the graphviewer
				//if one of the nodes that "holds" the street is a parking lot or garage

				if (v1.getLabel() == "parking lot" || v1.getLabel() == "garage"){
					cout << "The closest park is a " <<  v1.getLabel() << " that connects the street ";
					found = true;
					break;
				}
				else if (v2.getLabel() == "parking lot" || v2.getLabel() == "garage"){
					cout << "The closest park is a " <<  v2.getLabel() << " that connects the street ";
					found = true;
					break;
				}
				//closest park
				double distance1 = 0, bestDistParking1, distance2 = 0, bestDistParking2;
				vector<T> path1, path2;
				vector<T> bestParkToDest1, bestParkToDest2;
				T bestPark1, bestPark2;

				//park to v1
				g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
				path1 = g.getPath(parks[0],v1);

				for (unsigned int z = 0; z < path1.size()-1; z++)
					distance += g.edgeCost(path1[z].getId(),path1[z+1].getId());

				bestDistParking1 = distance1;
				bestParkToDest1 = path1;
				bestPark1 = parks[0];

				//closest park to v1
				for (unsigned int p = 1;  p < parks.size(); p++){
					distance = 0;
					g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
					path1 = g.getPath(parks[p], v1); //path between destination and park p
					for (unsigned int z = 0; z < path1.size()-1; z++)
						distance += g.edgeCost(path1[z].getId(),path1[z+1].getId());

					if (distance < bestDistParking1){
						bestDistParking1 = distance;
						bestParkToDest1 = path1;
						bestPark1 = parks[p];
					}
				}
				//park to v2
				g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
				path2 = g.getPath(parks[0],v2);

				for (unsigned int z = 0; z < path2.size()-1; z++)
					distance += g.edgeCost(path2[z].getId(),path2[z+1].getId());

				bestDistParking2 = distance2;
				bestParkToDest2 = path2;
				bestPark2 = parks[0];

				//closest park to v2
				for (unsigned int p = 1;  p < parks.size(); p++){
					distance = 0;
					g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
					path2 = g.getPath(parks[p], v2); //path between destination and park p
					for (unsigned int z = 0; z < path2.size()-1; z++)
						distance += g.edgeCost(path2[z].getId(),path2[z+1].getId());

					if (distance < bestDistParking2){
						bestDistParking2 = distance;
						bestParkToDest2 = path2;
						bestPark2 = parks[p];
					}
				}

				if (bestDistParking1 < bestDistParking2)
					cout << "The closest park is a " << bestPark1.getLabel() << " and it's " << bestDistParking1 << " meters away\n";
				else
					cout << "The closest park is a " << bestPark2.getLabel() << " and it's " << bestDistParking2 << " meters away\n";
				found = true;
				break;
			}
		}
		//if not found, return district and nearest streets to destination

		//idea:
		//find district and then give 2 options:
		//1: list of all streets and then choose the street
		//2: type street name(no caps!)

	}
}


#endif /* MENUSTRINGS_H_ */
