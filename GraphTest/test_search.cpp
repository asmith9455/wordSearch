#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraphTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{

			Graph g;

			read_graph_from_file(g, "word_list_a.txt");

			user_graph_search_loop(g);
			bool b = true, c = false;

			std::vector<std::string> expected_results = { "" };
			Assert::AreEqual(b, c);
		}

	};
}