/*
 * MenuStrings.h
 *
 *  Created on: 4 May 2017
 *      Author: vitor
 */

#ifndef MENUSTRINGS_H_
#define MENUSTRINGS_H_

#include <iostream>
#include "Graph.h"
#include "Utilities.h"
#include <algorithm>


void exact(string s);
void approximate(string s);


void menuStrings(){
	string street;
	cout << "What is the street you're searching for?\n";
	cin >> street;

	int choice;
	cout << "Do you want to search for the street using Exact Search or Approximate Search?\n";
	cout << "0->Exact Search\n"; cout << "1->Approximate Search\n";
	cin >> choice;
	if (choice == 0)
		exact(street);
	else
		approximate(street);
}

void exact(string s){

}

void approximate(string s){

}


#endif /* MENUSTRINGS_H_ */
