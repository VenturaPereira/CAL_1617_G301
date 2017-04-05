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

void initialise(Graph<VertexInfo> &g);

void initialise(Graph<VertexInfo> &g){

	//Graph<VertexInfo> g;

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
		v.idNo = stoi(id);
		v.X = stoi(x);
		v.Y = stoi(y);
		v.label = label;

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
		int idE = stoi(idEdge);
		int idSour = stoi(idS);
		int idDest = stoi(idD);
		VertexInfo v1, v2;
		bool found1,found2;

		for (unsigned int i = 0; i < vertices.size(); i++){
			if (vertices[i].idNo == idSour)
			{
				v1.X = vertices[i].X;
				v1.Y = vertices[i].Y;
				v1.idNo = vertices[i].idNo;
				found1 = true;
			}
			else if (vertices[i].idNo == idDest)
			{
				v2.X = vertices[i].X;
				v2.Y = vertices[i].Y;
				v2.idNo = vertices[i].idNo;
				found2 = true;
			}
			if (found1 && found2)
				g.addEdge(v1,v2, sqrt( ((v1.X - v2.X)^2) + ((v1.Y - v2.Y)^2)));
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
void showOptions(Graph<VertexInfo> &g){
	int a= 0;
	for(unsigned int i =0; i < g.getVertexSet().size(); i++)
		if(g.getVertexSet()[i]->getInfo().label != "garage" && g.getVertexSet()[i]->getInfo().label != "crossroad" && g.getVertexSet()[i]->getInfo().label != "parking lot")
			cout << a++ << " " <<  g.getVertexSet()[i]->getInfo().label << " x: "<< g.getVertexSet()[i]->getInfo().X << " y: "<<  g.getVertexSet()[i]->getInfo().Y<< "\n";
}
int main() {
	Graph<VertexInfo> g;
	int location, destination, gas;
	initialise(g);
	printGraph();
	cout << "Good day \n" << "Where are you?\n";
	showOptions(g);
	cin >> location;
	cout << "Where are you headed? \n";
	showOptions(g);
	cin >> destination;
	cout << "Do you wish to refill?\n1-Yes \n2-No \n";
	cin >> gas;
	getchar();
	return 0;
}
