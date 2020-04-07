#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../Vector/VectorProcessor.h"

using namespace std;

bool ArraysAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

TEST_CASE("Make empty vector from empty vector")
{
	vector<double> emptyVector;
	ProcessVector(emptyVector);
	CHECK(emptyVector.empty());
}

TEST_CASE("Make the same vector from vector that min. element are 0")
{
	vector<double> numbers = { 0, 1, 5 };
	vector<double> expected = numbers;
	ProcessVector(numbers);
	CHECK(ArraysAreEqual(numbers, expected));
}

TEST_CASE("Make the same vector from vector that min. element and max. element are 0")
{
	vector<double> numbers = { 0 };
	vector<double> expected = numbers;
	ProcessVector(numbers);
	CHECK(ArraysAreEqual(numbers, expected));
}

TEST_CASE("Make a vector, each element of which is multiplied by maximum element and divided by minimum element of the original vector")
{
	vector<double> numbers = { 4, 3, 2, 10 };
	ProcessVector(numbers);
	vector<double> expected = { 20, 15, 10, 50 };
	CHECK(ArraysAreEqual(numbers, expected));
}