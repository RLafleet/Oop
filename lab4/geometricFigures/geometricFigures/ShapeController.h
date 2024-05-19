#ifndef SHAPECONTROLLER_H
#define SHAPECONTROLLER_H

#include "ShapeManager.h"
#include "utils.h"

class ShapeController
{
public:
	ShapeController(std::istream& in, std::ostream& out, ShapeManager& shapeService)
		: m_in(in)
		, m_out(out)
		, m_shapeManager(shapeService)
	{
	}

	void ReadShapes();

	void ShapeMaxArea() const;

	void ShapeMinPerimeter() const;

	void DrawShapes();

private:
	std::istream& m_in;
	std::ostream& m_out;
	ShapeManager& m_shapeManager;
};

#endif // SHAPECONTROLLER_H