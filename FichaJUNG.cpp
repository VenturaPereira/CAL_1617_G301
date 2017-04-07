#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "Menu.h"
#include "Utilities.h"

using namespace std;

void printGraph();

template <class T>
void initialise(Graph<T> &g, vector<T> &parks);

class VertexInfo;

template <class T>
void initialise(Graph<T> &g, vector<T> &parks){

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
		v.setId(stoi(id));
		v.setX(stoi(x));
		v.setY(stoi(y));
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
	getline(inFile, idD, ';');


	//each line in the format: idEdge;idSource;idDest
	while(inFile)
	{
		int idE = stoi(idEdge);
		int idSour = stoi(idS);
		int idDest = stoi(idD);

		double weight = sqrt( ((g.getVertexSet()[idSour]->getInfo().getX() - g.getVertexSet()[idDest]->getInfo().getX())^2) + ((g.getVertexSet()[idSour]->getInfo().getY() - g.getVertexSet()[idDest]->getInfo().getY())^2));

		g.addEdge(g.getVertexSet()[idSour]->getInfo(),g.getVertexSet()[idDest]->getInfo(), weight);
		g.addEdge(g.getVertexSet()[idDest]->getInfo(),g.getVertexSet()[idSour]->getInfo(), weight);

		getline(inFile, idEdge, ';');
		getline(inFile, idS, ';');
		getline(inFile, idD, ';');

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
		idN = stoi(idNo);
		x = stoi(X);
		y = stoi(Y);

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
	printGraph();
	menu(g, parks);
	//brute force do caminho mais r�pido e depois comparar tempos
	getchar();
	return 0;
}
