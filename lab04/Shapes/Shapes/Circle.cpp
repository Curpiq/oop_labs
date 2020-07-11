#include "Circle.h"
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>

CCircle::CCircle(CPoint const& center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
	this->m_center = center;
	this->m_radius = radius;
	this->m_outlineColor = outlineColor;
	this->m_fillColor = fillColor;
}

double CCircle::GetArea()const
{
	return pow(m_radius, 2) * M_PI;
}

double CCircle::GetPerimeter()const
{
	return 2 * m_radius * M_PI;
}

std::string CCircle::ToString()const
{
	std::ostringstream ss;
	ss << "Center: " <<
		"(" << m_center.x << ", " <<m_center.y << ")\n" <<
		"Radius: " << m_radius << "\n" <<
		"Outline color: " << std::hex << m_outlineColor << "\n" <<
		"Fill color: " << std::hex << m_fillColor << "\n";
	return ss.str();
}

uint32_t CCircle::GetOutlineColor()const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor()const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter()const
{
	return m_center;
}

double CCircle::GetRadius()const
{
	return m_radius;
}

