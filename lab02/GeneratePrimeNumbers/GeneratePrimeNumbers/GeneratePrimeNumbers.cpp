#include "GeneratePrimeNumbers.h"

const int MAX_BOUND_OF_SET = 100000000;
const int MIN_BOUND_OF_SET = 1; 


bool IsItCorrectArgument(const string& inputString, int& upperBound)
{
	try
	{
		upperBound = std::stoi(inputString);
	}
	catch (const exception&)
	{
		return false;
	}
	if ((upperBound < MIN_BOUND_OF_SET) || (upperBound > MAX_BOUND_OF_SET))
	{
		return false;
	}
	return true;
}

bool ParseArgs(int argc, char* argv[], int& upperBound)
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: GeneratePrimeNumbers.exe <upper bound number>" << endl;
		return false;
	}
	if (!IsItCorrectArgument(argv[1], upperBound))
	{
		cout << "Invalid upper bound number" << endl;
		cout << "Use a number between 1 and 100000000" << endl;
		return false;
	}
	return true;
}

vector<bool> GetSieve(int upperBound)
{
	vector<bool> isPrimeNum(upperBound + 1, true);
	for (size_t i = 2; i * i < isPrimeNum.size(); i++)
	{
		if (isPrimeNum[i])
		{
			for (size_t j = i * i; j < isPrimeNum.size(); j += i)
			{
				isPrimeNum[j] = false;
			}
		}
	}
	return isPrimeNum;
}

set<int> GetPrimeNumbersSet(int upperBound)
{
	vector<bool> isPrimeNum = GetSieve(upperBound);
	set<int> primeNumbers;
	for (size_t i = 2; i < isPrimeNum.size(); i++)
	{
		if (isPrimeNum[i])
		{
			primeNumbers.insert(i);
		}
	}
	return primeNumbers;
}

