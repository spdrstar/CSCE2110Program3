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

#include "main.h"

int main()
{
	vector<node> nodes = inputGraph();
	
	printList(nodes);
	
	printMatrix(nodes);
	
	commands(nodes);
	
	printList(nodes);
	
	printMatrix(nodes);
	
	return 0;
}

/*
* Read in the nodes from  graph.txt and input them in a vector of nodes
*
* @return - all of the nodes from the graph.txt file in a vector of nodes
*/ 
std::vector<node> inputGraph()
{
	vector<node> nodes;
	
	// Opening the file
	std::ifstream graph;
	cout << "Opening file graph.txt..." << endl;
	graph.open("graph.txt");
	
	// Checking if the file is good
	if(!graph.good())
	{
		cout << "graph.txt did not read correctly. exiting program" << endl;
		exit(EXIT_FAILURE);
	}
	
	// Parsing the file for new nodes
	string line;
	while(std::getline(graph,line))
	{
		node entry;
		std::istringstream iss(line);
		
		char nodeName;
		iss >> nodeName;
		entry.name = nodeName;
		
		char connectedNode;
		char comma;
		while((iss >> comma >> connectedNode) && (comma == ','))
		{
			entry.connectedNodes.push_back(connectedNode);
		}
		
		nodes.push_back(entry);
	}
	
	return nodes;
}

/*
* Take in an existing graph of nodes and change it from the commands
*
* @param nodes - The existing graph of nodes to change
*/
void commands(vector<node> &nodes)
{
	// Opening the file
	std::ifstream commands;
	cout << "Opening file commands.txt..." << endl;
	cout << endl;
	commands.open("commands.txt");
	string line;
	
	// Checking if the file is good
	if(!commands.good())
	{
		cout << "commands.txt did not read correctly. exiting program" << endl;
		exit(EXIT_FAILURE);
	}
	
	// Parsing the file for new commands
	while(getline(commands,line))
	{
		// Take in the command
		std::istringstream iss(line);
		string temp;
		std::getline(iss, temp,',');
		string command = temp;
		cout << command;
		// Add Node
		if(command == "addnode")
		{
			// Node to be taken in
			char node1;
			char comma;
			iss >> node1;
			cout << ", " << node1;
			// Check for duplicates
			bool dup = false;
			for(int i=0; i<nodes.size(); i++)
			{
				if(node1 == nodes[i].name)
				{
					dup = true;
				}
			}
			
			// Add the node if it isn't a duplicate
			if(!dup)
			{
				node entry;
				entry.name = node1;
				nodes.push_back(entry);
			}
		}
		
		// Remove Node
		else if(command == "removenode")
		{
			// Node to be taken in
			char node1;
			//char comma;
			iss >> node1;
			cout << ", " << node1;
			
			// Check for existence
			bool exist = false;
			for(int i=0; i<nodes.size(); i++)
			{
				// If it exists, delete it
				if(node1 == nodes[i].name)
				{
					exist = true;
					nodes.erase(nodes.begin() + i);
				}
			}
			
			// If the node existed, delete edges that match it
			if(exist)
			{
				for(int i=0; i< nodes.size(); i++)
				{
					for(int j=0; j< nodes[i].connectedNodes.size(); j++)
					{
						if(nodes[i].connectedNodes[j] == node1)
							nodes[i].connectedNodes.erase(nodes[i].connectedNodes.begin() + j);
					}
				}
			}
		}
		
		// Add Edge
		else if(command == "addedge")
		{
			// Node to be taken in
			char node1;
			char node2;
			char comma;
			iss >> node1 >> comma >> node2;
			cout << ", " << node1 << ", " << node2;
			
			// Check for duplicates
			bool dup = false;
			for(int i=0; i<nodes.size(); i++)
			{
				if(node1 == nodes[i].name || node2 == nodes[i].name)
				{
					for(int j=0; j< nodes[i].connectedNodes.size();j++)
					{
						if(nodes[i].connectedNodes[j] == node2 || nodes[i].connectedNodes[j] == node1)
						{
							dup = true;
							
							// Kill the for loop
							j += nodes[i].connectedNodes.size();
						}
					}
					
					// Kill the for loop
					i += nodes.size();
				}
			}
			
			// Add the edge if it isn't a duplicate
			if(!dup)
			{
				for(int i=0; i< nodes.size(); i++)
				{
					if(node1 == nodes[i].name)
					{
						nodes[i].connectedNodes.push_back(node2);
					}
					if(node2 == nodes[i].name)
					{
						nodes[i].connectedNodes.push_back(node1);
					}
				}
			}
		}
		
		// Remove Edge
		else if(command == "removeedge")
		{
			// Node to be taken in
			char node1;
			char node2;
			char comma;
			iss >> node1 >> comma >> node2;
			cout << ", " << node1 << ", " << node2;
			
			// Check for duplicates
			bool exists = false;
			for(int i=0; i<nodes.size(); i++)
			{
				if(node1 == nodes[i].name || node2 == nodes[i].name)
				{
					for(int j=0; j< nodes[i].connectedNodes.size();j++)
					{
						if(nodes[i].connectedNodes[j] == node2 || nodes[i].connectedNodes[j] == node1)
						{
							exists = true;
							
							// Kill the for loop
							j += nodes[i].connectedNodes.size();
						}
					}
					
					// Kill the for loop
					i += nodes.size();
				}
			}
			
			// delete the edge if it exists
			if(exists)
			{
				for(int i=0; i< nodes.size(); i++)
				{
					if(node1 == nodes[i].name)
					{
						for(int j=0; j< nodes[i].connectedNodes.size();j++)
						{
							if(nodes[i].connectedNodes[j] == node2)
							{
								nodes[i].connectedNodes.erase(nodes[i].connectedNodes.begin() + j);
							}
						}
					}
					if(node2 == nodes[i].name)
					{
						for(int j=0; j< nodes[i].connectedNodes.size();j++)
						{
							if(nodes[i].connectedNodes[j] == node1)
							{
								nodes[i].connectedNodes.erase(nodes[i].connectedNodes.begin() + j);
							}
						}
					}
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

// Print the nodes as a list
void printList(vector<node> nodes)
{
	cout << "Printing Adjacency List:" << endl;
	cout << "Undirected graph contains " << nodes.size() << " nodes total." << endl;
	
	for(int i=0; i< nodes.size();i++)
	{
		cout << nodes[i].name << ": ";
		for(int j=0;j< nodes[i].connectedNodes.size();j++)
		{
			cout << nodes[i].connectedNodes[j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Print the nodes as a matrix
void printMatrix(vector<node> nodes)
{
	cout << "Printing Adjacency Matrix:" << endl;
	// First row
	cout << "  ";
	for(int i=0;i<nodes.size();i++)
		cout << nodes[i].name << " ";
	
	cout << endl;
	bool found = false;
	// Rest of the rows
	for(int i=0;i<nodes.size();i++)
	{
		// Node at the row
		cout << nodes[i].name << " ";
		
		for(int j=0;j<nodes.size();j++)
		{
			// Node isn't connected to itself
			if(i == j)
				cout << "0 ";
			else
			{
				for(int k=0;k<nodes[i].connectedNodes.size();k++)
				{
					//cout << nodes[j].name << nodes[i].connectedNodes[k] << endl;
					if(nodes[j].name == nodes[i].connectedNodes[k])
					{
						cout << "1 ";
						found = true;
						k += nodes[i].connectedNodes.size();
					}
					
				}
				if(!found)
				{
					cout << "0 ";
				}
				found = false;
			}
			
		}
		cout << endl;
	}
	
	cout << endl;
}