#include "pch.h"
#include "CppUnitTest.h"
#include "../FindShortestPath/FindShortestPath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestifStringIsDigit
{
	TEST_CLASS(TestifStringIsDigit)
	{
	public:

		TEST_METHOD(EmptyString)
		{
			string string = "";
			bool exp_result = false;
			bool result = ifStringIsDigit(string);
			Assert::AreEqual((int)exp_result, (int)result);
		}
		TEST_METHOD(stringContainsOnlyNumberZero)
		{
			string string = "0";
			bool exp_result = true;
			bool result = ifStringIsDigit(string);
			Assert::AreEqual((int)exp_result, (int)result);
		}
		TEST_METHOD(stringStartsWithZero)
		{
			string string = "023";
			bool exp_result = false;
			bool result = ifStringIsDigit(string);
			Assert::AreEqual((int)exp_result, (int)result);
		}
		TEST_METHOD(stringIsNegativeDigit)
		{
			string string = "-123";
			bool exp_result = false;
			bool result = ifStringIsDigit(string);
			Assert::AreEqual((int)exp_result, (int)result);
		}
		TEST_METHOD(digitsAreSeparatedBySpace)
		{
			string string = "1 3";
			bool exp_result = false;
			bool result = ifStringIsDigit(string);
			Assert::AreEqual((int)exp_result, (int)result);
		}
		TEST_METHOD(spaceBeforeDigits)
		{
			string string = " 123";
			bool exp_result = false;
			bool result = ifStringIsDigit(string);
			Assert::AreEqual((int)exp_result, (int)result);
		}
		TEST_METHOD(spaceAfterDigits)
		{
			string string = "32 ";
			bool exp_result = false;
			bool result = ifStringIsDigit(string);
			Assert::AreEqual((int)exp_result, (int)result);
		}
		TEST_METHOD(hexadecimalDigit)
		{
			string string = "1A";
			bool exp_result = false;
			bool result = ifStringIsDigit(string);
			Assert::AreEqual((int)exp_result, (int)result);
		}
	};
}
