// HTMLDecode.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "StringDecoder.h"
using namespace std;

int main()
{
    string inputString;
    while (getline(cin, inputString))
    {
        cout << StringDecoder(inputString) << endl;
    }
    return 0;
}

