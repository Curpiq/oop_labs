#include "Rectangle.h"
#include "stdafx.h"

CRectangle::CRectangle(CPoint const& topLeftCorner, double width, double height, uint32_t outlineColor, uint32_t fillColor)
{
	this->m_topLeftCorner = topLeftCorner;
	this->m_width = width;
	this->m_height = height;
	this->m_outlineColor = outlineColor;
	this->m_fillColor = fillColor;
}

double CRectangle::GetArea()const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter()const
{
	return 2 * (m_width + m_height);
}
std::string CRectangle::ToString()const
{
	std::ostringstream ss;
	ss << "Top left corner: " <<
		"(" << m_topLeftCorner.x << ", " << m_topLeftCorner.y << ")\n" <<
		"Width: " << m_width << "\n" <<
		"Height: " << m_height << "\n" <<
		"Outline color: " << std::hex << m_outlineColor << "\n" <<
		"Fill color: " << std::hex << m_fillColor << "\n";
	return ss.str();
}

uint32_t CRectangle::GetOutlineColor()const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor()const
{
	return m_fillColor;
}

