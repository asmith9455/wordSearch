#include "Graph.h"

Node* Graph::add_node(Node n, size_t depth){

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

	for (char c : s)
	{
		
		//this is not the desired behaviour - the memory usage is much higher this way - need to be able to search all nodes at a given depth level
		next_node = get_node(depth, c);

		if (!next_node){	// if tmpNode is null (the node for 'c' doesn't exist), we need to add a node with this character.
			next_node = add_node(Node(c, depth), depth); //next_node points to the most recently added element.
		}

		//we need to add this as a next node if the node doesn't have it in it's next nodes list
		auto ptr = n->get_next_node_with(c, tmp);
		if (!ptr)
			n->add_next_node(next_node, tmp);

		//now next_node points to the next node @ depth that corresponds to the string s
		n = next_node;
		tmp += c;
		depth++;
	}

	m_max_depth = max(m_max_depth, depth - 1);

	//now just need to add the string s as a terminating string at node n (corresponding to the last character)
	n->add_terminating_string(s);

}

vector<string> Graph::search(string search_string, size_t num_results_to_return)
{
	Node *n = get_start_node(), *next_node;
	size_t result_counter = 0;
	vector<string> results;

	string path_string_base;

	for (char c : search_string)
	{
		//go through the terminating strings and add them to the results vector
		next_node = n->get_next_node_with(c, path_string_base);

		if (next_node)
			n = next_node;
		else
			break;

		path_string_base += c;
	}

	//now all terminating words below this node in the graph are a search result - simply return the correct number of them

	//we must arrive at each node pointer with a certain path
	stack<pair<Node*, string>> nodes_to_check;

	nodes_to_check.push({ n , path_string_base + n->get_char()});
	string path_string;

	while (true)
	{

		n = nodes_to_check.top().first;

		path_string = nodes_to_check.top().second;

		nodes_to_check.pop();

		result_counter += n->get_terminating_strings(result_counter, num_results_to_return, results);
		
		if (result_counter >= num_results_to_return)
			return results;

		//use int here rather than size_t so the iteration works 
		auto new_nodes = n->get_next_nodes(path_string);

		for (Node* n : new_nodes)
			nodes_to_check.push({ n, path_string + n->get_char()});
		
		if (nodes_to_check.empty())
		{
			return results;
		}
			
	}

	return results;
}
