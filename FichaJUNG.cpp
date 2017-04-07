#include <cstdio>
#include <string>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "Menu.h"
#include "Utilities.h"

using namespace std;

void printGraph();

void initialise(Graph<VertexInfo> &g, vector<VertexInfo> &parks);

class VertexInfo;

void initialise(Graph<VertexInfo> &g, vector<VertexInfo> &parks){

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
	getline(inFile, idD, ' ');

	vector<VertexInfo> vertices = g.dfs();

	//each line in the format: idEdge;idSource;idDest
	while(inFile)
	{
		int idE = atoi(idEdge.c_str());
		int idSour = atoi(idS.c_str());
		int idDest = atoi(idD.c_str());
		VertexInfo v1, v2;
		bool found1,found2;

		for (unsigned int i = 0; i < vertices.size(); i++){
			if (vertices[i].getId() == idSour)
			{
				v1.setId(vertices[i].getId());
				v1.setX(vertices[i].getX());
				v1.setY(vertices[i].getY());
				found1 = true;
			}
			else if (vertices[i].getId() == idDest)
			{
				v2.setId(vertices[i].getId());
				v2.setX(vertices[i].getX());
				v2.setY(vertices[i].getY());
				found2 = true;
			}
			if (found1 && found2)
				g.addEdge(v1, v2, sqrt((v2.getX()^2 - v1.getX()^2) + (v2.getY()^2 - v1.getY()^2)));
		}

		getline(inFile, idEdge, ';');
		getline(inFile, idS, ';');
		getline(inFile, idD, ' ');

	}

	inFile.close();
}


void printGraph()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	ifstream inFile;
	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile) {
		cerr << "Unable to open file nos.txt";
		exit(1);   // call system to stop
	}

	string line, label, idNo, X, Y;
	int idN, x,y;


	getline(inFile, idNo, ';');
	getline(inFile, X, ';');
	getline(inFile, Y, ';');
	getline(inFile, label, ';');

	while(inFile)
	{
		VertexInfo v;
		idN = atoi(idNo.c_str());
		x = atoi(X.c_str());
		y = atoi(Y.c_str());

		gv->addNode(idN,x,y);
		gv->setVertexLabel(idN, label);

		getline(inFile, idNo, ';');
		getline(inFile, X, ';');
		getline(inFile, Y, ';');
		getline(inFile, label, ';');

	}

	inFile.close();


	//Ler o ficheiro arestas.txt
	inFile.open("arestas.txt");

	if (!inFile) {
		cerr << "Unable to open file arestas.txt";
		exit(1);   // call system to stop
	}

	int idAresta=0;
	int idNoOrigem=0;
	int idNoDestino=0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::UNDIRECTED);

	}

	inFile.close();

	gv->rearrange();
}

int main() {


	Graph<VertexInfo> g;

	vector<VertexInfo> parks;
	initialise(g, parks);

	g.dijkstraShortestPath(parks.at(0));
	//printGraph();
	//menu(g, parks);


	getchar();
	return 0;
}
