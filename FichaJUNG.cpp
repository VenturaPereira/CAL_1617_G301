#include <cstdio>
#include <string>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "Menu.h"
#include "Utilities.h"
#include <cmath>

using namespace std;


template <class T>
void initialise(Graph<T> &g, vector<T> &parks, vector<T> &gasStations);

class VertexInfo;

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

		if (label == "garage" || label == "parking lot")
			parks.push_back(v);

		if(label == "gas station")
			gasStations.push_back(v);


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

	string idEdge,idS,idD;


	getline(inFile, idEdge, ';');
	getline(inFile, idS, ';');
	getline(inFile, idD, ';');


	//each line in the format: idEdge;idSource;idDest
	while(inFile)
	{

		int idE = atoi(idEdge.c_str());
		int idSour = atoi(idS.c_str());
		int idDest = atoi(idD.c_str());


		int distanceX = g.getVertexSet()[idSour]->getInfo().getX() - g.getVertexSet()[idDest]->getInfo().getX();
		int distanceY = g.getVertexSet()[idSour]->getInfo().getY() - g.getVertexSet()[idDest]->getInfo().getY();

		double weight = sqrt( pow(distanceX, 2) + pow (distanceY, 2));


		g.addEdge(g.getVertexSet()[idSour]->getInfo(),g.getVertexSet()[idDest]->getInfo(), weight);
		g.addEdge(g.getVertexSet()[idDest]->getInfo(),g.getVertexSet()[idSour]->getInfo(), weight);

		getline(inFile, idEdge, ';');
		getline(inFile, idS, ';');
		getline(inFile, idD, ';');

	}

	inFile.close();

}

int main() {
	Graph<VertexInfo> g;
	vector<VertexInfo> parks, gasStations;
	initialise(g, parks, gasStations);
	menu(g, parks, gasStations);
	getchar();
	return 0;

}
