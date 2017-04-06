/*
 * Menu.cpp
 *
 *  Created on: 6 Apr 2017
 *      Author: vitor
 */

#include <iostream>
using namespace std;

template<class T>
void showPath(int gas,int location,int destination, Graph<T> &g){
	//primeiro até estacionamento
	///g.dijkstraShortestPath();

	//depois até ao destino

}

template<class T>
void showOptions(Graph<T> &g){
	for(unsigned int i =0; i < g.getVertexSet().size(); i++)
		if(g.getVertexSet()[i]->getInfo().label != "garage" && g.getVertexSet()[i]->getInfo().label != "crossroad" && g.getVertexSet()[i]->getInfo().label != "parking lot")
			cout << i << " " <<  g.getVertexSet()[i]->getInfo().label << " x: "<< g.getVertexSet()[i]->getInfo().X << " y: "<<  g.getVertexSet()[i]->getInfo().Y<< "\n";
}

template<class T>
void menu(Graph<T> &g){
	int location, destination, gas;
	cout << "Good day \n" << "Where are you?\n";
	showOptions(g);
	cin >> location;
	cout << "Where are you headed? \n";
	showOptions(g);
	cin >> destination;
	cout << "Do you wish to refill?\n1-Yes \n2-No \n";
	cin >> gas;
	showPath(gas, location, destination, g);
}


