
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
void exact(Graph<T> &g, vector<T> &parks, string d, string s);
template <class T>
void approximate(Graph<T> &g, vector<T> &parks, string d, string s);

template <class T>
void menuStrings(Graph<T> &g, vector<T> &parks){
	string street, district, map, go;
	getline(cin,district);
	cout << "Here's the map:\n";
	printGraphPath();
	cout << "What is the street you're searching for?\n";
	getline(cin,street);

	int choice2;
	cout << "Do you want to search for the street using Exact Search or Approximate Search?\n";
	cout << "0->Exact Search\n"; cout << "1->Approximate Search\n";

	cin >> choice2;
	if (choice2 == 0){
		exact(g, parks, district, street);}
	else
		approximate(g, parks, district, street);
}

template <class T>
void exact(Graph<T> &g, vector<T> &parks, string d, string str) {
	vector<streetInfo> streets, foundStreets;
	int adjSize, graphSize =g.getVertexSet().size();
	bool found;
	for(int i =0; i < graphSize; i++){
		adjSize = g.getVertexSet()[i]->getAdj().size();
		for(int j =0; j < adjSize; j++){
			found = false;
			streetInfo s;
			s.v1 = g.getVertexSet()[i]->getInfo();
			s.v2  = g.getVertexSet()[i]->getAdj()[j].getDest()->getInfo();
			s.street = g.getVertexSet()[i]->getAdj()[j].getName();
			for (unsigned int i = 0; i < streets.size(); i++)
				if (streets[i].street == s.street){
					found = true;
					break;
				}
			if (!found)
				streets.push_back(s);
		}
	}
	for(unsigned int a = 0; a < streets.size(); a++)
		if((kmp(streets.at(a).street,str)) != 0){
			foundStreets.push_back(streets.at(a));
			found = true;
		}

	if(!found)
		cout << "The street you asked for isn't in our data base.";

	else{
		bool valid = false;
		int a;
		while(!valid){
			cout << "Is the street you're looking for one of these?\n(choose the number, if your street isn't found, type -1)\n";
			for (unsigned int i = 0; i < foundStreets.size(); i++)
				cout << i << ": " << foundStreets[i].street << endl;
			cin >> a;
			if (a == -1){
				cout << "That street does not exist\n";
				valid = true;
			}
			else {
				cout << "Is " << foundStreets[a].street << " the street you're looking for?(Y/N)?\n";
				string ans;
				cin >> ans;
				if (ans == "Y" || ans == "y" || ans == "YES" || ans == "yes" || ans == "Yes"){
					nearestPark(g,parks,foundStreets[a].v1,foundStreets[a].v2);
					valid = true;
				}
				else if (ans == "N" || ans == "n" || ans == "NO" || ans == "no" || ans == "No")
					cout << "Let's try again\n";
			}
		}
	}

}

template <class T>
void nearestPark(Graph<T> &g,vector<T> &parks, VertexInfo v1, VertexInfo v2){

	cout << "Street found! These are the locations that connect it:\n";
	cout << "From " <<  v1.getLabel() << "(blue) to " << v2.getLabel() << "(red)" << endl;
	gv->setVertexColor(v1.getId(), "blue");
	gv->setVertexColor(v2.getId(), "red");
	gv->rearrange();
	Sleep(5000);
	//if one of the nodes that "holds" the street is a parking lot or garage
	if (v1.getLabel() == "parking lot" || v1.getLabel() == "garage"){
		cout << "The closest park is a " <<  v1.getLabel() << " that connects the street\n";
		cout << "The price will be " << v1.getCost() << "€/hour\n";
		return;
	}
	else if (v2.getLabel() == "parking lot" || v2.getLabel() == "garage"){
		cout << "The closest park is a " <<  v2.getLabel() << " that connects the street\n";
		cout << "The price will be " << v2.getCost() << "€/hour\n";
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
		cout << "The closest park is a " << bestPark1.getLabel() << " and it's " << bestDistParking1 << " meters away\n"  << "The price will be " << bestPark1.getCost() << "€/hour\n";
	else
		cout << "The closest park is a " << bestPark2.getLabel() << " and it's " << bestDistParking2 << " meters away\n"  << "The price will be " << bestPark2.getCost() << "€/hour\n";

}


template <class T>
void approximate(Graph<T> &g, vector<T> &parks, string d, string str){

	int distance = 0, graphSize =g.getVertexSet().size(), adjSize;
	bool found = false;
	vector<streetInfo> similarStreetNames, streetNames;
	for (int i = 0; i < graphSize; i++){
		adjSize = g.getVertexSet()[i]->getAdj().size();
		for (int j = 0; j < adjSize; j++){
			string edgeName =  g.getVertexSet()[i]->getAdj()[j].getName();
			distance = editDistance(str, edgeName);
			streetInfo s;
			s.v1 = g.getVertexSet()[i]->getInfo();
			s.v2 = g.getVertexSet()[i]->getAdj()[j].getDest()->getInfo();
			s.street = edgeName;

			if (distance <= 5){
				for (unsigned int i = 0; i < similarStreetNames.size(); i++)
					if (similarStreetNames[i].street == s.street){
						found = true;
						break;
					}
				if (!found)
					similarStreetNames.push_back(s);

			}
			else if (distance > 5 && edgeName.size() > str.size() ){
				for (unsigned int i = 0; i < similarStreetNames.size(); i++)
					if (streetNames[i].street == s.street){
						found = true;
						break;
					}
				if (!found)
					streetNames.push_back(s);
			}
		}
	}
	//if there are similar possible streets
	if (similarStreetNames.size() > 0)	{
		bool valid = false;
		int a;
		while(!valid){
			cout << "Is the street you're looking for one of these?\n(choose the number, if your street isn't found, type -1)\n";
			for (unsigned int i = 0; i < similarStreetNames.size(); i++)
				cout << i << ": " << similarStreetNames[i].street << endl;
			cin >> a;
			if (a == -1){
				cout << "That street does not exist\n";
				valid = true;
			}
			else {
				cout << "Is " << similarStreetNames[a].street << " the street you're looking for?(Y/N)?\n";
				string ans;
				cin >> ans;
				if (ans == "Y" || ans == "y" || ans == "YES" || ans == "yes" || ans == "Yes"){
					nearestPark(g,parks,similarStreetNames[a].v1,similarStreetNames[a].v2);
					valid = true;
				}
				else if (ans == "N" || ans == "n" || ans == "NO" || ans == "no" || ans == "No")
					cout << "Let's try again\n";
			}
		}
	}
	//if there are multiple possible streets
	else {
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
			else {
				cout << "Is " << streetNames[a].street << " the street you're looking for?(Y/N)?\n";
				string ans;
				cin >> ans;
				if (ans == "Y" || ans == "y" || ans == "YES" || ans == "yes" || ans == "Yes"){
					nearestPark(g,parks,streetNames[a].v1,streetNames[a].v2);
					valid = true;
				}
				else if (ans == "N" || ans == "n" || ans == "NO" || ans == "no" || ans == "No")
					cout << "Let's try again\n";
			}
		}
	}

}


#endif /* MENUSTRINGS_H_ */
