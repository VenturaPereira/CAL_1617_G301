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

struct streetInfo{
	VertexInfo v1;
	VertexInfo v2;
	string street;
};

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
void nearestPark(Graph<T> &g,vector<T> &parks, VertexInfo v1, VertexInfo v2){

	cout << "Street found! These are the locations that connect it:\n";
	cout << "From " <<  v1.getLabel() << "(blue) to " << v2.getLabel() << "(red)" << endl;
	printGraphPath();
	gv->setVertexColor(v1.getId(), "blue");
	gv->setVertexColor(v2.getId(), "red");
	gv->rearrange();
	Sleep(5000);
	//if one of the nodes that "holds" the street is a parking lot or garage
	if (v1.getLabel() == "parking lot" || v1.getLabel() == "garage"){
		cout << "The closest park is a " <<  v1.getLabel() << " that connects the street ";
		return;
	}
	else if (v2.getLabel() == "parking lot" || v2.getLabel() == "garage"){
		cout << "The closest park is a " <<  v2.getLabel() << " that connects the street ";
		return;
	}
	//closest park, by comparing the closest park to each node
	double distance1 = 0, bestDistParking1, distance2 = 0, bestDistParking2;
	vector<T> path1, path2;
	vector<T> bestParkToDest1, bestParkToDest2;
	T bestPark1, bestPark2;

	//park[0] to v1
	g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
	path1 = g.getPath(parks[0],v1);

	for (unsigned int z = 0; z < path1.size()-1; z++)
		distance1 += g.edgeCost(path1[z].getId(),path1[z+1].getId());

	bestDistParking1 = distance1;
	bestParkToDest1 = path1;
	bestPark1 = parks[0];
	//closest park to v1
	for (unsigned int p = 1;  p < parks.size(); p++){
		g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
		path1 = g.getPath(parks[p], v1); //path between destination and park p
		for (unsigned int z = 0; z < path1.size()-1; z++)
			distance1 += g.edgeCost(path1[z].getId(),path1[z+1].getId());

		if (distance1 < bestDistParking1){
			bestDistParking1 = distance1;
			bestParkToDest1 = path1;
			bestPark1 = parks[p];
		}
	}

	//park to v2
	g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
	path2 = g.getPath(parks[0],v2);

	for (unsigned int z = 0; z < path2.size()-1; z++)
		distance2 += g.edgeCost(path2[z].getId(),path2[z+1].getId());

	bestDistParking2 = distance2;
	bestParkToDest2 = path2;
	bestPark2 = parks[0];

	//closest park to v2
	for (unsigned int p = 1;  p < parks.size(); p++){
		distance2 = 0;
		g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
		path2 = g.getPath(parks[p], v2); //path between destination and park p
		for (unsigned int z = 0; z < path2.size()-1; z++)
			distance2 += g.edgeCost(path2[z].getId(),path2[z+1].getId());

		if (distance2 < bestDistParking2){
			bestDistParking2 = distance2;
			bestParkToDest2 = path2;
			bestPark2 = parks[p];
		}
	}

	if (bestDistParking1 < bestDistParking2)
		cout << "The closest park is a " << bestPark1.getLabel() << " and it's " << bestDistParking1 << " meters away\n";
	else
		cout << "The closest park is a " << bestPark2.getLabel() << " and it's " << bestDistParking2 << " meters away\n";

}


template <class T>
void approximate(Graph<T> &g, vector<T> &parks, string d, string s){

	//search district d

	//if not found, return district and nearest streets to destination
	//if found, search for street
	int distance = 0, graphSize =g.getVertexSet().size(), adjSize;
	bool found = false;
	vector<streetInfo> streetNames;
	for (int i = 0; i < graphSize; i++){
		if (found)
			break;
		adjSize = g.getVertexSet()[i]->getAdj().size();
		for (int j = 0; j < adjSize; j++){
			string edgeName =  g.getVertexSet()[i]->getAdj()[j].getName();
			distance = getEditDistanceOT(s, edgeName);
			VertexInfo v1 = g.getVertexSet()[i]->getInfo();
			VertexInfo v2 = g.getVertexSet()[i]->getAdj()[j].getDest()->getInfo();
			if (distance <= 3){
				nearestPark(g,parks,v1,v2);
				streetNames.clear();
				found = true;
				break;
			}
			else if (distance > 3 && distance < 6){
				streetInfo s;
				s.v1 = v1;
				s.v2 = v2;
				s.street = edgeName;
				streetNames.push_back(s);
			}
		}
		//if not found, return district and nearest streets to destination

		//idea:
		//find district and then give 2 options:
		//1: list of all streets and then choose the street
		//2: type street name(no caps!)

	}
	//if the are multiple possible streets
	if (streetNames.size() > 1)
	{
		bool valid = false;
		int a;
		while(!valid){
			cout << "Is the street you're looking for one of these?\n(choose the number, if your street isn't found, type -1)\n";
			for (unsigned int i = 0; i < streetNames.size(); i++)
				cout << i << ": " << streetNames[i].street << endl;
			cin >> a;
			if (a == -1){
				cout << "That street does not exist\n";
				valid = true;
			}
			else
			{
				cout << "Is " << streetNames[a].street << " the street you're looking for?(Y/N)?\n";
				string ans;
				cin >> ans;
				if (ans == "Y"){
					nearestPark(g,parks,streetNames[a].v1,streetNames[a].v2);
					valid = true;
				}
				else if (ans == "N")
					cout << "Let's try again\n";
			}
		}
	}

}


#endif /* MENUSTRINGS_H_ */
