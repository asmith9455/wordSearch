#include "NodeConnection.h"



NodeConnection::NodeConnection(){}

NodeConnection::NodeConnection(Node * next_node, unique_id_t first_id)
{
	m_next_node = next_node;
	m_paths.insert(first_id);
}

std::set<unique_id_t> intersection_of_sets(std::set<unique_id_t> s1, std::set<unique_id_t> s2) {
	std::set<unique_id_t> to_return;

	std::vector<unique_id_t> tmp(std::max(s1.size(), s2.size()), 0);

	auto it = std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), tmp.begin());

	tmp.resize(it - tmp.begin());

	for (const auto& i : tmp)
		to_return.insert(i);

	return to_return;

}
