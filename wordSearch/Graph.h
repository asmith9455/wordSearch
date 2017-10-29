#pragma once
#include <string>
#include <list>
#include <stack>
#include "Node.h"


class Graph
{
	Node start_node = Node(' ', 0);

public:
	list<Node> nodes;

public:
	Graph();

	void addString(string s);

	//the search preserves the order in which the strings were added
	vector<string> search(string search_string, size_t num_results);

	~Graph();
};

