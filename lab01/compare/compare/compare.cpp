// compare.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include "compare.h"
using namespace std;

struct Args
{
    string fileName1;
    string fileName2;
};

struct ComparationResults
{
    int num;
    bool isEqual;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n" << "Usage: compare.exe <file1> <file2>" << endl;
        return nullopt;
    }
    Args args;
    args.fileName1 = argv[1];
    args.fileName2 = argv[2];
    return args;
}

optional<ComparationResults> CompareFiles(istream& file1, istream& file2)
{
    //Сравнение содержимого файлов
    string str1;
    string str2;
    ComparationResults comparationResults;
    comparationResults.isEqual = false;
    comparationResults.num = 1;
    while (!file1.eof() && !file2.eof())
    {
        getline(file1, str1);
        getline(file2, str2);
        if (str1 != str2)
        {
            comparationResults.isEqual = false;
            return comparationResults;
        }
        comparationResults.num++;
        comparationResults.isEqual = true;
    }
    return comparationResults;
}

int Comparation(optional<Args>& args)
{
    //Открытие файлов 
    ifstream file1;
    file1.open(args->fileName1);
    ifstream file2;
    file2.open(args->fileName2);
    if (!file1.is_open() || !file2.is_open())
    {
        cout << "Failed to open " << args->fileName1 << " and/or " << args->fileName2 << " for reading" << endl;
        return -1;
    }
    auto comparationResults = CompareFiles(file1, file2);
    if (file1.bad())
    {
        cout << "Failed to read data from " << args->fileName1 << endl;
        return -1;
    }
    if (file2.bad())
    {
        cout << "Failed to read data from " << args->fileName1 << endl;
        return -1;
    }
    if (file1.eof() && file2.eof() && comparationResults->isEqual == true)
    {
        return 0;
    }
    return comparationResults->num;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    //Проверка правильности параметров командной строки
    if (!args)
    {
        return 1;
    }
    int result = Comparation(args);
    if (result == -1)
    {
        return 1;
    }
    if (result == 0)
    {
        cout << "Files are equal" << endl;
        return 0;
    }
    cout << "Files are different. Line number is " << result << endl;
    return 1;
}
