#ifndef ICANVAS_H
#define ICANVAS_H

#include "CPoint.h"
#include "utils.h"

// Выяснить чего здесь не хватает
class ICanvas
{
public:
    virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;

    virtual void FillPolygon(std::vector<CPoint>, uint32_t lineColor, uint32_t fillColor) = 0;

    virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;

    virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;
};

#endif //ICANVAS_H