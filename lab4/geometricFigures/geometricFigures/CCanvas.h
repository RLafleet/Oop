#pragma once
#include <utility>

#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(std::shared_ptr<sf::RenderWindow> window) : m_window(std::move(window)) {};

	void DrawBorder();

	void FillPolygon();

	void DrawLine();

	void FillCircle();

private:
	std::shared_ptr<sf::RenderWindow> m_window;
};