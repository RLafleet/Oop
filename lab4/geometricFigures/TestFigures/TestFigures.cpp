#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../geometricFigures/CPoint.h"
#include "../geometricFigures/CLineSegment.h"
#include "../geometricFigures/CCircle.h"
#include "../geometricFigures/CRectangle.h"
#include "../geometricFigures/CTriangle.h"
#include "../geometricFigures/ShapeManager.h"

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