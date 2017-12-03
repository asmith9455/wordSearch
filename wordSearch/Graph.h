#pragma once
#include <string>
#include <list>
#include <stack>
#include "Node.h"


class Graph
{
	Node start_node = Node(' ', 0);


	// pointers to list remain valid for the lifetime of the list 
	// (adding/removing elements from the list doesn't invalidate 
	// the positions of the list's elements on the heap)
	// 
	// should probably create a nodes container and expose the two methods - add_node and last_added_node (back?)
	list<Node> nodes;

	void add_node(Node n);
	Node* last_added_node();

	//with the current setup - need to disable copy assignment

public:

	void addString(string s);

	//the search preserves the order in which the strings were added
	vector<string> search(string search_string, size_t num_results);

};

