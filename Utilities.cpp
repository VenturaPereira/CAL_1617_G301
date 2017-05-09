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



