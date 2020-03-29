// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

bool ParseArgs(int argc, char* argv[], unsigned char& inputByte)
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n" << "Usage: flipbyte.exe <decimal number>" << endl;
        return false;
    }
    int num;
    try
    {
        num = stoi(argv[1]);
    }
    catch (const exception& err)
    {
        cout << err.what() << endl;
        return false;
    }

    if ((num < 0) || (num > 255))
    {
        cout << "Invalid argument. Range of numbers: 0 - 255" << endl;
        return false;
    }
    inputByte = static_cast<unsigned int>(num);
    return true;
}

unsigned char FlipByte(unsigned char number)
{
    unsigned char revNum = 0;
    for (int i = 0; i < 8; i++) {
        revNum <<= 1;
        revNum |= number & 1;
        number >>= 1;
    }
    return revNum;
}

int main(int argc, char* argv[])
{
    unsigned char inputByte;
    if (!ParseArgs(argc, argv, inputByte))
    {
        cout << "Input must be a decimal number in the byte range" << endl;
        return 1;
    }
    cout << static_cast<int>(FlipByte(inputByte)) << endl;
    return 0;
}