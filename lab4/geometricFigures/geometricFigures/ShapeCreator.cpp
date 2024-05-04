#pragma once
#include "ShapeCreator.h"

std::shared_ptr<IShape> ShapeCreator::CreateShape(const std::string& line)
{
    std::istringstream iss(line);
    std::string shapeName;
    iss >> shapeName;

    if (shapeName == CLineSegment::NAME)
    {
        return ShapeCreator::CreateCLineSegment(iss);
    }
    if (shapeName == CCircle::NAME)
    {
        return ShapeCreator::CreateCCircle(iss);
    }
    if (shapeName == CTriangle::NAME)
    {
        return ShapeCreator::CreateCTriangle(iss);
    }
    if (shapeName == CRectangle::NAME)
    {
        return ShapeCreator::CreateCRectangle(iss);
    }

    return nullptr;
}

std::shared_ptr<CLineSegment> ShapeCreator::CreateCLineSegment(std::istringstream& iss) {
    double startX, startY, endX, endY;

    if (!(iss >> startX >> endX >> startY >> endY))
    {
        throw std::invalid_argument("Invalid line segment coordinates");
    }
    CPoint startPoint = { startX, endX };
    CPoint endPoint = { startY, endY };

    uint32_t outlineColor;
    if (!(iss >> std::hex >> outlineColor))
    {
        throw std::invalid_argument("Invalid color values");
    }

    return std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}

std::shared_ptr<CRectangle> ShapeCreator::CreateCRectangle(std::istringstream& iss)
{
    double leftTopX, leftTopY, height, width;

    if (!(iss >> leftTopX >> leftTopY >> height >> width))
    {
        throw std::invalid_argument("Invalid rectangle coordinates");
    }
    CPoint leftTopPoint = CPoint(leftTopX, leftTopY);

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        throw std::invalid_argument("Invalid color values");
    }

    return std::make_shared<CRectangle>(leftTopPoint, height, width, outlineColor, fillColor);
}

std::shared_ptr<CTriangle> ShapeCreator::CreateCTriangle(std::istringstream& iss)
{
    double vertex1X, vertex1Y, vertex2X, vertex2Y, vertex3X, vertex3Y;

    if (!(iss >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y))
    {
        throw std::invalid_argument("Invalid number of triangle coordinates");
    }

    CPoint vertex1(vertex1X, vertex1Y);
    CPoint vertex2 = CPoint(vertex2X, vertex2Y);
    CPoint vertex3 = CPoint(vertex3X, vertex3Y);

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        throw std::invalid_argument("Invalid color values");
    }

    return std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

std::shared_ptr<CCircle> ShapeCreator::CreateCCircle(std::istringstream& iss)
{
    double centerX, centerY, radius;

    if (!(iss >> centerX >> centerY >> radius))
    {
        throw std::invalid_argument("Invalid circle parameters");
    }
    CPoint centerPoint = { centerX, centerY };

    uint32_t outlineColor, fillColor;
    if (!(iss >> std::hex >> outlineColor >> fillColor))
    {
        throw std::invalid_argument("Invalid color values");
    }

    return std::make_shared<CCircle>(centerPoint, radius, outlineColor, fillColor);
}