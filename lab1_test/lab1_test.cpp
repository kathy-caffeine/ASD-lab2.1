#include "pch.h"
#include "CppUnitTest.h"
#include"../lab1/RBTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab1test
{
	TEST_CLASS(lab1test)
	{
	public:
		RBTree <int> RB;
		int* keys;
		int* Ktree;
		int* values;
		int* Vtree;

		TEST_METHOD(insert_1)
		{
			RB.insert(1, 1);
			keys = new int[1]{ 1 };
			Ktree = RB.get_keys();
			Assert::AreEqual(keys[0], Ktree[0]);
		}
		TEST_METHOD(remove_1)
		{
			RB.insert(1, 1);
			RB.insert(2, 2);
			RB.remove(2);
			Assert::AreEqual((int)RB.get_size(), 1);
		}
		TEST_METHOD(clear_1)
		{
			RB.insert(1, 1);
			RB.insert(2, 2);
			RB.clear();
			Assert::AreEqual((int)RB.get_size(), 0);
		}
		TEST_METHOD(insert_3)
		{
			RB.insert(1, 1);
			RB.insert(3, 3);
			RB.insert(3, 3);
			keys = new int[3]{ 1, 3, 3 };
			Ktree = RB.get_keys();
			Assert::AreEqual((int)RB.get_size(), 3);
		}
		TEST_METHOD(remove_4)
		{
			RB.insert(1, 1);
			RB.insert(2, 2);
			RB.insert(3, 3);
			RB.remove(2);
			Assert::AreEqual((int)RB.get_size(), 1);
		}
		TEST_METHOD(clear_2)
		{
			RB.insert(1, 1);
			RB.insert(2, 2);
			RB.insert(3, 3);
			RB.clear();
			Assert::AreEqual((int)RB.get_size(), 0);
		}
	};
}