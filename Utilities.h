/*
 * Utilities.h
 *
 *  Created on: 6 Apr 2017
 *      Author: vitor
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
using namespace std;

class VertexInfo{

	int idNo, X,Y;
	string label;
public:
	int getId() const;
	int getX() const;
	int getY() const;
	string getLabel() const;
	void setId(int id);
	void setX(int x);
	void setY(int y);
	void setLabel(string label);
};


#endif /* UTILITIES_H_ */
