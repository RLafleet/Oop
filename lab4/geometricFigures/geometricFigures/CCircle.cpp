#include "CCircle.h"

static constexpr double PI = 3.14159; 
//std::numbers::pi

double CCircle::GetArea() const
{
    return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * PI * m_radius;
}

std::string CCircle::Info() const
{
    std::stringstream ss;
    ss << "Name: " << NAME << std::endl;
    ss << IShape::Info();
    ss << "FillColor: " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << std::endl;
    ss << "Center: (" << m_centerPoint.m_x << ", " << m_centerPoint.m_y << ")" << std::endl;
    ss << "Radius: " << m_radius << std::endl;
    return ss.str();
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
    return m_centerPoint;
}

double CCircle::GetRadius() const
{
    return m_radius;
}

void CCircle::Draw(std::shared_ptr<ICanvas> canvas)
{
    canvas->DrawCircle(m_centerPoint, m_radius, m_outlineColor);
    canvas->FillCircle(m_centerPoint, m_radius, m_fillColor);
}