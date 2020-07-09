#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../GeneratePrimeNumbers/GeneratePrimeNumbers.h"

bool AreEqual(const set<int>& x, const set<int>& y)
{
	return x == y;
}

TEST_CASE("Check the argument")
{
	int upperBound;
	REQUIRE(IsItCorrectArgument("", upperBound) == false);
	REQUIRE(IsItCorrectArgument("A", upperBound) == false);
	REQUIRE(IsItCorrectArgument("0", upperBound) == false);
	REQUIRE(IsItCorrectArgument("-1", upperBound) == false);
	REQUIRE(IsItCorrectArgument("100000001", upperBound) == false);
	REQUIRE(IsItCorrectArgument("1", upperBound) == true);
	REQUIRE(IsItCorrectArgument("100000000", upperBound) == true);
}

TEST_CASE("Check the prime numbers set")
{

	REQUIRE(AreEqual(GetPrimeNumbersSet(1), {}));
	REQUIRE(AreEqual(GetPrimeNumbersSet(3), { 2, 3 }));
	REQUIRE(AreEqual(GetPrimeNumbersSet(10), { 2, 3, 5, 7 }));
}

TEST_CASE("Check the number of elements of the prime numbers set")
{
	set<int> primeNumbers = GetPrimeNumbersSet(100000000);
	REQUIRE(primeNumbers.size() == 5761455);
}

