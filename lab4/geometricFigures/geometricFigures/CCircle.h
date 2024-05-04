#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "ISolidShape.h"
#include "CPoint.h"

class CCircle : public ISolidShape
{
public:
    static constexpr const char* NAME = "circle";

    CCircle(CPoint centerPoint, double radius, uint32_t outlineColor, uint32_t fillColor)
        : m_centerPoint(centerPoint),
        m_radius(radius),
        m_outlineColor(outlineColor),
        m_fillColor(fillColor)
    {
        if (radius <= 0)
        {
            throw std::invalid_argument("Invalid radius");
        }
    }

    double GetArea() const override;

    double GetPerimeter() const override;

    std::string Info() const override;

    uint32_t GetOutlineColor() const override;

    uint32_t GetFillColor() const override;

    CPoint GetCenter() const;

    double GetRadius() const;

    void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
    CPoint m_centerPoint;
    double m_radius;
    uint32_t m_outlineColor;
    uint32_t m_fillColor;
};


#endif //CCIRCLE_H