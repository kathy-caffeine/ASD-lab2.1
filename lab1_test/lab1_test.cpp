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
	};
}