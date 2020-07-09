#include "GeneratePrimeNumbers.h"


int main(int argc, char* argv[])
{
    int upperBound;
    if (!ParseArgs(argc, argv, upperBound))
    {
        return 1;
    }
    set<int> primeNumbers = GetPrimeNumbersSet(upperBound);
    for (auto number : primeNumbers)
    {
        cout << number << " ";
    }
    return 0;

}

