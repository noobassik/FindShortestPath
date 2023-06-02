#include "pch.h"
#include "CppUnitTest.h"
#include "../FindShortestPath/FindShortestPath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool compareVectors(const vector<int>& exp_vector, const vector<vector<int>>& real_vector)
{
	for (int i = 0; i < exp_vector.size(); i++) {
		if (exp_vector[i] != real_vector[0][i]) return false;
	}
}

namespace TestfillRowInVector
{
	TEST_CLASS(TestfillRowInVector)
	{
	public:
		TEST_METHOD(emptyString)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = "";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = {};
			int row = 0, col = 0;
			try {
				fillRowInVector(real_vector, labels, row, col, line);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const FileNotFoundException& ex) {
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		TEST_METHOD(elementsAreLetters)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = "A;B;C;D;E;";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = {};
			int row = 0, col = 0;
			try {
				fillRowInVector(real_vector, labels, row, col, line);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const FileNotFoundException& ex) {
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		TEST_METHOD(firstElemntIsEmpty)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = ";B;C;D;E;";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = {};
			int row = 0, col = 0;
			try {
				fillRowInVector(real_vector, labels, row, col, line);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const FileNotFoundException& ex) {
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		TEST_METHOD(elementsAreLettersWithDigits)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = "A1;B2;D3;C4;E5;";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = {};
			int row = 0, col = 0;
			try {
				fillRowInVector(real_vector, labels, row, col, line);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const FileNotFoundException& ex) {
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}

		TEST_METHOD(lineContainsNegativeDigits)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = "A;0;-1;0;2;0;";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = {};
			int row = 0, col = 0;
			try {
				fillRowInVector(real_vector, labels, row, col, line);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const FileNotFoundException& ex) {
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		TEST_METHOD(elementsAreDigitsStartedWithZeros)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = "A;0;001;0;2;0;";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = {0, 1, 0, 2, 0};
			int row = 0, col = 0;
			fillRowInVector(real_vector, labels, row, col, line);
			Assert::IsTrue(compareVectors(exp_vector, real_vector));
		}
		TEST_METHOD(oneElement)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = "A;1;";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = { 1 };
			int row = 0, col = 0;
			fillRowInVector(real_vector, labels, row, col, line);
			Assert::IsTrue(compareVectors(exp_vector, real_vector));
		}
		TEST_METHOD(lineContainsOnlyDelimeters)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = ";;;;;";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = {};
			int row = 0, col = 0;
			try {
				fillRowInVector(real_vector, labels, row, col, line);
				Assert::Fail(L"Expected exception not thrown.");
			}
			catch (const FileNotFoundException& ex) {
			}
			catch (const InvalidInputException& ex) {
			}
			catch (...) {
				Assert::Fail(L"Unexpected exception thrown.");
			}
		}
		TEST_METHOD(complex)
		{
			vector<string> labels = { "A", "B", "C", "D", "E" };
			string line = "A;0;1;0;2;0;";
			vector<vector<int>> real_vector;
			real_vector.resize(5, vector<int>(labels.size(), 0));
			vector<int> exp_vector = {0, 1, 0, 2, 0};
			int row = 0, col = 0;
			fillRowInVector(real_vector, labels, row, col, line);
			Assert::IsTrue(compareVectors(exp_vector, real_vector));
		}
	};
}
