// invert.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 
#include <array>
using namespace std;
const int MAX_SIZE = 3;
typedef array<array<double, MAX_SIZE>, MAX_SIZE> Matrix3x3;

struct Args
{
    string MatrixFile;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n" << "Usage: invert.exe <matrix file1>" << endl;
        return nullopt;
    }
    Args args;
    args.MatrixFile = argv[1];
    return args;
}

bool ReadMatrix(const optional<Args>& args, Matrix3x3& matrix)
{
    string str;
    ifstream file;
    file.open(args->MatrixFile);
    if (!file.is_open())
    {
        cout << "Failed to open " << args->MatrixFile << " for reading" << endl;
        return false;
    }
    bool isCorrectMatrix = true;
    int row = 0;
    while (!file.eof() && isCorrectMatrix)
    {
        if (row == MAX_SIZE)
        {
            isCorrectMatrix = false;
            break;
        }
        getline(file, str);
        istringstream line(str);
        int column = 0;
        while (!line.eof())
        {
            if (column == MAX_SIZE)
            {
                isCorrectMatrix = false;
                break;
            }
            line >> matrix[row][column];
            column++;
        }
        if (column < MAX_SIZE)
        {
            isCorrectMatrix = false;
            break;
        }
        row++;
    }
    if ((row < MAX_SIZE) || (!isCorrectMatrix))
    {
        cout << "Input must be a 3x3 dimensional matrix of numbers" << endl;
        return false;
    }
    if (file.bad())
    {
        cout << "Failed to read data from " << args->MatrixFile << endl;
        return false;
    }
    return true;
}

double GetDeterminant(const Matrix3x3& matrix)
{
    double det = matrix[0][0] * matrix[1][1] * matrix[2][2] +
        matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] -
        matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][0] * matrix[1][2] * matrix[2][1] -
        matrix[0][1] * matrix[1][0] * matrix[2][2];
    return det;
}

Matrix3x3 TransposeMatrix(const Matrix3x3& matrix)
{
    Matrix3x3 transpMatrix;
    transpMatrix = matrix;
    for (int row = 0; row < MAX_SIZE - 1; row++)
    {
        for (int col = row + 1; col < MAX_SIZE; col++)
        {
            swap(transpMatrix[col][row], transpMatrix[row][col]);   
        }
    }
    return transpMatrix;
}

Matrix3x3 GetAdjMatrix(const Matrix3x3& matrix)
{
    Matrix3x3 adjMatrix;
    adjMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    adjMatrix[0][1] = (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) * (-1);
    adjMatrix[0][2] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];
    adjMatrix[1][0] = (matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]) * (-1);
    adjMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adjMatrix[1][2] = (matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]) * (-1);
    adjMatrix[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    adjMatrix[2][1] = (matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]) * (-1);
    adjMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            if (adjMatrix[i][j] == -0)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }
    return adjMatrix;
}

bool Invert(const Matrix3x3& matrix, Matrix3x3& invertMatrix)
{
    double det = GetDeterminant(matrix);
    if (det == 0)
    {
        return false;
    }
    Matrix3x3 transpMatrix = TransposeMatrix(matrix);
    Matrix3x3 adjMatrix = GetAdjMatrix(transpMatrix);
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            invertMatrix[i][j] = adjMatrix[i][j] / det;
        }
    }
    return true;
}

void PrintMatrix(const Matrix3x3& matrix)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            cout << fixed << setprecision(3) << matrix[i][j];
            if (j < 2)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}


int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    //Проверка правильности параметров командной строки
    if (!args)
    {
        return 1;
    }
    Matrix3x3 inputMatrix;
    if (!ReadMatrix(args, inputMatrix))
    {
        return 1;
    }
    Matrix3x3 invertMatrix;
    if (!Invert(inputMatrix, invertMatrix))
    {
        cout << "The inverse matrix doesn't exist" << endl;
        return 1;
    }
    PrintMatrix(invertMatrix);
    return 0;

}
