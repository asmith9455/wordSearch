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

public:
	vector<Node*> next_nodes;

	Node(char c, size_t depth);

	char get_char();
	size_t get_terminating_strings(size_t index, size_t index_limit, vector<string>& add_to);

	void add_next_node(Node* n);
	void add_terminating_string(string s);

	Node* check_for_next_node_with(char c);

	~Node();
};

