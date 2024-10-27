#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab 7.3 pek.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const int rowCount = 4;
            const int colCount = 4;

            
            int** a = new int* [rowCount];
            for (int i = 0; i < rowCount; i++) {
                a[i] = new int[colCount];
            }

            
            a[0][0] = 1;   a[0][1] = 2;   a[0][2] = 3;   a[0][3] = 4;
            a[1][0] = 5;   a[1][1] = 6;   a[1][2] = 7;   a[1][3] = 8;
            a[2][0] = 9;   a[2][1] = -10; a[2][2] = 11;  a[2][3] = 12;
            a[3][0] = 13;  a[3][1] = 14;  a[3][2] = 15;  a[3][3] = 16;

            
            int expectedSum = 104; 

            
            int actualSum = SumColumnsWithoutNegative(a, rowCount, colCount);

            
            Assert::AreEqual(expectedSum, actualSum);

            
            for (int i = 0; i < rowCount; i++) {
                delete[] a[i];
            }
            delete[] a;
        
		}
	};
}
