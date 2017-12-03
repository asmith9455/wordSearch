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

void test_001()
{
	Graph g;

	g.addString("abc");
	g.addString("abcd");
	g.addString("test2");
	g.addString("test1");
	g.addString("diagram");
	g.addString("untest");

	auto r = g.search("test", 5);

	cout << "Results are: " << endl;

	for (auto s : r)
		cout << s << endl;
}

//reads words from a file containing one word per line
//and inserts them into a graph, which is then returned by reference
void read_graph_from_file(Graph &g, string filepath) {

	ifstream fs(filepath);
	string s;

	//add all strings in the file to the graph

	unsigned word_added_count = 0;

	while (getline(fs, s)) {
		g.addString(s);
		word_added_count++;

		/*if (word_added_count % 10000 == 0) {
			cout << word_added_count << endl;
		}*/

		//if (false && word_added_count > 10000)
		//	break;
	}

	//can now quickly search the graph with partial or complete searches
	//order of results preserves the order in which strings were added.


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

vector<string> search_graph(Graph& g)
{
	return g.search("dea", 10);
}

int main()
{

	Graph g;
	vector<string> results;
	
	cout << "Hello" << endl;

	read_graph_from_file(g, "word_list_a.txt");

	results = search_graph(g);

	for (const auto& r : results)
		cout << "result: " << r << endl;

	//user_graph_search_loop(g);

	system("pause");

	return 0;
}