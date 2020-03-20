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

const int maxSize = 3;

struct Args
{
    string fileName;
};

struct Matrix3x3
{
    array<array<double, maxSize>, maxSize> matrix;
    explicit Matrix3x3() noexcept : matrix{} {}
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

optional<Matrix3x3> ReadMatrix(optional<Args>& args)
{
    string str;
    ifstream file;
    file.open(args->fileName);
    if (!file.is_open())
    {
        cout << "Failed to open " << args->fileName << " for reading" << endl;
        return nullopt;
    }
    if (file.bad())
    {
        cout << "Failed to read data from " << args->fileName << endl;
        return nullopt;
    }
    Matrix3x3 inputMatrix;
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
        istringstream line(str);
        double x;
        while (line >> x)
        {
            inputMatrix.matrix[row][column] = x;
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
        return nullopt;
    }
    return inputMatrix;
}

double GetDeterminant(array<array<double, 3>, 3> matrix)
{
    double det = matrix[0][0] * matrix[1][1] * matrix[2][2] +
        matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] -
        matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][0] * matrix[1][2] * matrix[2][1] -
        matrix[0][1] * matrix[1][0] * matrix[2][2];
    cout << det << endl;
    return det;
}

optional<Matrix3x3> TransposeMatrix(array<array<double, 3>, 3> matrix)
{
    Matrix3x3 transpMatrix;
    for (int row = 0; row < maxSize - 1; row++)
    {
        for (int col = row + 1; col < maxSize; col++)
        {
            swap(matrix[col][row], matrix[row][col]);
            
        }
    }
    transpMatrix.matrix = matrix;
    return transpMatrix;
}

optional<Matrix3x3> GetAdjMatrix(array<array<double, 3>, 3> matrix)
{
    Matrix3x3 adjMatrix;
    adjMatrix.matrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
    adjMatrix.matrix[0][1] = (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) * (-1);
    adjMatrix.matrix[0][2] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];
    adjMatrix.matrix[1][0] = (matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]) * (-1);
    adjMatrix.matrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
    adjMatrix.matrix[1][2] = (matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]) * (-1);
    adjMatrix.matrix[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
    adjMatrix.matrix[2][1] = (matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]) * (-1);
    adjMatrix.matrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    return adjMatrix;
}

optional<Matrix3x3> GetInvertMatrix(array<array<double, 3>, 3> adjMatrix, double det)
{
    Matrix3x3 invertMatrix{};
    for (int i = 0; i < maxSize; i++)
    {
        for (int j = 0; j < maxSize; j++)
        {
            invertMatrix.matrix[i][j] = adjMatrix[i][j]/det;
        }
    }
    return invertMatrix;
}

optional<Matrix3x3> Invert(optional<Matrix3x3> matrix)
{
    double det = GetDeterminant(matrix->matrix);
    if (det == 0)
    {
        return nullopt;
    }
    auto transpMatrix = TransposeMatrix(matrix->matrix);
    auto adjMatrix = GetAdjMatrix(transpMatrix->matrix);
    auto invertMatrix = GetInvertMatrix(adjMatrix->matrix, det);
    return invertMatrix;
}

void PrintMatrix(array<array<double, 3>, 3> matrix)
{
    for (int i = 0; i < maxSize; i++)
    {
        for (int j = 0; j < maxSize; j++)
        {
            if (matrix[i][j] == -0)
            {
                matrix[i][j] = 0;
            }
            cout << fixed << setprecision(3) << matrix[i][j] << " ";
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

    auto inputMatrix = ReadMatrix(args);
    if (!inputMatrix)
    {
        return 1;
    }

    auto invertMatrix = Invert(inputMatrix);
    if (!invertMatrix)
    {
        cout << "The inverse matrix doesn't exist" << endl;
        return 1;
    }
    PrintMatrix(invertMatrix->matrix);
    return 0;

}
