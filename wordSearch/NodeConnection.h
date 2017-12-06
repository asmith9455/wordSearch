#pragma once
//#include "Node.h"
#include <vector>
#include <set>
#include <algorithm>


using unique_id_t = size_t;

std::set<unique_id_t> intersection_of_sets(std::set<unique_id_t> s1, std::set<unique_id_t> s2);

class Node;


class NodeConnection
{
public:
	using unique_id_t = size_t;

private:
	Node* m_next_node = nullptr;
	std::set<unique_id_t> m_paths;

public:

	NodeConnection();
	NodeConnection(Node* next_node, unique_id_t first_id);

	Node* get_next_node() { return m_next_node; }
	
	void add_path_id(unique_id_t id) { m_paths.insert(id); }

	std::set<unique_id_t> get_path_intersection(std::set<unique_id_t> s) {
		return intersection_of_sets(s, m_paths);
	}

	std::set<unique_id_t> get_all_ids() {
		return m_paths;
	}

};

