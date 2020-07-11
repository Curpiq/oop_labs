#pragma once

#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint const& topLeftCorner, double width, double height, uint32_t outlineColor, uint32_t fillColor);
	double GetArea()const override;
	double GetPerimeter()const override;
	std::string ToString()const override;
	uint32_t GetOutlineColor()const override;
	uint32_t GetFillColor()const override;
	CPoint GetLeftTop()const;
	CPoint GetRightBottom()const;
	double GetWidth()const;
	double GetHeight()const;
private:
	double m_width, m_height;
	CPoint m_topLeftCorner;
	uint32_t m_outlineColor, m_fillColor;
};