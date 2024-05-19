#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	static constexpr const char* NAME = "rectangle";

	CRectangle(CPoint leftTopPoint, double height, double width, uint32_t outlineColor, uint32_t fillColor)
		: m_leftTopPoint(leftTopPoint)
		, m_height(height)
		, m_width(width)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
		if (height <= 0 || width <= 0)
		{
			throw std::invalid_argument("Invalid rectangle sizes");
		}
	}

	double GetArea() const override;

	double GetPerimeter() const override;

	std::string Info() const override;

	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetLeftTop() const;

	CPoint GetRightBottom() const;

	double GetHeight() const;

	double GetWidth() const;

	void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
	CPoint m_leftTopPoint;
	double m_height;
	double m_width;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};

#endif // CRECTANGLE_H