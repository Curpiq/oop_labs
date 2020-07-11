#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Complex/Complex.h"

CComplex a(2, 3);
CComplex b(7, 1);

TEST_CASE("Returns the real part of a complex number")
{
	CHECK(a.Re() == 2);
	CHECK(b.Re() == 7);
}

TEST_CASE("Returns the imaginary part of a complex number")
{
	CHECK(a.Im() == 3);
	CHECK(b.Im() == 1);
}

TEST_CASE("Returns the modulus of a complex number")
{
	CHECK(a.GetMagnitude() == sqrt(13));
	CHECK(b.GetMagnitude() == sqrt(50));
}

TEST_CASE("Returns the argument of a complex number")
{
	CHECK(a.GetArgument() == atan(1.5) * 180 / M_PI);
	CHECK(b.GetArgument() == atan2(1, 7) * 180 / M_PI);
}

TEST_CASE("Binary plus should sum complex numbers")
{
	CComplex c = a + b;
	CHECK(c.Re() == 9);
	CHECK(c.Im() == 4);
}

TEST_CASE("Binary plus should sum a complex number and a real number")
{
	CComplex c = a + 3;
	CHECK(c.Re() == 5);
	CHECK(c.Im() == 3);

	c = b + 5;
	CHECK(c.Re() == 12);
	CHECK(c.Im() == 1);
}

TEST_CASE("Binary minus should sub a complex number from a complex number")
{
	CComplex с = a - b;
	CHECK(с.Re() == -5);
	CHECK(с.Im() == 2);
}

TEST_CASE("Binary minus should sub a complex number from a real number")
{
	CComplex c = 8 - a;
	CHECK(c.Re() == 6);
	CHECK(c.Im() == -3);

	c = b - 3;
	CHECK(c.Re() == 4);
	CHECK(c.Im() == 1);
}

TEST_CASE("Multiplication should multiply complex numbers")
{
	CComplex C = a * b;
	CHECK(C.Re() == 11);
	CHECK(C.Im() == 23);
}

TEST_CASE("Multiplication should multiply a complex number and a real number")
{
	CComplex c = a * 4;
	CHECK(c.Re() == 8);
	CHECK(c.Im() == 12);

	c = 2 * b;
	CHECK(c.Re() == 14);
	CHECK(c.Im() == 2);
}

TEST_CASE("Division should divide a complex number by a complex number")
{
	CComplex c = a / b;
	CHECK(c.Re() == 0.34);
	CHECK(c.Im() == 0.38);
}

TEST_CASE("Mustn't divide a complex number by zero")
{
	CComplex c(0, 0);
	CHECK_THROWS(a / c);
	CHECK_THROWS(a / 0);
}

TEST_CASE("Division should get the quotient of a complex number and a real number")
{
	CComplex c = a / 2;
	CHECK(c.Re() == 1);
	CHECK(c.Im() == 1.5);

	c = 3 / b;
	CHECK(c.Re() == 0.42);
	CHECK(c.Im() == -0.06);
}

TEST_CASE("Unary plus should return a copy of a complex number")
{
	CComplex c = +a;
	CHECK(c.Re() == 2);
	CHECK(c.Im() == 3);
	c = +b;
	CHECK(c.Re() == 7);
	CHECK(c.Im() == 1);
}

TEST_CASE("Unary minus should return the opposite complex number")
{
	CComplex c = -a;
	CHECK(c.Re() == -2);
	CHECK(c.Im() == -3);
	c = -b;
	CHECK(c.Re() == -7);
	CHECK(c.Im() == -1);
}

TEST_CASE("+= must add to the complex number combining with the assignment")
{
	CComplex c(2, 3);
	c += b;
	CHECK(c.Re() == 9);
	CHECK(c.Im() == 4);

	c += 2;
	CHECK(c.Re() == 11);
	CHECK(c.Im() == 4);
}

TEST_CASE("-= must subtract from a complex number combining with the assignment")
{
	CComplex c(2, 3);
	c -= b;
	CHECK(c.Re() == -5);
	CHECK(c.Im() == 2);

	c -= 2;
	CHECK(c.Re() == -7);
	CHECK(c.Im() == 2);
}

TEST_CASE("*= must multiply a complex number combining with the assignment")
{
	CComplex c(2, 3);
	c *= b;
	CHECK(c.Re() == 11);
	CHECK(c.Im() == 23);

	c *= 3;
	CHECK(c.Re() == 33);
	CHECK(c.Im() == 69);
}

TEST_CASE("/= must divide a complex number combining with the assignment")
{
	CComplex c(2, 3);
	c /= b;
	CHECK(c.Re() == 0.34);
	CHECK(c.Im() == 0.38);

	c /= 2;
	CHECK(c.Re() == 0.17);
	CHECK(c.Im() == 0.19);
}
TEST_CASE("/= mustn't divide a complex number by zero")
{
	CComplex c(0, 0);
	CHECK_THROWS(a /= c);
	CHECK_THROWS(a /= 0);
}

TEST_CASE("== сompares a complex numbers")
{
	CComplex c(7, 1);
	CHECK(c == b);
	CHECK(!(c == a));
}

TEST_CASE("== сompares a complex number with a real number")
{
	CComplex c(7, 1);
	CHECK(!(c == 5));
}

TEST_CASE("!= must check complex numbers for the inequality")
{
	CHECK(a != b);

	CComplex c(2, 3);
	CHECK(!(c != a));
}

TEST_CASE("!= must check complex number and real number for the inequality")
{
	CComplex c(2, 3);
	CHECK(a != 2);
}

