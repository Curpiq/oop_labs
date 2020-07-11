#include "stdafx.h"
#include "ShapeHandler.h"
#include "boost/algorithm/string.hpp"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

using namespace std;
using namespace std::placeholders;

CShapeHandler::CShapeHandler(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
				{ "LineSegment", bind(&CShapeHandler::CreateLineSegment, this, _1) },
				{ "Rectangle", bind(&CShapeHandler::CreateRectangle, this, _1) },
				{ "Triangle", bind(&CShapeHandler::CreateTriangle, this, _1) },
				{ "Circle", bind(&CShapeHandler::CreateCircle, this, _1) },
		})
{
}

bool CShapeHandler::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream ss(commandLine);
	if (cin.eof())
	{
		return true;
	}
	string action;
	ss >> action;
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(ss);
	}
	return false;
}


bool IsColor(const string& line)
{
	uint32_t color;
	try
	{
		color = stoul(line, 0, 16);
	}
	catch (const exception&)
	{
		return false;
	}
	return true;
}

bool IsNumber(const string& line)
{
	double number;
	try
	{
		number = stod(line);
	}
	catch (const exception&)
	{
		return false;
	}
	return true;
}

bool AreCorrectParams(const vector<string>& params, size_t colorCheck)
{
	for (size_t i = 0; i < params.size(); i++)
	{
		if (i < colorCheck)
		{
			if (!IsNumber(params[i]))
			{
				return false;
			}
		}
		else
		{
			if (!IsColor(params[i]))
			{
				return false;
			}
		}
	}
}

void CShapeHandler::PrintShapeWithMaxArea()const
{
	if (m_shapesList.empty())
	{
		cout << "Empty list of shapes" << endl;
		return;
	}
	auto shape = std::max_element(m_shapesList.begin(), m_shapesList.end(), [](const auto& shape1, const auto& shape2) {
		return shape1->GetArea() < shape2->GetArea();
		});
	cout << (*shape)->ToString() << endl;
}

void CShapeHandler::PrintShapeWithMinPerimeter()const
{
	if (m_shapesList.empty())
	{
		cout << "Empty list of shapes" << endl;
		return;
	}
	auto shape = min_element(m_shapesList.begin(), m_shapesList.end(), [](const auto& shape1, const auto& shape2) {
		return shape1->GetPerimeter() < shape2->GetPerimeter();
		});
	cout << (*shape)->ToString() << endl;
}

bool CShapeHandler::CreateLineSegment(istream& args)
{
	string command;
	vector<string> params;

	getline(args, command);
	boost::algorithm::trim(command);
	boost::split(params, command, boost::algorithm::is_any_of(" "));
	if (params.size() != 5 || !AreCorrectParams(params, 4))
	{
		m_output << "Invalid command!" << endl;
		return true;
	}
	CPoint startPoint = { stod(params[0]), stod(params[1]) };
	CPoint endPoint = { stod(params[2]), stod(params[3]) };
	uint32_t outlineColor = stoul(params[4], 0, 16);
	m_shapesList.push_back(make_shared<CLineSegment>(startPoint, endPoint, outlineColor));
	return true;
}

bool CShapeHandler::CreateRectangle(istream& args)
{
	string command;
	vector<string> params;
	getline(args, command);
	boost::algorithm::trim(command);
	boost::split(params, command, boost::algorithm::is_any_of(" "));
	if (params.size() != 6 || !AreCorrectParams(params, 4))
	{
		m_output << "Invalid command!" << endl;
		return true;
	}
	CPoint topLeftCorner = { stod(params[0]), stod(params[1]) };
	double width = stod(params[2]);
	double height = stod(params[3]);
	uint32_t outlineColor = stoul(params[4], 0, 16);
	uint32_t fillColor = stoul(params[5], 0, 16);
	m_shapesList.push_back(make_shared<CRectangle>(topLeftCorner, width, height, outlineColor, fillColor));
	return true;
}

bool CShapeHandler::CreateTriangle(istream& args)
{
	string command;
	vector<string> params;
	getline(args, command);
	boost::algorithm::trim(command);
	boost::split(params, command, boost::algorithm::is_any_of(" "));
	if (params.size() != 8 || !AreCorrectParams(params, 6))
	{
		m_output << "Invalid command!" << endl;
		return true;
	}
	CPoint vertex1 = { stod(params[0]), stod(params[1]) };
	CPoint vertex2 = { stod(params[2]), stod(params[3]) };
	CPoint vertex3 = { stod(params[4]), stod(params[5]) };
	uint32_t outlineColor = stoul(params[6], 0, 16);
	uint32_t fillColor = stoul(params[7], 0, 16);
	m_shapesList.push_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
	return true;
}

bool CShapeHandler::CreateCircle(istream& args)
{
	string command;
	vector<string> params;
	getline(args, command);
	boost::algorithm::trim(command);
	boost::split(params, command, boost::algorithm::is_any_of(" "));
	if (params.size() != 5 || !AreCorrectParams(params, 3))
	{	
		m_output << "Invalid command!" << endl;
		return true;
	}
	CPoint center = { stod(params[0]), stod(params[1]) };
	double radius = stod(params[2]);
	uint32_t outlineColor = stoul(params[3], 0, 16);
	uint32_t fillColor = stoul(params[4], 0, 16);
	m_shapesList.push_back(make_shared<CCircle>(center, radius, outlineColor, fillColor));
	return true;
}

