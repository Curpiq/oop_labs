// MiniDictionary.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Dictionary.h"
#include <windows.h>


void ConfirmSaving(const Dictionary& dictionary, const string& dictionaryFileName)
{
    cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;;
    string str;
    getline(cin, str);
    if ((str == "Y") || (str == "y"))
    {
        ofstream dictionaryFile(dictionaryFileName);
        SaveDictionary(dictionary, dictionaryFile);
        cout << "Изменения сохранены. До свидания." << endl;
    }
    else
    {
        cout << "Изменения не сохранены. До свидания." << endl;
    }
}

void UnknownLineProcessing(Dictionary& dictionary, const string& inputLine, bool& changed)
{
    string translation;
    cout << "Неизвестное слово \"" << inputLine << "\". Введите перевод или пустую строку для отказа." << endl;
    getline(cin, translation);
    if (translation != "")
    {
        AddTranslation(inputLine, translation, dictionary);
        cout << "Слово \"" << inputLine << "\" сохранено в словаре как \"" << translation << "\"." << endl;
        changed = true;
    }
    else
    {
        cout << "Слово \"" << inputLine << "\" проигнорировано." << endl;
    }
}

void InputLineProcessing(Dictionary& dictionary, const string& dictionaryFileName)
{
    string inputLine;
    string translation;
    bool changed = false;
    while (getline(cin, inputLine))
    {
        if (inputLine == "...")
        {
            if (changed)
            {
                ConfirmSaving(dictionary, dictionaryFileName);
            }
            return;
        }
        else if (FindTranslation(inputLine, translation, dictionary))
        {
            cout << translation << endl;
        }
        else
        {
            UnknownLineProcessing(dictionary, inputLine, changed);
        }
    }
}

bool ParseArgs(int argc, char* argv[], string& fileName)
{
    if (argc != 2)
    {
        cout << "Invalid arguments count" << endl;
        cout << "Usage: MiniDictionary.exe <dictionary file name>" << endl;
        return false;
    }
    else
    {
        fileName = argv[1];
        return true;
    }
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string dictionaryFileName;
    if (!ParseArgs(argc, argv, dictionaryFileName))
    {
        return 1;
    }
    ifstream dictionaryFile(dictionaryFileName);
    if (!dictionaryFile.is_open())
    {
        cout << "Failed to open" << dictionaryFileName << "for reading" << endl;
        return 1;
    }
    if (dictionaryFile.bad())
    {
        cout << "Failed to read data from " << dictionaryFileName << endl;
        return 1;
    }
    Dictionary dictionary = DictionaryFilling(dictionaryFile);
    InputLineProcessing(dictionary, dictionaryFileName);
    return 0;
}
