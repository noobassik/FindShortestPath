#include "pch.h"
#include "CppUnitTest.h"
#include "../FindShortestPath/FindShortestPath.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestmatrixValidation
{
	TEST_CLASS(TestmatrixValidation)
	{
	public:
		
		TEST_METHOD(wrongValueInArrivalCity)
		{
			vector<vector<int>> matrix = { {0,1,0,2,0},
											{0,0,3,2,0},
											{0,1,0,2,5},
											{0,1,33,0,5},
											{0,0,3,2,0} };
			vector<string> labels = { "A", "B", "C", "D", "E" };
			try {
				matrixValidation(matrix, labels);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		TEST_METHOD(roadInFirstCityExist)
		{
			vector<vector<int>> matrix = { {0,1,0,2,0},
											{1,0,3,2,0},
											{0,1,0,2,5},
											{0,1,0,0,5},
											{0,0,3,2,0} };
			vector<string> labels = { "A", "B", "C", "D", "E" };
			try {
				matrixValidation(matrix, labels);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		TEST_METHOD(oneWayPathExists)
		{
			vector<vector<int>> matrix = { {0,1,0,2,0},
											{0,0,3,2,0},
											{0,1,0,2,0},
											{0,1,3,0,5},
											{0,0,3,2,0} };
			vector<string> labels = { "A", "B", "C", "D", "E" };
			try {
				matrixValidation(matrix, labels);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		TEST_METHOD(horizontalAsymmetry)
		{
			vector<vector<int>> matrix = { {0,1,0,2,0},
											{0,0,3,2,0},
											{0,1,0,2,0},
											{0,1,3,0,5},
											{0,0,0,0,0} };
			vector<string> labels = { "A", "B", "C", "D", "E" };
			try {
				matrixValidation(matrix, labels);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
	};
}
