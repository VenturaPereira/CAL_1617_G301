/*
 * Menu.cpp
 *
 *  Created on: 6 Apr 2017
 *      Author: vitor
 */

#include <iostream>
#include "Graph.h"
#include "Utilities.h"
#include <algorithm>


using namespace std;


//paints the path that goes through a gas station
template<class T>
void printPathWithGas(vector<T>LoctoGas,vector<T> GastoPark,vector<T> ParktoDest){
	for(unsigned int i = 0; i < LoctoGas.size(); i++)
	{
		Sleep(1000);
		gv->setVertexColor(LoctoGas.at(i).getId(), "blue");
		gv->rearrange();
	}

	for(unsigned int i = 0; i < GastoPark.size(); i++)
	{
		Sleep(1000);
		gv->setVertexColor(GastoPark.at(i).getId(), "green");
		gv->rearrange();
	}

	for(unsigned int i = 0; i < ParktoDest.size(); i++)
	{
		Sleep(1000);
		gv->setVertexColor(ParktoDest.at(i).getId(), "red");
		gv->rearrange();
	}
}

//paints the path that doesn't go through a gas station
template<class T>
void printPathNoGas(vector<T>LoctoPark, vector<T> ParktoDest){
	for(unsigned int i = 0; i < LoctoPark.size(); i++)
	{
		Sleep(1000);
		gv->setVertexColor(LoctoPark.at(i).getId(), "green");
		gv->rearrange();
	}

	for(unsigned int i = 0; i < ParktoDest.size(); i++)
	{
		Sleep(1000);
		gv->setVertexColor(ParktoDest.at(i).getId(), "red");
		gv->rearrange();
	}
}

template<class T>
void shortestPath(int gas,int location,int destination, Graph<T> &g, vector<T> &parks, vector<T> &gasStations){

	double distance = 0, bestDistParking, bestDistGasStation, bestDistLocation, gasToPark;
	vector<T> path;
	vector<T> bestPathGasToLoc;
	vector<T> bestParktoGas;
	vector<T> bestParkToDest;
	vector<T> bestParktoLoc;
	vector<T> ids;
	T bestPark;
	T bestGasStation;

	//parking to destination
	g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
	path = g.getPath(parks[0],g.getVertexSet().at(destination)->getInfo());

	for (unsigned int z = 0; z < path.size()-1; z++)
		distance += g.edgeCost(path[z].getId(),path[z+1].getId());

	bestDistParking = distance;
	bestParkToDest = path;
	bestPark = parks[0];

	//closest park
	for (unsigned int p = 1;  p < parks.size(); p++){
		distance = 0;
		g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
		path = g.getPath(parks[p], g.getVertexSet().at(destination)->getInfo()); //path between destination and park p
		for (unsigned int z = 0; z < path.size()-1; z++)
			distance += g.edgeCost(path[z].getId(),path[z+1].getId());

		if (distance < bestDistParking){
			bestDistParking = distance;
			bestParkToDest = path;
			bestPark = parks[p];
		}
	}

	//distance to gas station, if chosen

	if (gas == 1){
		g.dijkstraShortestPath(g.getVertexSet().at(gasStations[0].getId())->getInfo());
		path = g.getPath(g.getVertexSet().at(location)->getInfo(), gasStations[0]);
		for(unsigned int k = 0; k < path.size()-1; k++)
			distance += g.edgeCost(path[k].getId(),path[k+1].getId());
		bestDistGasStation = distance;
		bestPathGasToLoc = path;
		bestGasStation = gasStations[0];

		for(unsigned int k = 1; k < gasStations.size(); k++){
			distance = 0;
			g.dijkstraShortestPath(g.getVertexSet().at(gasStations[k].getId())->getInfo());
			path = g.getPath(gasStations[k], g.getVertexSet().at(location)->getInfo());

			for(unsigned int j = 0; j < path.size()-1; j++)
				distance += g.edgeCost(path[j].getId(), path[j+1].getId());

			if(distance < bestDistGasStation)
			{
				bestDistGasStation = distance;
				bestPathGasToLoc = path;
				bestGasStation = gasStations[k];
			}
		}

		//best gas station to best park
		g.dijkstraShortestPath(bestGasStation);
		bestParktoGas = g.getPath(bestGasStation, bestPark);

		distance = 0;
		for (unsigned int l = 0; l < path.size()-1; l++)
			distance += g.edgeCost(path[l].getId(),path[l+1].getId());
		gasToPark = distance;

	}

	else{
		//location to the park
		g.dijkstraShortestPath(g.getVertexSet().at(location)->getInfo());
		bestParktoLoc = g.getPath(g.getVertexSet().at(location)->getInfo(), bestPark);
		for (unsigned int l = 0; l < bestParktoLoc.size()-1; l++)
			distance += g.edgeCost(bestParktoLoc[l].getId(),bestParktoLoc[l+1].getId());
		bestDistLocation = distance;
	}

	if (gas == 1){
		//between gas station and location
		cout << "The closest gas station to your location is " << bestDistGasStation << " meters away." << endl;
		cout << "To get there, you'll have to follow this path: " << endl;
		reverse(bestPathGasToLoc.begin(), bestPathGasToLoc.end());
		for (unsigned int l = 0; l < bestPathGasToLoc.size(); l++)
		{
			ids.push_back(bestPathGasToLoc.at(l));
			if (l == bestPathGasToLoc.size()-1)
				cout << bestPathGasToLoc[l].getLabel() << "." << endl;
			else
				cout << bestPathGasToLoc[l].getLabel() << ", ";
		}

		cout << "The closest park to your destination is " << bestPark.getLabel() << " and it is " << gasToPark << " meters away." << endl;
		if(bestPark.getLabel() == "garage")
			cout << "The price will be 1.5$/hour" << endl;
		else if(bestPark.getLabel() == "parking lot")
			cout << "The price will be 0.75$/hour" << endl;
		cout << "After filling up your tank, you should follow this route: " << endl;
		for (unsigned int l = 0; l < bestParktoGas.size(); l++)
		{
			ids.push_back(bestParktoGas.at(l));
			if (l == bestParktoGas.size()-1)
				cout << bestParktoGas[l].getLabel() << "." << endl;
			else
				cout << bestParktoGas[l].getLabel() << ", ";
		}

		cout << "To reach your destination, you'll have to follow this path, by foot: " << endl;
		for (unsigned int l = 0; l < bestParkToDest.size(); l++)
		{
			ids.push_back(bestParkToDest.at(l));
			if (l == bestParkToDest.size()-1)
				cout << bestParkToDest[l].getLabel() << ". " << endl;
			else
				cout << bestParkToDest[l].getLabel() << ", ";
		}
	}
	else{
		//showing distance between location and park
		cout << "The closest park to your destination is " << bestPark.getLabel() << " and it is " << bestDistLocation << " meters away." << endl;
		if(bestPark.getLabel() == "garage")
			cout << "The price will be 1.5$/hour" << endl;
		else if(bestPark.getLabel() == "parking lot")
			cout << "The price will be 0.75$/hour" << endl;
		cout << "To get there, you'll have to follow this path: " << endl;
		for (unsigned int l = 0; l < bestParktoLoc.size(); l++)
		{
			ids.push_back(bestParktoLoc.at(l));
			if (l == bestParktoLoc.size()-1)
				cout << bestParktoLoc[l].getLabel() << "." << endl;
			else
				cout << bestParktoLoc[l].getLabel() << ", ";
		}


		//showing distance between park and destination
		cout << "To reach your destination, you'll have to follow this path, by foot: " << endl;
		for (unsigned int l = 0; l < bestParkToDest.size(); l++)
		{
			ids.push_back(bestParkToDest[l]);
			if (l == bestParkToDest.size()-1)
				cout << bestParkToDest[l].getLabel() << ". " << endl;
			else
				cout << bestParkToDest[l].getLabel() << ", ";
		}
	}


	cout << "The map will be updated with the path..." << endl;
	Sleep(3000);
	if (gas == 1)
		printPathWithGas(bestPathGasToLoc, bestParktoGas, bestParkToDest);
	else
		printPathNoGas(bestParktoLoc,bestParkToDest);

	getchar();
}

template<class T>
void cheapestPath(int gas,int location,int destination, Graph<T> &g, vector<T> &parks, vector<T> &gasStations){

	double distance = 0, bestDistParking, bestDistGasStation, bestDistLocation, gasToPark;
	vector<T> path;
	vector<T> bestPathGasToLoc;
	vector<T> bestParktoGas;
	vector<T> bestParkToDest;
	vector<T> bestParktoLoc;
	vector<T> ids;
	T bestPark;
	T bestGasStation;
	float cheapestCost;

	//first, we find the cheapest park and closest to the destination

	//parking to destination
	g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
	path = g.getPath(parks[0],g.getVertexSet().at(destination)->getInfo());

	for (unsigned int z = 0; z < path.size()-1; z++)
		distance += g.edgeCost(path[z].getId(),path[z+1].getId());

	bestDistParking = distance;
	bestParkToDest = path;
	bestPark = parks[0];
	cheapestCost = bestPark.getCost();

	//closest park
	for (unsigned int p = 1;  p < parks.size(); p++){
		distance = 0;
		if (parks[p].getCost() == cheapestCost) //if it's the same price, the only thing that will influence is the distance
		{
			g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
			path = g.getPath(parks[p], g.getVertexSet().at(destination)->getInfo()); //path between destination and park p
			for (unsigned int z = 0; z < path.size()-1; z++)
				distance += g.edgeCost(path[z].getId(),path[z+1].getId());

			if (distance < bestDistParking) {
				bestDistParking = distance;
				bestParkToDest = path;
				bestPark = parks[p];
				cheapestCost = parks[p].getCost();
			}
		}
		else if (parks[p].getCost() < cheapestCost) //park is cheapest, doesn't matter the distance
		{
			g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
			path = g.getPath(parks[p], g.getVertexSet().at(destination)->getInfo()); //path between destination and park p
			for (unsigned int z = 0; z < path.size()-1; z++)
				distance += g.edgeCost(path[z].getId(),path[z+1].getId());

			bestDistParking = distance;
			bestParkToDest = path;
			bestPark = parks[p];
			cheapestCost = parks[p].getCost();

		}
	}

	//distance to gas station, if chosen
	if (gas == 1){
		g.dijkstraShortestPath(g.getVertexSet().at(gasStations[0].getId())->getInfo());
		path = g.getPath( g.getVertexSet().at(location)->getInfo(), gasStations[0]);

		for(unsigned int k = 0; k < path.size()-1; k++)
			distance += g.edgeCost(path[k].getId(),path[k+1].getId());

		bestDistGasStation = distance;
		bestPathGasToLoc = path;
		bestGasStation = gasStations[0];

		for(unsigned int k = 1; k < gasStations.size(); k++){
			distance = 0;
			g.dijkstraShortestPath(g.getVertexSet().at(gasStations[k].getId())->getInfo());
			path = g.getPath(gasStations[k], g.getVertexSet().at(location)->getInfo());
			for(unsigned int j = 0; j < path.size()-1; j++)
				distance += g.edgeCost(path[j].getId(), path[j+1].getId());

			if(distance < bestDistGasStation)
			{
				bestDistGasStation = distance;
				bestPathGasToLoc = path;
				bestGasStation = gasStations[k];
			}
		}

		//best gas station to best park
		g.dijkstraShortestPath(bestGasStation);
		bestParktoGas = g.getPath(bestGasStation, bestPark);

		distance = 0;
		for (unsigned int l = 0; l < path.size()-1; l++)
			distance += g.edgeCost(path[l].getId(),path[l+1].getId());
		gasToPark = distance;

	}

	else{
		//location to the park
		g.dijkstraShortestPath(g.getVertexSet().at(location)->getInfo());
		bestParktoLoc = g.getPath(g.getVertexSet().at(location)->getInfo(), bestPark);
		for (unsigned int l = 0; l < bestParktoLoc.size()-1; l++)
			distance += g.edgeCost(bestParktoLoc[l].getId(),bestParktoLoc[l+1].getId());
		bestDistLocation = distance;
	}

	if (gas == 1){
		//between gas station and location
		cout << "The closest gas station to your location is " << bestDistGasStation << " meters away." << endl;
		cout << "We estimate it will cost you around " << bestGasStation.getCost() << " � to refill the tank\n";
		cout << "To get there, you'll have to follow this path: " << endl;
		reverse(bestPathGasToLoc.begin(), bestPathGasToLoc.end());
		for (unsigned int l = 0; l < bestPathGasToLoc.size(); l++)
		{
			ids.push_back(bestPathGasToLoc.at(l));
			if (l == bestPathGasToLoc.size()-1)
				cout << bestPathGasToLoc[l].getLabel() << "." << endl;
			else
				cout << bestPathGasToLoc[l].getLabel() << ", ";
		}

		cout << "The closest park to your destination is a " << bestPark.getLabel() << " and it is " << gasToPark << " meters away.\n";
		cout << "The price will be " << bestPark.getCost() << "�/hour\n";
		cout << "After filling up your tank, you should follow this route: " << endl;
		for (unsigned int l = 0; l < bestParktoGas.size(); l++)
		{
			ids.push_back(bestParktoGas.at(l));
			if (l == bestParktoGas.size()-1)
				cout << bestParktoGas[l].getLabel() << "." << endl;
			else
				cout << bestParktoGas[l].getLabel() << ", ";
		}

		cout << "To reach your destination, you'll have to follow this path, by foot: " << endl;
		for (unsigned int l = 0; l < bestParkToDest.size(); l++)
		{
			ids.push_back(bestParkToDest.at(l));
			if (l == bestParkToDest.size()-1)
				cout << bestParkToDest[l].getLabel() << ". " << endl;
			else
				cout << bestParkToDest[l].getLabel() << ", ";
		}
	}
	else{
		//showing distance between location and park
		cout << "The closest park to your destination is " << bestPark.getLabel() << " and it is " << bestDistLocation << " meters away." << endl;
		cout << "The price will be " << bestPark.getCost() << "�/hour\n";
		cout << "To get there, you'll have to follow this path: " << endl;
		for (unsigned int l = 0; l < bestParktoLoc.size(); l++)
		{
			ids.push_back(bestParktoLoc.at(l));
			if (l == bestParktoLoc.size()-1)
				cout << bestParktoLoc[l].getLabel() << "." << endl;
			else
				cout << bestParktoLoc[l].getLabel() << ", ";
		}


		//showing distance between park and destination
		cout << "To reach your destination, you'll have to follow this path, by foot: " << endl;
		for (unsigned int l = 0; l < bestParkToDest.size(); l++)
		{
			ids.push_back(bestParkToDest[l]);
			if (l == bestParkToDest.size()-1)
				cout << bestParkToDest[l].getLabel() << ". " << endl;
			else
				cout << bestParkToDest[l].getLabel() << ", ";
		}
	}


	cout << "The map will be updated with the path..." << endl;
	Sleep(3000);
	if (gas == 1)
		printPathWithGas(bestPathGasToLoc, bestParktoGas, bestParkToDest);
	else
		printPathNoGas(bestParktoLoc,bestParkToDest);

	getchar();
}

//shows options
template<class T>
void showOptions(Graph<T> &g){
	for(unsigned int i =0; i < g.getVertexSet().size(); i++)
		if(g.getVertexSet()[i]->getInfo().getLabel() != "garage" && g.getVertexSet()[i]->getInfo().getLabel() != "crossroad" && g.getVertexSet()[i]->getInfo().getLabel() != "parking lot" && g.getVertexSet()[i]->getInfo().getLabel() != "gas station")
			cout << g.getVertexSet()[i]->getInfo().getId() << " " <<  g.getVertexSet()[i]->getInfo().getLabel() << " x: "<< g.getVertexSet()[i]->getInfo().getX() << " y: "<<  g.getVertexSet()[i]->getInfo().getY()<< "\n";
}

//menu
template<class T>
void menuGraphs(Graph<T> &g, vector<T> parks, vector<T> gasStations){

	int location, destination, choice, gas;
	cout << "Good day \n" << "Where are you?(choose the node id)\n";
	printGraphPath();
	showOptions(g);
	cin >> location;
	cout << "Where are you headed?(choose the node id)\n";
	showOptions(g);
	cin >> destination;
	if (location == destination)
	{
		cout << "Please try again\n";
		menuGraphs(g,parks,gasStations);
	}
	cout << "Do you wish to refill?\n1-Yes \n2-No \n";
	cin >> gas;
	cout << "Do you want the shortest route(0) or the cheapest route(1)?\n";
	cout << "0->Shortest\n"; cout << "1->Cheapest\n";
	cin >> choice;
	if (choice == 0)
		shortestPath(gas, location, destination, g, parks, gasStations);
	else
		cheapestPath(gas, location, destination, g, parks, gasStations);


	cout << endl << "Thanks for using our application!\n" << endl;

}
