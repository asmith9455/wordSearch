#include "Graph.h"

void Graph::add_node(Node n){
	nodes->push_back(n);
}

Node* Graph::last_added_node() {
	if (nodes->empty())
		return nullptr;
	else
		return &(nodes->back());
}

void Graph::addString(string s)
{
	Node *n = &start_node, *next_node;
	string tmp;
	size_t depth = 1;

	for (char c : s)
	{
		tmp += c;
		//this is not the desired behaviour - the memory usage is much higher this way - need to be able to search all nodes at a given depth level
		next_node = n->check_for_next_node_with(c);

		if (!next_node)
		{	// if tmpNode is null (the node for 'c' doesn't exist), we need to add a node with this character.
			add_node(Node(c, depth));
			next_node = last_added_node();		//point to the most recently added element.
			n->add_next_node(next_node);
		}

		//now next_node points to the next node @ depth that corresponds to the string s
		
		n = next_node;

		depth++;
	}

	m_max_depth = max(m_max_depth, depth - 1);

	//now just need to add the string s as a terminating string at node n (corresponding to the last character)
	n->add_terminating_string(s);

}

vector<string> Graph::search(string search_string, size_t num_results_to_return)
{
	Node *n = &start_node, *next_node;
	size_t result_counter = 0;
	vector<string> results;

	for (char c : search_string)
	{
		//go through the terminating strings and add them to the results vector

		next_node = n->check_for_next_node_with(c);

		if (next_node)
			n = next_node;
		else
			break;
	}

	//now all terminating words below this node in the graph are a search result - simply return the correct number of them

	stack<Node*> nodes_to_check;

	nodes_to_check.push(n);

	while (true)
	{
		n = nodes_to_check.top();
		nodes_to_check.pop();

		result_counter += n->get_terminating_strings(result_counter, num_results_to_return, results);
		
		if (result_counter >= num_results_to_return)
			return results;

		//use int here rather than size_t so the iteration works 
		for (auto it = n->next_nodes.rbegin(); it != n->next_nodes.rend(); ++it)
			nodes_to_check.push(*it);
		
		if (nodes_to_check.empty())
		{
			return results;
		}
			
	}

	return results;
}
