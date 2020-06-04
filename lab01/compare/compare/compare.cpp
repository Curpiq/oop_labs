// compare.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <optional>

using namespace std;

struct Args
{
    string fileName1;
    string fileName2;
};

struct Comparing
{
    int lineNumber;
    bool isEqual;
};

struct ComparisonResult
{
    int result = 0;
};

Comparing CompareFiles(istream& file1, istream& file2)
{
    //Сравнение содержимого файлов
    Comparing comparing;
    comparing.lineNumber = 1;
    comparing.isEqual = false;
    string str1;
    string str2;
    while (!file1.eof() && !file2.eof())
    {
        getline(file1, str1);
        getline(file2, str2);
        if (str1 != str2)
        {
            comparing.isEqual = false;
            return comparing;
        }
        comparing.isEqual = true;
        comparing.lineNumber++;
    }
    return comparing;
}

optional<ComparisonResult> Compare(string fileName1, string fileName2)
{
    //Открытие файлов 
    ifstream file1;
    file1.open(fileName1);
    ifstream file2;
    file2.open(fileName2);
    if (!file1.is_open() || !file2.is_open())
    {
        cout << "Failed to open " << fileName1 << " and/or " << fileName2 << " for reading" << endl;
        return nullopt;
    }
    if (file1.bad() || file2.bad())
    {
        cout << "Failed to read data from " <<fileName1 << "and/or" << fileName2 << endl;
        return nullopt;
    }
    ComparisonResult comparisonResult;
    Comparing result = CompareFiles(file1, file2);
    if (file1.eof() && file2.eof() && result.isEqual == true)
    {
        return comparisonResult;
    }
    comparisonResult.result = result.lineNumber;
    return comparisonResult;
}

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

int main(int argc, char* argv[])
{
    //Проверка правильности параметров командной строки
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }
    auto comparisonResult = Compare(args->fileName1, args->fileName2);
    if (!comparisonResult)
    {
        return 1;
    }
    if (comparisonResult->result == 0)
    {
        cout << "Files are equal" << endl;
        return 0;
    }
    cout << "Files are different. Line number is " << comparisonResult->result << endl;
    return 1;
}
