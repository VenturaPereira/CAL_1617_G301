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

void showPath(int gas,int location,int destination, Graph<T> &g, vector<T> &parks, vector<T> &gasStations){

		double distance = 0, bestDistParking, bestDistGasStation , bestDistLocation, gasToPark, parkToDest;
		vector<T> path;
		vector<T> bestPathParking;
		vector<T> bestPathGasStation;
		vector<T> pathParkToDest;
		T bestPark;
		T bestGasStation;


		//closest gas station
		if(gas == 1){
			g.dijkstraShortestPath(g.getVertexSet().at(location)->getInfo());
			path = g.getPath( gasStations[0], g.getVertexSet().at(location)->getInfo());

			for(unsigned int k = 0; k < path.size(); k++){
				distance += g.edgeCost(path[k].getId(),path[k+1].getId());
			}

			bestDistGasStation = distance;
			bestPathGasStation = path;
			bestGasStation = gasStations[0];

			for(unsigned int k = 1; k < gasStations.size(); k++){
				distance = 0;
				g.dijkstraShortestPath(g.getVertexSet().at(gasStations[k].getId())->getInfo());
				path = g.getPath(gasStations[k], g.getVertexSet().at(location)->getInfo());
				for(unsigned int j = 0; j < path.size()-1; j++){
					distance += g.edgeCost(path[j].getId(), path[j+1].getId());
				}
				if(distance < bestDistGasStation)
				{
					bestDistGasStation = distance;
					bestPathGasStation = path;
					bestGasStation = gasStations[k];
				}
			}
			//

			//closest park
			g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
			path = g.getPath(g.getVertexSet().at(destination)->getInfo(), parks[0]);


			for (unsigned int z = 0; z < path.size()-1; z++)
				distance += g.edgeCost(path[z].getId(),path[z+1].getId());

			bestDistParking = distance;
			bestPathParking = path;
			bestPark = parks[0];


			for (unsigned int p = 1; p < parks.size(); p++){
				distance = 0;
				g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
				path = g.getPath(g.getVertexSet().at(destination)->getInfo(), parks[p]); //path between destination and park p
				for (unsigned int z = 0; z < path.size()-1; z++)
					distance += g.edgeCost(path[z].getId(),path[z+1].getId());
				if (distance < bestDistParking){
					bestDistParking = distance;
					bestPathParking = path;
					bestPark = parks[p];
				}
			}
			//

			//best gas station to best park
			g.dijkstraShortestPath(bestGasStation);
			path = g.getPath(bestGasStation, bestPark);
			for (unsigned int l = 0; l < path.size()-1; l++){
				distance += g.edgeCost(path[l].getId(),path[l+1].getId());
			}

			gasToPark = distance;
			//

			//output
			cout << "The closest gas station to your location is " << bestGasStation.getLabel() <<  " and it is " << bestDistGasStation << " meters away." << endl;
			cout << "To get there, you'll have to follow this path: " << endl;
			for (unsigned int l = 0; l < bestPathGasStation.size(); l++)
			{
				if (l == bestPathGasStation.size()-1)
					cout << bestPathGasStation[l].getLabel() << "." << endl;
				else
					cout << bestPathGasStation[l].getLabel() << ", ";
			}
			cout << "The closest park to your destination is " << bestPark.getLabel() << " and it is " << gasToPark << " meters away." << endl;
			cout << "After filling up your tank, you should follow this route: " << endl;
			for (unsigned int l = 0; l < path.size(); l++)
			{
				if (l == path.size()-1)
					cout << path[l].getLabel() << "." << endl;
				else
					cout << path[l].getLabel() << ", ";
			}
			cout << "To reach your destination, you'll have to follow this path, by foot: " << endl;
			for (unsigned int l = 0; l < bestPathParking.size(); l++)
			{
				if (l == bestPathParking.size()-1)
					cout << bestPathParking[l].getLabel() << ". " << endl;
				else
					cout << bestPathParking[l].getLabel() << ", ";
			}
			//
		}

		else{
			g.dijkstraShortestPath(g.getVertexSet().at(parks[0].getId())->getInfo());
					path = g.getPath(parks[0],g.getVertexSet().at(destination)->getInfo());

					//for 1st park
					for (unsigned int z = 0; z < path.size()-1; z++)
						distance += g.edgeCost(path[z].getId(),path[z+1].getId());

					bestDistParking = distance;
					bestPathParking = path;
					bestPark = parks[0];

					//closest park
					for (unsigned int p = 1; p < parks.size(); p++){
						distance = 0;
						g.dijkstraShortestPath(g.getVertexSet().at(parks[p].getId())->getInfo());
						path = g.getPath(parks[p], g.getVertexSet().at(destination)->getInfo()); //path between destination and park p
						for (unsigned int z = 0; z < path.size()-1; z++)
							distance += g.edgeCost(path[z].getId(),path[z+1].getId());
						if (distance < bestDistParking){
							bestDistParking = distance;
							bestPathParking = path;
							bestPark = parks[p];
						}
					}



					//location to the park
					g.dijkstraShortestPath(g.getVertexSet().at(location)->getInfo());
					path = g.getPath(g.getVertexSet().at(location)->getInfo(), bestPark);
					for (unsigned int l = 0; l < path.size()-1; l++)
						distance += g.edgeCost(path[l].getId(),path[l+1].getId());
						bestDistLocation = distance;


					cout << "The closest park to your destination is " << bestPark.getLabel() << " and it is " << bestDistLocation << " meters away." << endl;
					cout << "To get there, you'll have to follow this path: " << endl;
					for (unsigned int l = 0; l < path.size(); l++)
					{
						if (l == path.size()-1)
							cout << path[l].getLabel() << "." << endl;
						else
							cout << path[l].getLabel() << ", ";
					}
					cout << "Afterwards, you'll have to walk " << bestDistParking << " meters." << endl;
					cout << "To reach your destination, you'll have to follow this path, by foot: " << endl;
					for (unsigned int l = 0; l < bestPathParking.size(); l++)
					{
						if (l == bestPathParking.size()-1)
							cout << bestPathParking[l].getLabel() << ". " << endl;
						else
							cout << bestPathParking[l].getLabel() << ", ";
					}
		}



		getchar();
}

template<class T>
void showOptions(Graph<T> &g){
	for(unsigned int i =0; i < g.getVertexSet().size(); i++)
		if(g.getVertexSet()[i]->getInfo().getLabel() != "garage" && g.getVertexSet()[i]->getInfo().getLabel() != "crossroad" && g.getVertexSet()[i]->getInfo().getLabel() != "parking lot" && g.getVertexSet()[i]->getInfo().getLabel() != "gas station")
			cout << g.getVertexSet()[i]->getInfo().getId() << " " <<  g.getVertexSet()[i]->getInfo().getLabel() << " x: "<< g.getVertexSet()[i]->getInfo().getX() << " y: "<<  g.getVertexSet()[i]->getInfo().getY()<< "\n";
}

template<class T>
void menu(Graph<T> &g, vector<T> parks, vector<T> gasStations){
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
			showPath(gas, location, destination, g, parks, gasStations);
		}
}

