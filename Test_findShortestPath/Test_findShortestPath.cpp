#include "pch.h"
#include "CppUnitTest.h"
#include "../FindShortestPath/FindShortestPath.h"
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestfindShortestPath
{
	TEST_CLASS(TestfindShortestPath)
	{
	public:
		
		TEST_METHOD(oneCity)
		{
			vector<vector<int>> matrix = { {0} };
			int V = 1;
			int src = 0;
			int result = findShortestPath(matrix, V, src);
			int exp_result = 0;

			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(twoCity)
		{
			vector<vector<int>> matrix = { {0, 2},
										   {0, 0} };
			int V = 2;
			int src = 0;
			int result = findShortestPath(matrix, V, src);
			int exp_result = 2;

			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(threeCity)
		{
			vector<vector<int>> matrix = {  {0,1,0},
											{0,0,3},
											{0,1,0} };
			int V = 3;
			int src = 0;
			int result = findShortestPath(matrix, V, src);
			int exp_result = 4;

			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(initialCityIsBetweenFirstAndLast)
		{
			vector<vector<int>> matrix = {  {0,1,0},
											{0,0,3},
											{0,1,0} };
			int V = 3;
			int src = 1;
			int result = findShortestPath(matrix, V, src);
			int exp_result = 3;

			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(initialCityIsLast)
		{
			vector<vector<int>> matrix = {  {0,1,0},
											{0,0,3},
											{0,1,0} };
			int V = 3;
			int src = 2;
			int result = findShortestPath(matrix, V, src);
			int exp_result = 0;

			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(oneShortestPath)
		{
			vector<vector<int>> matrix = {  {0,1,0,0},
											{0,0,3,4},
											{0,1,0,4},
											{0,1,3,0} };
			int V = 4;
			int src = 0;
			int result = findShortestPath(matrix, V, src);
			int exp_result = 5;

			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(twoShortestPaths)
		{
			vector<vector<int>> matrix = { {0,2,0,0,0},
											{0,0,1,1,0},
											{0,2,0,1,4},
											{0,2,1,0,4},
											{0,0,1,1,0} };
			int V = 5;
			int src = 0;
			int result = findShortestPath(matrix, V, src);
			int exp_result = 7;

			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(allPathsAreShortest)
		{
			vector<vector<int>> matrix = { {0,1,0,0,0},
											{0,0,1,1,0},
											{0,1,0,1,1},
											{0,1,1,0,1},
											{0,0,1,1,0} };

			int V = 5;
			int src = 0;
			int result = findShortestPath(matrix, V, src);
			int exp_result = 3;

			Assert::AreEqual(exp_result, result);
		}
	};
}
