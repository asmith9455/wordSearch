#include "Node.h"

Node::Node(char c, size_t depth)
{
	_c = c;
	_depth = depth;
}

char Node::get_char()
{
	return _c;
}

size_t Node::get_terminating_strings(size_t index, size_t index_limit, vector<string>& add_to)
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

void Node::add_next_node(Node* n)
{
	next_nodes.push_back(n);
}

void Node::add_terminating_string(string s)
{
	_terminating_strings.push_back(s);
}

Node* Node::check_for_next_node_with(char c)
{
	for (Node* n : next_nodes)
		if (n->get_char() == c)
			return n;

	return nullptr;
}

Node::~Node()
{
}
