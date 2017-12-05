#pragma once
#include <vector>

using namespace std;

//could template this so that things other than strings can be searched
class Node
{
	char _c;
	size_t _depth;

	//each node contains references to a number of further nodes
	

	//the sorted union of terminating strings at all nodes is 
	//equivalent to the original sorted list
	vector<string> _terminating_strings;

	vector<Node*> next_nodes;
	vector<vector<string>> path_strings;	//each next node has some associate path_strings
	

public:

	Node(char c, size_t depth);

	char get_char();
	size_t get_terminating_strings(size_t index, size_t index_limit, vector<string>& add_to);

	void add_next_node(Node* n, string path_string);
	void add_terminating_string(string s);
	vector<Node*> get_next_nodes(string path_string);
	Node* get_next_node_with(char c, string path_string);

	size_t depth() {
		return _depth;
	}

};

