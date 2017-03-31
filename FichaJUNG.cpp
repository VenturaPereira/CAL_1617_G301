#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"
using namespace std;

struct VertexInfo{

	int idNo, X,Y;
	string label;
};


void printGraph();

void initialise();

void initialise(){

	Graph<VertexInfo>* g;

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile) {
		cerr << "Unable to open file nos.txt";
		exit(1);   // call system to stop
	}

	string line;

	//each node will be in this format: id;x;y;label
	while(getline(inFile, line))
	{
		VertexInfo v;
		stringstream linestream(line);
		string data, label;
		linestream >> v.idNo;

		cout << v.idNo << endl;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> v.X;

		cout << v.X << endl;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> v.Y;

		cout << v.Y << endl;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> v.label;
		g->addVertex(v);
	}

	inFile.close();

	//Ler o ficheiro arestas.txt

	inFile.open("arestas.txt");

	if (!inFile) {
		cerr << "Unable to open file arestas.txt";
		exit(1);   // call system to stop
	}

	vector<VertexInfo> vertices = g->dfs();
	//each line in the format: idEdge;idSource;idDest;weight
	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;
		int idAresta=0;
		int idNoOrigem=0;
		int idNoDestino=0;
		double weight = 0;

		linestream >> idAresta;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> weight;
		for (int i = 0; i < vertices.size(); i++)
			if (vertices[i].idNo == idNoOrigem)
				for (int j = 0; j < vertices.size(); j++)
					if (j != i && vertices[j].idNo == idNoDestino)
						g->addEdge(vertices[i], vertices[j], weight);
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

	string line;

	int idNo=0;
	int X=0;
	int Y=0;
	string label;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> idNo;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> X;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> Y;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> label;
		gv->addNode(idNo,X,Y);
		gv->setVertexLabel(idNo, label);

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

	printGraph();
	getchar();
	return 0;
}
