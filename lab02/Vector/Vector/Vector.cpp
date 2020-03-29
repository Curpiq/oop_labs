// Vector.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Вариант №6
#include "stdafx.h"
#include "VectorProcessor.h"
using namespace std;

int main()
{
    vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
    ProcessVector(numbers);
    sort(numbers.begin(), numbers.end());
    cout << fixed << setprecision(3);
    copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, " "));
    return 0;
}
