#include "stdafx.h"
#include "VectorProcessor.h"

using namespace std;

void ProcessVector(vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}
	auto result = minmax_element(numbers.begin(), numbers.end());
	double min = *result.first;
	double max = *result.second;
	if (isnan(max / min) || isinf(max / min))
	{
		return;
	}
	transform(numbers.begin(), numbers.end(), numbers.begin(),
		[&min, &max](double x) -> double { return x * max / min; });
}