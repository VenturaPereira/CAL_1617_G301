#include <cstdio>
#include <string>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "Utilities.h"
#include <cmath>
#include "MenuGraphs.h"
#include "MenuStrings.h"

using namespace std;


template <class T>
void initialise(Graph<T> &g, vector<T> &parks, vector<T> &gasStations);

class VertexInfo;

//initialises the graph
template <class T>
void initialise(Graph<T> &g, vector<T> &parks, vector<T> &gasStations){

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile) {
		cerr << "Unable to open file nos.txt";
		exit(1);   // call system to stop
	}

	string line, label,x,y,id;

	getline(inFile, id, ';');
	getline(inFile, x, ';');
	getline(inFile, y, ';');
	getline(inFile, label, ';');

	//each node will be in this format: id;x;y;label
	while(inFile)
	{
		VertexInfo v;

		v.setId(atoi(id.c_str()));
		v.setX(atoi(x.c_str()));
		v.setY(atoi(y.c_str()));
		v.setLabel(label);

		if (label == "garage"){
			v.setCost(3);
			parks.push_back(v);
		}
		else if ( label == "parking lot"){
			v.setCost(2);
			parks.push_back(v);
		}

		else if(label == "gas station"){
			v.setCost(1.50);
			gasStations.push_back(v);
		}
		else
			v.setCost(0); //anything else has 0 cost

		g.addVertex(v);

		getline(inFile, id, ';');
		getline(inFile, x, ';');
		getline(inFile, y, ';');
		getline(inFile, label, ';');
	}
	inFile.close();

	//Ler o ficheiro arestas.txt

	inFile.open("arestas.txt");

	if (!inFile) {
		cerr << "Unable to open file arestas.txt";
		exit(1);   // call system to stop
	}

	string idEdge,idS,idD, edgeName;


	getline(inFile, idEdge, ';');
	getline(inFile, idS, ';');
	getline(inFile, idD, ';');
	getline(inFile, edgeName, ';');

	//each line in the format: idEdge;idSource;idDest;streetName
	while(inFile)
	{
		int idE = atoi(idEdge.c_str());
		int idSour = atoi(idS.c_str());
		int idDest = atoi(idD.c_str());

		int distanceX = g.getVertexSet()[idSour]->getInfo().getX() - g.getVertexSet()[idDest]->getInfo().getX();
		int distanceY = g.getVertexSet()[idSour]->getInfo().getY() - g.getVertexSet()[idDest]->getInfo().getY();

		double weight = sqrt( pow(distanceX, 2) + pow (distanceY, 2));

		g.addEdge(g.getVertexSet()[idSour]->getInfo(),g.getVertexSet()[idDest]->getInfo(), weight, edgeName);
		g.addEdge(g.getVertexSet()[idDest]->getInfo(),g.getVertexSet()[idSour]->getInfo(), weight, edgeName);

		getline(inFile, idEdge, ';');
		getline(inFile, idS, ';');
		getline(inFile, idD, ';');
		getline(inFile, edgeName, ';');

	}

	inFile.close();

}


int main() {
	Graph<VertexInfo> g;
	vector<VertexInfo> parks, gasStations;
	int choice;
	initialise(g, parks, gasStations);

	cout << "Do you want to work with graphs(0) or strings(1)?\n";
	cout << "0->Graphs\n"; cout << "1->Strings\n";
	cin >> choice;
	if (choice == 0)
		menuGraphs(g, parks, gasStations);
	else
		menuStrings(g, parks);

	getchar();
	return 0;
}


