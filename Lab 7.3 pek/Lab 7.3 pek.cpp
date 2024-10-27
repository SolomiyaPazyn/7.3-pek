// Lab_7_3.cpp
// < Пазин, Соломія  >
// Лабораторна робота № 7.3.pek
// Опрацювання динамічних багатовимірних масивів. Рекурсивний спосіб.
// Варіант 25
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}


void InputRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
}


void PrintRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}


bool HasNegativeInColumn(int** a, const int rowCount, int colNo, int rowNo) {
    if (a[rowNo][colNo] < 0)
        return true;
    if (rowNo < rowCount - 1)
        return HasNegativeInColumn(a, rowCount, colNo, rowNo + 1);
    return false;
}

int SumColumn(int** a, const int rowCount, int colNo, int rowNo) {
    int sum = a[rowNo][colNo];
    if (rowNo < rowCount - 1)
        sum += SumColumn(a, rowCount, colNo, rowNo + 1);
    return sum;
}

int SumColumnsWithoutNegativeHelper(int** a, const int rowCount, const int colCount, int colNo) {
    int sum = 0;
    if (!HasNegativeInColumn(a, rowCount, colNo, 0))
        sum = SumColumn(a, rowCount, colNo, 0);

    if (colNo < colCount - 1)
        sum += SumColumnsWithoutNegativeHelper(a, rowCount, colCount, colNo + 1);

    return sum;
}

int SumColumnsWithoutNegative(int** a, const int rowCount, const int colCount) {
    return SumColumnsWithoutNegativeHelper(a, rowCount, colCount, 0);
}

int SumDiagonalElements(int** a, const int rowCount, const int colCount, int d, int i) {
    if (i >= rowCount)
        return 0;

    int j = d + i;
    int sum = 0;
    if (j >= 0 && j < colCount)
        sum = abs(a[i][j]);

    if (i < rowCount - 1)
        sum += SumDiagonalElements(a, rowCount, colCount, d, i + 1);

    return sum;
}

void MinSumOfParallelDiagonalsHelper(int** a, const int rowCount, const int colCount, int d, int& minSum) {
    int currentSum = SumDiagonalElements(a, rowCount, colCount, d, 0);
    if (currentSum < minSum)
        minSum = currentSum;

    if (d < colCount - 1)
        MinSumOfParallelDiagonalsHelper(a, rowCount, colCount, d + 1, minSum);
}

void MinSumOfParallelDiagonals(int** a, const int rowCount, const int colCount) {
    int minSum = INT_MAX;
    MinSumOfParallelDiagonalsHelper(a, rowCount, colCount, -rowCount + 1, minSum);
    cout << "Minimum sum of absolute values on diagonals parallel to the secondary diagonal = " << minSum << endl;
}

int main() {
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 14;
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);
    PrintRows(a, rowCount, colCount, 0);

    int sum = SumColumnsWithoutNegative(a, rowCount, colCount);
    cout << "Sum of elements in columns without negative elements = " << sum << endl;

    MinSumOfParallelDiagonals(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}