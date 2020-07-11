#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3, uint32_t outlineColor, uint32_t fillColor)
{
	this->m_vertex1 = vertex1;
	this->m_vertex2 = vertex2;
	this->m_vertex3 = vertex3;
	this->m_outlineColor = outlineColor;
	this->m_fillColor = fillColor;
}

double CTriangle::GetSide(CPoint const& point1, CPoint const& point2)
{
	double side = sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
	return side;
}

double CTriangle::GetPerimeter()const
{
	double side1 = GetSide(m_vertex1, m_vertex2);
	double side2 = GetSide(m_vertex2, m_vertex3);
	double side3 = GetSide(m_vertex1, m_vertex3);
	return side1 + side2 + side3;
}

double CTriangle::GetArea()const
{
	double p = GetPerimeter()/2;
	return sqrt(p * (p - GetSide(m_vertex1, m_vertex2)) * (p - GetSide(m_vertex1, m_vertex3)) * (p - GetSide(m_vertex2, m_vertex3)));
}

std::string CTriangle::ToString()const
{
	std::ostringstream ss;
	ss << "Vertex1: " <<
	    "(" << m_vertex1.x << ", " << m_vertex1.y << ")\n" <<
		"Vertex2: " << "(" << m_vertex2.x << ", " << m_vertex2.y << ")\n" <<
		"Vertex3: " << "(" << m_vertex3.x << ", " << m_vertex3.y << " )\n" <<
		"Outline color: " << std::hex << m_outlineColor << "\n" <<
		"Fill color: " << std::hex << m_fillColor << "\n";
	return ss.str();
}

uint32_t CTriangle::GetOutlineColor()const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor()const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1()const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2()const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3()const
{
	return m_vertex3;
}