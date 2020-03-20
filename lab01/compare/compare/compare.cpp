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

void CompareFiles(ifstream& file1, ifstream& file2, bool& isEqual, int& count)
{
    //Сравнение содержимого файлов
    string str1 = " ";
    string str2 = " ";
    while (!file1.eof() && !file2.eof())
    {
        getline(file1, str1);
        getline(file2, str2);
        if (str1 != str2)
        {
            isEqual = false;
            break;
        }
        else
        {
            count++;
            isEqual = true;
        }
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

    //Открытие файлов 
    ifstream file1;
    file1.open(args->fileName1);
    ifstream file2;
    file2.open(args->fileName2);
    if (!file1.is_open() || !file2.is_open())
    {
        cout << "Failed to open " << args->fileName1 << " and/or " << args->fileName2 << " for reading" << endl;
        return 1;
    }
    bool isEqual = false;
    int count = 1;
    CompareFiles(file1, file2, isEqual, count);
    if (file1.bad())
    {
        cout << "Failed to read data from " << args->fileName1 << endl;
        return 1;
    }
    if (file2.bad())
    {
        cout << "Failed to read data from " << args->fileName1 << endl;
        return 1;
    }
    if (file1.eof() && file2.eof() && isEqual == true)
    {
        cout << "Files are equal" << endl;
        return 0;
    }
    cout << "Files are different. Line number is " << count << endl;
    return 1;
}
