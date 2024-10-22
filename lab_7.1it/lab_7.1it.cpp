#include <iostream> 
#include <iomanip> 
#include <time.h> 
using namespace std;
void Create(int** Z, const int rowCount, const int colCount, const int Low,
    const int High, int i, int j);
void Print(int** Z, const int rowCount, const int colCount, int i, int j);
void Sort(int** Z, const int rowCount, const int colCount, int i0, int i1);
void Change(int** Z, const int row1, const int row2, const int colCount, int j);
void Calc(int** Z, const int rowCount, const int colCount, int& S, int& k, int i, int j);
int main()
{
    srand((unsigned)time(NULL));
    int Low = 4;
    int High = 45;
    int rowCount = 9;
    int colCount = 7;
    int** Z = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        Z[i] = new int[colCount];
    Create(Z, rowCount, colCount, Low, High, 0, 0);
    Print(Z, rowCount, colCount, 0, 0);
    Sort(Z, rowCount, colCount, 0, 0);
    Change(Z, rowCount, colCount, 0, 0);
    Print(Z, rowCount, colCount, 0, 0);

    int S = 0;
    int k = 0;
    Calc(Z, rowCount, colCount, S, k, 0, 0);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    Print(Z, rowCount, colCount, 0, 0);
    for (int i = 0; i < rowCount; i++)
        delete[] Z[i];
    delete[] Z;

    return 0;
}
void Create(int** Z, const int rowCount, const int colCount,
    const int Low, const int High, int i, int j)
{
    Z[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(Z, rowCount, colCount, Low, High, i, j + 1);
    else if (i < rowCount - 1)
        Create(Z, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** Z, const int rowCount, const int colCount, int i, int j)
{
    cout << setw(4) << Z[i][j];
    if (j < colCount - 1)
        Print(Z, rowCount, colCount, i, j + 1);
    else if (i < rowCount - 1)
    {
        cout << endl;
        Print(Z, rowCount, colCount, i + 1, 0);
    }
    else
        cout << endl << endl;
}

void Sort(int** Z, const int rowCount, const int colCount, int i0, int i1)
{
    if (i0 >= colCount - 1)
        return;

    if (i1 < colCount - i0 - 1)
    {
        if ((Z[0][i1] < Z[0][i1 + 1])
            ||
            (Z[0][i1] == Z[0][i1 + 1] &&
                Z[1][i1] > Z[1][i1 + 1])
            ||
            (Z[0][i1] == Z[0][i1 + 1] &&
                Z[1][i1] == Z[1][i1 + 1] &&
                Z[2][i1] < Z[2][i1 + 1]))
            Change(Z, i1, i1 + 1, rowCount, 0);

        Sort(Z, rowCount, colCount, i0, i1 + 1);
    }
    else
    {
        Sort(Z, rowCount, colCount, i0 + 1, 0);
    }
}

void Change(int** Z, const int col1, const int col2, const int rowCount, int j = 0)
{
    int tmp;
    if (j < rowCount)
    {
        tmp = Z[j][col1];
        Z[j][col1] = Z[j][col2];
        Z[j][col2] = tmp;
        Change(Z, col1, col2, rowCount, j + 1);
    }
    return;
}

void Calc(int** Z, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0)
{
    if (i >= rowCount)
        return;

    if (j < colCount)
    {
        if (Z[i][j] % 2 == 0 && !(i % 2 != 0 || j % 2 != 0))
        {
            S += Z[i][j];
            k++;
            Z[i][j] = 0;
        }
        Calc(Z, rowCount, colCount, S, k, i, j + 1);
    }
    else
    {
        Calc(Z, rowCount, colCount, S, k, i + 1, 0);
    }
}
