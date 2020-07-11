#include "Complex.h"

CComplex::CComplex(double real, double image)
{
	this->m_real = real;
	this->m_image = image;
}
double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(m_real * m_real + m_image * m_image);
}

double CComplex::GetArgument()const
{
	return atan2(m_image, m_real) * 180 / M_PI;
}

CComplex CComplex::operator+(const CComplex& num)const
{
	return CComplex(m_real + num.Re(), m_image + num.Im());;
}

CComplex CComplex::operator-(const CComplex& num) const
{
	return CComplex(m_real - num.Re(), m_image - num.Im());
}

CComplex CComplex::operator*(const CComplex& num) const
{
	double real = m_real * num.Re() - m_image * num.Im();
	double image = m_real * num.Im() + m_image * num.Re();
	return CComplex(real, image);
}

CComplex CComplex::operator/(const CComplex& num) const
{
	if (num.Re() == 0 && num.Im() == 0)
	{
		throw  std::invalid_argument("division by zero");
	}

	double real = (m_real * num.Re() + m_image * num.Im())/(pow(num.Re(), 2) + pow(num.Im(), 2));;
	double image = (m_image * num.Re() - m_real * num.Im())/ (pow(num.Re(), 2) + pow(num.Im(), 2));;
	return CComplex(real, image);
}

CComplex CComplex::operator+() const
{
	return *this;
}

CComplex CComplex::operator-() const
{
	return 0 - *this;
}

CComplex& CComplex::operator+=(const CComplex& num)
{
	m_real += num.m_real;
	m_image += num.m_image;
	return *this;
}

CComplex& CComplex::operator-=(const CComplex& num)
{
	m_real -= num.m_real;
	m_image -= num.m_image;
	return *this;
}

CComplex& CComplex::operator*=(const CComplex& num)
{
	*this = *this * num;
	return *this;
}

CComplex& CComplex::operator/=(const CComplex& num)
{
	*this = *this / num;
	return *this;
}

bool CComplex::operator==(const CComplex& num)const
{
	bool numbersAreEqual = (fabs(m_real - num.Re()) < DBL_EPSILON && fabs(m_image - num.Im()) < DBL_EPSILON);
	return numbersAreEqual;
}

bool CComplex::operator!=(const CComplex& num) const
{
	return !(*this == num);
}

CComplex operator+(const double a, const CComplex& b)
{
	return CComplex(a) + b;
}

CComplex operator-(const double a, const CComplex& b)
{
	return CComplex(a) - b;
}

CComplex operator*(const double a, const CComplex& b)
{
	return CComplex(a) * b;;
}

CComplex operator/(const double a, const CComplex& b)
{
	return CComplex(a) / b;
}

bool operator==(double a, const CComplex& b)
{
	return CComplex(a) == b;
}

bool operator!=(double a, const CComplex& b)
{
	return !(CComplex(a) == b);
}


