// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

int ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n" << "Usage: flipbyte.exe <decimal number>" << endl;
        return -1;
    }
    bool parsed = true;
    int num;
    try
    {
        num = stoi(argv[1]);
    }
    catch (const invalid_argument & err)
    {
        cout << err.what() << endl;
        parsed = false;
    }
    catch (const out_of_range & err)
    {
        cout << err.what() << endl;
        parsed = false;
    }

    if (!parsed)
    {
        cout << "Input must be a decimal number in the byte range" << endl;
        return -1;
    }

    if ((num < 0) || (num > 255))
    {
        cout << "Invalid argument. Range of numbers: 0 - 255" << endl;
        return -1;
    }

    return num;
}

unsigned int FlipByte(int num)
{
    unsigned int number = num;
    unsigned int revNum;
    for (revNum = 0; number; number >>= 1) {
        revNum <<= 1;
        revNum |= number & 1;
    }
    if (num < 128)
    {
        revNum <<= 7 - (int)logb(revNum);
    }
    return revNum;
}

int main(int argc, char* argv[])
{
    int num = ParseArgs(argc, argv);
    if (num == -1)
    {
        return 1;
    }
    unsigned int revNum = FlipByte(num);
    cout << revNum << endl;
    return 0;
}