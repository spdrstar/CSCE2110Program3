/*
* Author: Zachary Eisenhauer
* Date: 12/2/2016
* Assignment: Program 3
*
* In Main.cpp
* 	Functions to read in graph.txt, commands.txt and print a created graph of them in list form and matrix form
*  
* In Main.h
*	The function prototypes in this file, the class definition for a node, and the libaries used
*/

// Include Statements
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <sstream>
#include <vector>
using std::vector;

#include <string>
using std::string;

#include <stdlib.h>     /* exit, EXIT_FAILURE */

// Classes
class node{
public:	
	char name;
	vector<char> connectedNodes;
};

// Function Prototypes
std::vector<node> inputGraph();
void commands(vector<node> &);
void printList(vector<node>);
void printMatrix(vector<node> nodes);