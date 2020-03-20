// invert.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int maxSize = 3;
struct Args
{
    string fileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n" << "Usage: compare.exe <file1>" << endl;
        return nullopt;
    }
    Args args;
    args.fileName = argv[1];
    return args;
}

bool ReadMatrix(optional<Args>& args, double inputMatrix[maxSize][maxSize])
{
    ifstream file;
    file.open(args->fileName);
    if (!file.is_open())
    {
        cout << "Failed to open " << args->fileName << " for reading" << endl;
        return false;
    }
    string str;
    bool correct = true;
    int column = 0;
    int row = 0;
    while ((getline(file, str)) && (correct == true)) 
    {
        if (row == maxSize)
        {
            correct = false;
            break;
        }
        stringstream line(str);
        while (line >> inputMatrix[row][column])
        {
            column++;
        }
        if (column != maxSize)
        {
            correct = false;
            break;
        }
        column = 0;
        row++;
    }
    if (row < maxSize)
    {
        correct = false;
    }
    if (!correct)
    {
        cout << "Input must be a 3x3 dimensional matrix of numbers" << endl;
        return false;
    }
    if (file.bad())
    {
        cout << "Failed to read data from " << args->fileName << endl;
        return false;
    }
    return true;
}

double GetDeterminant(double matrix[maxSize][maxSize])
{
    double det = matrix[0][0] * matrix[1][1] * matrix[2][2] +
        matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] -
        matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][0] * matrix[1][2] * matrix[2][1] -
        matrix[0][1] * matrix[1][0] * matrix[2][2];
    return det;
}

void TransposeMatrix(double matrix[maxSize][maxSize])
{
    for (int row = 0; row < maxSize - 1; row++)
    {
        for (int col = row + 1; col < maxSize; col++)
        {
            swap(matrix[col][row], matrix[row][col]);
        }
    }
}

void GetAdjMatrix(double matrix[maxSize][maxSize], double adjMatrix[maxSize][maxSize])
{
    adjMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    adjMatrix[0][1] = (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) * (-1);
    adjMatrix[0][2] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];
    adjMatrix[1][0] = (matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]) * (-1);
    adjMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adjMatrix[1][2] = (matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]) * (-1);
    adjMatrix[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    adjMatrix[2][1] = (matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]) * (-1);
    adjMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

void GetInvertMatrix(double matrix[maxSize][maxSize],double adjMatrix[maxSize][maxSize], double det)
{
    for (int i = 0; i < maxSize; i++)
    {
        for (int j = 0; j < maxSize; j++)
        {
            matrix[i][j] = adjMatrix[i][j]/det;
        }
    }
}

bool Invert(double matrix[maxSize][maxSize])
{
    double det = GetDeterminant(matrix);
    if (det == 0)
    {
        return false;
    }
    TransposeMatrix(matrix);
    double adjMatrix[maxSize][maxSize];
    GetAdjMatrix(matrix, adjMatrix);
    GetInvertMatrix(matrix, adjMatrix, det);
    return true;
}


int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    //Проверка правильности параметров командной строки
    if (!args)
    {
        return 1;
    }
    double inputMatrix[maxSize][maxSize];
    if (!ReadMatrix(args, inputMatrix))
    {
        return 1;
    }
    if (!Invert(inputMatrix))
    {
        cout << "Обратной матрицы не существует" << endl;
        return 1;
    }
    for (int i = 0; i < maxSize; i++)
    {
        for (int j = 0; j < maxSize; j++)
        {
            if (inputMatrix[i][j] == -0) 
            {
                inputMatrix[i][j] = 0;
            }
            cout << inputMatrix[i][j] << " ";

        }
        cout << endl;
    }
    return 0;

}
