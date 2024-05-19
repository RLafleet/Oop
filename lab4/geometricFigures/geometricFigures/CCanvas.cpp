#include "CCanvas.h"

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(static_cast<float>(from.m_x), static_cast<float>(from.m_y));
	line[1].position = sf::Vector2f(static_cast<float>(to.m_x), static_cast<float>(to.m_y));
	line[0].color = sf::Color(lineColor);
	line[1].color = sf::Color(lineColor);

	m_window->draw(line);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t lineColor, uint32_t fillColor)
{
	if (points.empty())
	{
		return;
	}

	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i,
			sf::Vector2f(static_cast<float>(points[i].m_x),
				static_cast<float>(points[i].m_y)));
	}

	polygon.setOutlineColor(sf::Color(lineColor));
	polygon.setFillColor(sf::Color(fillColor));

	m_window->draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(static_cast<float>(center.m_x), static_cast<float>(center.m_y));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color(lineColor));
	circle.setOutlineThickness(2);

	m_window->draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(static_cast<float>(center.m_x), static_cast<float>(center.m_y));
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineColor(sf::Color::Transparent);

	m_window->draw(circle);
}