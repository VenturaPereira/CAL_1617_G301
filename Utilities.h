/*
 * Utilities.h
 *
 *  Created on: 6 Apr 2017
 *      Author: vitor
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <vector>
#include "graphviewer.h"
#include <fstream>
#include <sstream>
using namespace std;

extern GraphViewer *gv;

class VertexInfo{

	int idNo, X,Y;
	string label;
	float cost;
public:
	int getId() const;
	int getX() const;
	int getY() const;
	string getLabel() const;
	float getCost() const;
	void setId(int id);
	void setX(int x);
	void setY(int y);
	void setLabel(string label);
	void setCost(float cost);

};
int getEditDistanceOPT(string needle, string haystack);
int editDistance(string pattern, string text);


void pre_kmp(string pattern, vector<int> & prefix);

int kmp(string text, string pattern);

void printGraphPath();

#endif /* UTILITIES_H_ */
