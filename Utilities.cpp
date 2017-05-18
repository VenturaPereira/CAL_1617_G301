/*
 * Utilities.cpp
 *
 *  Created on: 6 Apr 2017
 *      Author: vitor
 */

#include "Utilities.h"

int VertexInfo::getId() const{
	return this->idNo;
}
int VertexInfo::getX() const{
	return this->X;
}
int VertexInfo::getY() const{
	return this->Y;
}
string VertexInfo::getLabel() const{
	return this->label;
}
float VertexInfo::getCost() const{
	return this->cost;
}
void VertexInfo::setId(int id)
{
	this->idNo = id;
}
void VertexInfo::setX(int x)
{
	this->X = x;
}
void VertexInfo::setY(int y)
{
	this->Y = y;
}
void VertexInfo::setLabel(string label)
{
	this->label = label;
}
void VertexInfo::setCost(float cost)
{
	this->cost = cost;
}

// Returns the distance between two strings. Space complexity: O(|P|.|T|).

int getEditDistanceOPT(string needle, string haystack) {
	// initialization
	vector<vector<int> > D(haystack.length() + 1,
			vector<int>(needle.length() + 1));

	for (unsigned int i = 0; i <= needle.length(); i++)
		D[0][i] = i;
	for (unsigned int i = 0; i <= haystack.length(); i++)
		D[i][0] = i;

	// algorithm
	for (unsigned int i = 1; i <= haystack.length(); i++) {
		for (unsigned int j = 1; j <= needle.length(); j++) {
			if (haystack[i - 1] == needle[j - 1])
				D[i][j] = D[i - 1][j - 1];
			else
				D[i][j] = 1
						+ min(min(D[i - 1][j - 1], D[i - 1][j]), D[i][j - 1]);
		}
	}

	// return distance between strings
	return D[haystack.length()][needle.length()];
}

// Returns the distance between two strings. Space complexity: O(|T|).

int editDistance(string pattern, string text)
{
	int n=text.length();
	vector<int> d(n+1);
	int old,neww;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) neww = old;
			else {
				neww = min(old,d[j]);
				neww = min(neww,d[j-1]);
				neww = neww +1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

void pre_kmp(string pattern, vector<int> & prefix)
{
	int m=pattern.length();
	prefix[0]=-1;
	int k=-1;
	for (int q=1; q<m; q++) {
		while (k>-1 && pattern[k+1]!=pattern[q])
			k = prefix[k];
		if (pattern[k+1]==pattern[q]) k=k+1;
		prefix[q]=k;
	}
}

int kmp(string text, string pattern)
{
	int num=0;
	int m=pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
		//	std::cout <<"pattern occurs with shift" << i-m+1 << std::endl;
			num++;
			q=prefix[q];
		}
	}
	return num;
}
//prints the graph
void printGraphPath(){

	gv->createWindow(1250, 1250);

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
	string nomeAresta;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		getline(linestream,nomeAresta);
		nomeAresta = nomeAresta.substr(1, nomeAresta.size()-2);
		gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::UNDIRECTED);
		gv->setEdgeLabel(idAresta, nomeAresta);
	}

	inFile.close();

	gv->rearrange();
}
