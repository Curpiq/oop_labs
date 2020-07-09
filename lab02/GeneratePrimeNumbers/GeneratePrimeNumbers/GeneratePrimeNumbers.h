#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

bool ParseArgs(int argc, char* argv[], int& upperBound);
bool IsItCorrectArgument(const string& inputString, int& upperBound);
vector<bool> GetSieve(int upperBound);
set<int> GetPrimeNumbersSet(int upperBound);
