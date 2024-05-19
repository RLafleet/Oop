#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../geometricFigures/CPoint.h"
#include "../geometricFigures/CLineSegment.h"
#include "../geometricFigures/CCircle.h"
#include "../geometricFigures/CRectangle.h"
#include "../geometricFigures/CTriangle.h"
#include "../geometricFigures/ShapeManager.h"

const uint32_t OUTLINE_COLOR = 0xFFFFFF;
const uint32_t FILL_COLOR = 0x000000;

TEST_CASE("Invalid identifier error")
{
    double expectedPerimeter = 5;
    double expectedArea = 0;

    CPoint startPoint = { 0, 0 };
    CPoint endPoint = { 3, 4 };

    CLineSegment line(startPoint, endPoint, 0x000000);

    REQUIRE(line.GetStartPoint().m_x == startPoint.m_x);
    REQUIRE(line.GetStartPoint().m_y == startPoint.m_y);
    REQUIRE(line.GetEndPoint().m_x == endPoint.m_x);
    REQUIRE(line.GetEndPoint().m_y == endPoint.m_y);

    REQUIRE(line.GetOutlineColor() == 0x000000);

    REQUIRE(line.GetArea() == expectedArea);
    REQUIRE(line.GetPerimeter() == expectedPerimeter);
}

TEST_CASE("valid test circle")
{
	CPoint center = { 3, 4 };
	double radius = 3;

	CCircle circle(center, radius, OUTLINE_COLOR, FILL_COLOR);

	REQUIRE(circle.GetCenter().m_x == center.m_x);
	REQUIRE(circle.GetCenter().m_y == center.m_y);
	REQUIRE(circle.GetRadius() == radius);

	REQUIRE(circle.GetOutlineColor() == OUTLINE_COLOR);
	REQUIRE(circle.GetFillColor() == FILL_COLOR);
}

TEST_CASE("not valid circle")
{
	CPoint center = { 3, 4 };
	double radius = 0;

	REQUIRE_THROWS_AS(CCircle(center, radius, OUTLINE_COLOR, FILL_COLOR), std::invalid_argument);

	radius = -3;

	REQUIRE_THROWS_AS(CCircle(center, radius, OUTLINE_COLOR, FILL_COLOR), std::invalid_argument);
}

TEST_CASE("valid tests rectangle")
{
	double expectedArea = 2;
	double expectedPerimeter = 6;
	double expectedRightBottomX = 5;
	double expectedLeftBottomX = 5;

	CPoint leftTop = { 3, 4 };
	double width = 2;
	double height = 1;

	CRectangle rectangle(leftTop, height, width, OUTLINE_COLOR, FILL_COLOR);

	REQUIRE(rectangle.GetLeftTop().m_x == leftTop.m_x);
	REQUIRE(rectangle.GetLeftTop().m_y == leftTop.m_y);
	REQUIRE(rectangle.GetRightBottom().m_x == expectedRightBottomX);
	REQUIRE(rectangle.GetRightBottom().m_y == expectedLeftBottomX);

	REQUIRE(rectangle.GetOutlineColor() == OUTLINE_COLOR);
	REQUIRE(rectangle.GetFillColor() == FILL_COLOR);

}

TEST_CASE("not valid rectangle")
{
	CPoint leftTop = { 3, 4 };
	double width = -2;
	double height = 1;

	REQUIRE_THROWS_AS(CRectangle(leftTop, height, width, OUTLINE_COLOR, FILL_COLOR), std::invalid_argument);

	width = 2;
	height = -1;

	REQUIRE_THROWS_AS(CRectangle(leftTop, height, width, OUTLINE_COLOR, FILL_COLOR), std::invalid_argument);

	width = 2;
	height = 0;

	REQUIRE_THROWS_AS(CRectangle(leftTop, height, width, OUTLINE_COLOR, FILL_COLOR), std::invalid_argument);

	width = 0;
	height = 1;

	REQUIRE_THROWS_AS(CRectangle(leftTop, height, width, OUTLINE_COLOR, FILL_COLOR), std::invalid_argument);
}

TEST_CASE("test triangle valid")
{
	double expectedArea = 6;
	double expectedPerimeter = 12;

	CPoint vertex1 = { 0, 0 };
	CPoint vertex2 = { 0, 3 };
	CPoint vertex3 = { 4, 0 };

	CTriangle triangle(vertex1, vertex2, vertex3, OUTLINE_COLOR, FILL_COLOR);

	REQUIRE(triangle.GetVertex1().m_x == vertex1.m_x);
	REQUIRE(triangle.GetVertex1().m_y == vertex1.m_y);
	REQUIRE(triangle.GetVertex2().m_x == vertex2.m_x);
	REQUIRE(triangle.GetVertex2().m_y == vertex2.m_y);
	REQUIRE(triangle.GetVertex3().m_x == vertex3.m_x);
	REQUIRE(triangle.GetVertex3().m_y == vertex3.m_y);

	REQUIRE(triangle.GetOutlineColor() == OUTLINE_COLOR);
	REQUIRE(triangle.GetFillColor() == FILL_COLOR);

}

TEST_CASE("test not valid vertix")
{
	CPoint vertex1 = { 0, 0 };
	CPoint vertex2 = { 1, 1 };
	CPoint vertex3 = { 2, 2 };

	REQUIRE_THROWS_AS(CTriangle(vertex1, vertex2, vertex3, OUTLINE_COLOR, FILL_COLOR), std::invalid_argument);
}

TEST_CASE("test get perimetr and area")
{
	std::string expectedMaxArea = "Name: circle\n"
								  "Perimeter: 18.8495\n"
								  "Area: 28.2743\n"
								  "OutlineColor: ffffff\n"
								  "FillColor: 000000\n"
								  "Center: (3, 4)\n"
								  "Radius: 3\n";

	std::string expectedMinPerimeter = "Name: line\n"
									   "Perimeter: 5\n"
									   "Area: 0\n"
									   "OutlineColor: ffffff\n"
									   "StartPoint: (0, 0)\n"
									   "EndPoint: (3, 4)\n";

	ShapeManager shapeManager;

	shapeManager.ConstructShape("line 0 0 3 4 0xFFFFFF");
	shapeManager.ConstructShape("circle 3 4 3 0xFFFFFF 0x000000");
	shapeManager.ConstructShape("rectangle 3 4 2 1 0xFFFFFF 0x000000");
	shapeManager.ConstructShape("triangle 0 0 0 3 4 0 0xFFFFFF 0x000000");

	REQUIRE(shapeManager.GetShapeWithMaxArea()->Info() == expectedMaxArea);
	REQUIRE(shapeManager.GetShapeWithMinPerimeter()->Info() == expectedMinPerimeter);
}

