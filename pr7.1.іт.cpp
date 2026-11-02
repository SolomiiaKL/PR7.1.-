// Lab_7_1.cpp
// Соломія Клак
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Варіант 14

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Прототипи функцій згідно з методичкою
void Create(int** z, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** z, const int rowCount, const int colCount);
void Sort(int** z, const int rowCount, const int colCount);
void Change(int** z, const int col1, const int col2, const int rowCount);
void Calc(int** z, const int rowCount, const int colCount, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));

    // Параметри варіанта 14
    const int Low = 18;
    const int High = 74;
    const int rowCount = 9;
    const int colCount = 6;

    // Виділення пам'яті для динамічної матриці Z(9x6)
    int** z = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        z[i] = new int[colCount];

    // 1. Формування та виведення початкової матриці
    Create(z, rowCount, colCount, Low, High);
    cout << "Initial matrix Z:" << endl;
    Print(z, rowCount, colCount);

    // 2. Впорядкування стовпчиків за ключами і виведення модифікованої матриці
    Sort(z, rowCount, colCount);
    cout << "Sorted matrix Z (columns rearranged):" << endl;
    Print(z, rowCount, colCount);

    // 3. Обчислення кількості, суми за критерієм та заміна нулями
    int S = 0;
    int k = 0;
    Calc(z, rowCount, colCount, S, k);

    // Виведення результатів та остаточної матриці
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix Z (after Calc):" << endl;
    Print(z, rowCount, colCount);

    // Звільнення динамічної пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] z[i];
    delete[] z;

    return 0;
}

// Функція формування елементів матриці випадковими числами
void Create(int** z, const int rowCount, const int colCount, const int Low, const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            z[i][j] = Low + rand() % (High - Low + 1);
}

// Функція форматного виведення матриці
void Print(int** z, const int rowCount, const int colCount)
{
    cout << endl;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            cout << setw(5) << z[i][j];
        cout << endl;
    }
    cout << endl;
}

// Функція перестановки двох стовпчиків місцями
void Change(int** z, const int col1, const int col2, const int rowCount)
{
    int tmp;
    for (int i = 0; i < rowCount; i++)
    {
        tmp = z[i][col1];
        z[i][col1] = z[i][col2];
        z[i][col2] = tmp;
    }
}

// Функція впорядкування стовпчиків за ключами: -> <- <-
void Sort(int** z, const int rowCount, const int colCount)
{
    for (int i0 = 0; i0 < colCount - 1; i0++)
    {
        for (int i1 = 0; i1 < colCount - i0 - 1; i1++)
        {
            // Ключ 1: 1-й рядок за зростанням (z[0][i1] > z[0][i1 + 1])
            // Ключ 2: якщо 1-й однакові, то 2-й рядок за спаданням (z[1][i1] < z[1][i1 + 1])
            // Ключ 3: якщо 1-й і 2-й однакові, то 3-й рядок за спаданням (z[2][i1] < z[2][i1 + 1])
            if ((z[0][i1] > z[0][i1 + 1]) ||
                (z[0][i1] == z[0][i1 + 1] && z[1][i1] < z[1][i1 + 1]) ||
                (z[0][i1] == z[0][i1 + 1] && z[1][i1] == z[1][i1 + 1] && z[2][i1] < z[2][i1 + 1]))
            {
                Change(z, i1, i1 + 1, rowCount);
            }
        }
    }
}

// Функція обчислення суми, кількості та заміни елементів нулями
void Calc(int** z, const int rowCount, const int colCount, int& S, int& k)
{
    S = 0;
    k = 0;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            // Критерій Варіанта 14: "всі, крім: непарних або кратних 7"
            // Перевіряємо заперечення умови (непарне або кратне 7):
            if (!(z[i][j] % 2 != 0 || z[i][j] % 7 == 0))
            {
                S += z[i][j];
                k++;
                z[i][j] = 0;
            }
        }
    }
}