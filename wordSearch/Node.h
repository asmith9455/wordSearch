#pragma once
#include <vector>
#include <set>
#include "NodeConnection.h"
#include <algorithm>

using namespace std;



//could template this so that things other than strings can be searched
class Node
{
public:
	using unique_id_t = NodeConnection::unique_id_t;
	
private:
	char m_c;
	size_t m_depth;	//depth of the node
	set<unique_id_t> m_terminating_ids;

	vector<NodeConnection> m_node_connections; //each node contains references to a number of further nodes

public:

	Node() {}
	Node(char c, size_t depth);

	char get_char();
	void add_next_node_connection(Node* next_node, unique_id_t id);
	void add_terminating_id(unique_id_t id);

	size_t depth() { return m_depth;	}

	std::pair<Node*, set<unique_id_t>> get_next_node_with(char c, set<unique_id_t> incoming_ids) {
		
		set<unique_id_t> intersection_set;

		auto matching_node_con_it = std::find_if(m_node_connections.begin(), m_node_connections.end(),
			[&incoming_ids, &c, &intersection_set](NodeConnection nc) -> bool 
		{
			intersection_set = nc.get_path_intersection(incoming_ids);
			return !intersection_set.empty() && c == nc.get_next_node()->get_char();
		});

		if (matching_node_con_it == m_node_connections.end())
			return { nullptr, intersection_set };
		else
			return { &(*matching_node_con_it->get_next_node()), intersection_set };

	}

	std::pair<Node*, set<unique_id_t>> get_next_node_with(char c) {
		
		auto matching_node_con_it = std::find_if(m_node_connections.begin(), m_node_connections.end(),
			[&c](NodeConnection nc) -> bool
		{
			return c == nc.get_next_node()->get_char();
		});

		if (matching_node_con_it == m_node_connections.end())
			return { nullptr, set<unique_id_t>() };
		else
			return { &(*matching_node_con_it->get_next_node()),
					 matching_node_con_it->get_all_ids()	};

	}

	bool get_terminating_strings(size_t& result_counter, size_t num_results_to_return, vector<string>& results, set<unique_id_t> paths, string current_path) {

		//first check this node for any terminating strings and if they exist append to the results list

		auto inter_set_term = intersection_of_sets(m_terminating_ids, paths);

		if (!inter_set_term.empty())
		{
			results.push_back(current_path);
			++result_counter;
			if (result_counter == num_results_to_return)
				return true;
		}

		for (auto nc : m_node_connections)
		{
			auto path_intersection = nc.get_path_intersection(paths);

			if (!path_intersection.empty()) //if this is a valid path to continue down given the existing unique ids "paths"
				if (
					nc.get_next_node()->get_terminating_strings(
						result_counter, num_results_to_return, results, path_intersection, 
						current_path + nc.get_next_node()->get_char()))
					return true;

		}

		return false;

	}

};

