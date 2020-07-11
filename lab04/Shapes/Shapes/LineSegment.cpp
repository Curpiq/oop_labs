#include "stdafx.h"
#include "LineSegment.h"

CLineSegment::CLineSegment(CPoint const& startPoint, CPoint const& endPoint, uint32_t outlineColor)
{
	this->m_startPoint = startPoint;
	this->m_endPoint = endPoint;
	this->m_outlineColor = outlineColor;
}

double CLineSegment::GetArea()const
{
	return 0;
}

double CLineSegment::GetPerimeter()const
{
	return sqrt(pow((m_startPoint.x - m_endPoint.x), 2) + pow((m_startPoint.y - m_endPoint.y), 2));
}

std::string CLineSegment::ToString() const
{
	std::ostringstream ss;
	ss << "Start point: " << 
		"(" << m_startPoint.x << ", " << m_startPoint.y << ")\n" <<
		"End point: " << "(" << m_endPoint.x << ", " << m_endPoint.y << ")\n" <<
		"Outline color: " << std::hex << m_outlineColor << "\n";
	return ss.str();
}

uint32_t CLineSegment::GetOutlineColor()const
{
	return m_outlineColor;
}

//CPoint CLineSegment::GetStartPoint()const
//{
//	m_startPoint;
//}
//
//CPoint CLineSegment::GetEndPoint()const
//{
//	return m_endPoint;
//}

