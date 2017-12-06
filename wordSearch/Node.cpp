#include "Node.h"

Node::Node(char c, size_t depth)
{
	m_c = c;
	m_depth = depth;
}

char Node::get_char()
{
	return m_c;
}



// the path string is the string including all chars up to this node, but not including this node
void Node::add_next_node_connection(Node* next_node, unique_id_t id)
{
	//check if there is a node connection to n already
	auto it = std::find_if(m_node_connections.begin(), m_node_connections.end(), 
		[&next_node](NodeConnection nc) -> bool {return nc.get_next_node() == next_node; });

	if (it != m_node_connections.end())			//if the next_node pointer is already a connected node
		it->add_path_id(id);
	else										//otherwise we need to add a new connection to the node
		m_node_connections.push_back(NodeConnection(next_node, id));
}

void Node::add_terminating_id(unique_id_t id) {
	m_terminating_ids.insert(id);
}

/*size_t Node::get_terminating_strings(size_t index, size_t index_limit, vector<string>& add_to)
{
	size_t init_size = add_to.size();

	for (string s : _terminating_strings)
	{
		add_to.push_back(s);

		if (++index == index_limit)
			return index_limit - init_size;
	}

	return add_to.size() - init_size;
}

vector<Node*> Node::get_next_nodes(string path_string)
{
	size_t index = 0;
	vector<Node*> results;

	for (Node* n : next_nodes) {

		bool path_matches = std::find(path_strings[index].begin(), path_strings[index].end(), path_string) != path_strings[index].end();

		if (path_matches)
			results.push_back(n);

		++index;
	}

	return results;
}

Node* Node::get_next_node_with(char c, string path_string)
{
	size_t index = 0;

	for (Node* n : next_nodes) {

		bool path_matches = std::find(path_strings[index].begin(), path_strings[index].end(), path_string) != path_strings[index].end();

		if (n->get_char() == c)
		{
//			if (!path_matches)
//				path_strings[index].push_back(path_string);
			
			return n;
		}
		++index;
	}
		
	return nullptr;
}*/

