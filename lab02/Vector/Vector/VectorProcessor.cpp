#include "stdafx.h"
#include "VectorProcessor.h"

using namespace std;
void ProcessVector(vector<double>& numbers)
{
	if (numbers.size() == 0)
	{
		return;
	}
	double maxElement = *max_element(numbers.begin(), numbers.end());
	double minElement = *min_element(numbers.begin(), numbers.end());
	for (vector<double>::iterator i = numbers.begin(); i != numbers.end(); i++)
	{
		*i = *i * maxElement / minElement;
	}
}