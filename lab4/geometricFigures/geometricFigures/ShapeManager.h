#ifndef INC_1_2_SHAPEMANAGER_H
#define INC_1_2_SHAPEMANAGER_H

#include "IShape.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "ShapeCreator.h"

class ShapeManager
{
public:
	void ConstructShape(const std::string& str);

	std::shared_ptr<IShape>GetShapeMaxSize() const;

	std::shared_ptr<IShape>GetShapeMinPerimetr() const;

private:
	std::vector<std::shared_ptr<ISshape>> m_shapes = {};

};

#endif //INC_1_2_SHAPEMANAGER_H