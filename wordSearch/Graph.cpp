#include "Graph.h"

//add a new node and return a pointer to it
Node* Graph::add_node(char c, size_t depth){

	Node n(c, depth);

	if (nodes->size() <= depth)
		nodes->push_back({});	//push back a new vector of nodes

	auto depth_it = nodes->begin();
	std::advance(depth_it, depth);

	depth_it->push_back(n);
	m_last_added_node = &(depth_it->back());	//return a reference to the last added node

	return m_last_added_node;
}

Node* Graph::get_node(size_t depth, char c) {
	
	if (nodes->size() <= depth)
		return nullptr;

	auto depth_it = nodes->begin();
	std::advance(depth_it, depth);

	auto it = std::find_if(
		depth_it->begin(),
		depth_it->end(),
		[&c](Node n) -> bool {return n.get_char() == c; });

	if (it == depth_it->end())
		return nullptr;
	else
		return &(*it);	//return a pointer to the node we found.
}

void Graph::addString(string s)
{
	Node *n = get_start_node(), *next_node;
	string tmp;
	size_t depth = 1;
	unique_id_t id = num_added_nodes;

	for (char c : s) {
		//this is not the desired behaviour - the memory usage is much higher this way - need to be able to search all nodes at a given depth level
		next_node = get_node(depth, c);

		if (!next_node)	// if tmpNode is null (the next_node for 'c' doesn't exist), we need to add a node with this character.
			next_node = add_node(c, depth); //next_node points to the most recently added element.

		//add a connection to the next_node from the current node
		n->add_next_node_connection(next_node, id);

		//now next_node points to the next node @ depth that corresponds to the string s
		n = next_node;
		tmp += c;
		depth++;
	}

	m_max_depth = max(m_max_depth, depth - 1);

	n->add_terminating_id(id);

	++num_added_nodes;

}

vector<string> Graph::search(string search_string, size_t num_results_to_return)
{


	//part 1 - traverse the graph using the partial search

	vector<string> results;
	Node *n = get_start_node(), *next_node = nullptr;
	size_t result_counter = 0;

	bool first_char = true;
	string path_string_base;
	set<unique_id_t> path_ids;

	for (char c : search_string)
	{
		//go through the terminating strings and add them to the results vector
		if (first_char) {
			//on the first character, we search for the next node using only the character (path_ids are not important)
			auto pair = n->get_next_node_with(c);
			next_node = pair.first;
			path_ids = pair.second;
		}
		else {
			auto pair = n->get_next_node_with(c, path_ids);
			next_node = pair.first;
			path_ids = pair.second;	//path ids may be reduced in size by internal intersection operations
		}

		if (next_node)
			n = next_node;
		else
			break;

		path_string_base += c;
		first_char = false;
	}

	//part 2 - find all possible matches up to the number of requested results

	using node_tracker_t = tuple<Node*, set<unique_id_t>, string>;

	stack<node_tracker_t> nodes_to_check;

	nodes_to_check.push({ n, path_ids, path_string_base });


	n->get_terminating_strings(result_counter, num_results_to_return, results, path_ids, path_string_base);

	return results;
}
