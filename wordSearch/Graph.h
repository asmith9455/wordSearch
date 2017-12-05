#pragma once
#include <string>
#include <list>
#include <stack>
#include <memory>
#include "Node.h"
#include <algorithm>


class Graph
{


	// pointers to list remain valid for the lifetime of the list 
	// (adding/removing elements from the list doesn't invalidate 
	// the positions of the list's elements on the heap)
	// must use a shared pointer so that copying the Graph doesn't invalidate the references to nodes
	//shared_ptr<list<Node>> nodes = make_shared<list<Node>>();
	//list<Node> nodes;

	using nodes_t =list<list<Node>>;

	shared_ptr<nodes_t> nodes = make_shared<nodes_t>();	//hold the information in a multidimensional array wrapped in a shared pointer

	Node* add_node(Node n, size_t depth);
	Node* get_node(size_t depth, char c);
	Node* get_start_node() {
		return get_node(0, ' ');
	}
	Node* m_last_added_node = nullptr;
	size_t m_max_depth = 0;

	//with the current setup - need to disable copy assignment

public:

	Graph() {
		nodes->push_back({ Node(' ', 0) });
	}

	void addString(string s);

	size_t num_nodes() { return nodes->size(); }

	size_t max_depth() {
		return m_max_depth;
	}

	/*vector<size_t> node_counts_by_depth() {
		vector<size_t> results = { 1 };
		for (size_t i = 1; i <= m_max_depth; ++i) {
			size_t count = std::count_if(nodes->begin(), nodes->end(), [&i](Node n)->bool {return n.depth() == i; });
			results.push_back(count);
		}
		return results;
	}*/

	//the search preserves the order in which the strings were added
	vector<string> search(string search_string, size_t num_results);

};

