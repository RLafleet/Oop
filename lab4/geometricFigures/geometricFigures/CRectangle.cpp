#include "CRectangle.h"

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * m_width + 2 * m_height;
}

std::string CRectangle::Info() const
{
	std::stringstream ss;
	ss << "Name: " << NAME << std::endl;
	ss << IShape::Info();
	ss << "FillColor: " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << std::endl;
	ss << "LeftTop: (" << m_leftTopPoint.m_x << ", " << m_leftTopPoint.m_y << ")" << std::endl;
	ss << "RightBottom: (" << CRectangle::GetRightBottom().m_x << ", " << CRectangle::GetRightBottom().m_y << ")" << std::endl;
	ss << "Height: " << m_height << std::endl;
	ss << "Width: " << m_width << std::endl;
	return ss.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopPoint;
}

CPoint CRectangle::GetRightBottom() const
{
	return { m_leftTopPoint.m_x + m_width, m_leftTopPoint.m_y + m_height };
}

double CRectangle::GetHeight() const
{
	return m_height;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

void CRectangle::Draw(std::shared_ptr<ICanvas> canvas)
{
	CPoint rightTop(GetRightBottom().m_x, m_leftTopPoint.m_y);
	CPoint leftBottom(m_leftTopPoint.m_x, GetRightBottom().m_y);

	canvas->FillPolygon(
		{ m_leftTopPoint,
			rightTop,
			GetRightBottom(),
			leftBottom },
		m_outlineColor,
		m_fillColor);

	canvas->DrawLine(m_leftTopPoint, rightTop, m_outlineColor);
	canvas->DrawLine(rightTop, GetRightBottom(), m_outlineColor);
	canvas->DrawLine(GetRightBottom(), leftBottom, m_outlineColor);
	canvas->DrawLine(leftBottom, m_leftTopPoint, m_outlineColor);
}