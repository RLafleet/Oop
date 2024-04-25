#ifndef INC_1_2_SHAPEMANAGER_H
#define INC_1_2_SHAPEMANAGER_H

#include "../Shape/IShape.h"
#include "../Shape/CLineSegment/CLineSegment.h"
#include "../Shape/CRectangle/CRectangle.h"
#include "../Shape/CCircle/CCircle.h"
#include "../Shape/CTriangle/CTriangle.h"
#include "../Factory/ShapeFactory.h"

class ShapeManager
{
public:
	void ConstructShape(const std::string str);

	std::shared_ptr<IShape>GetShapeMaxSize() const;

	std::shared_ptr<IShape>GetShapeMinPerimetr() const;

private:
	std::vector<std::shared_ptr<ISshape>> m_shapes = {};

};

#endif //INC_1_2_SHAPEMANAGER_H