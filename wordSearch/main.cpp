#include "Graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::vector;
using std::string;
using std::ifstream;
using std::getline;
using std::cin;
using std::cout;
using std::endl;

//reads words from a file containing one word per line
//and inserts them into a graph
Graph read_graph_from_file(string filepath) {
	Graph g;
	ifstream fs(filepath);
	string s;

	//add all strings in the file to the graph
	unsigned word_added_count = 0;

	while (getline(fs, s)) {
		g.addString(s);
		word_added_count++;
	}

	//can now quickly search the graph with partial or complete searches
	//order of results preserves the order in which strings were added.
	return g;
}

void user_graph_search_loop(Graph& g) {

	string s;
	size_t u;
	vector<string> results;

	while (true)
	{
		cout << "Search For: ";
		cin >> s;
		cout << endl << "Num Results: ";
		cin >> u;

		results = g.search(s, u);

		cout << endl << "Results are: " << endl;

		for (auto s : results)
			cout << s << endl;

	}
}

int main()
{

	Graph g2 = read_graph_from_file("word_list_a.txt");

	cout << "size is: " << g2.num_nodes() << endl;

	vector<string> results2 = g2.search("dea", 10);

	cout << "results: " << endl;

	for (const auto& r : results2)
		cout << "result: " << r << endl;

	auto r = g2.node_counts_by_depth();

	system("pause");

	return 0;
}