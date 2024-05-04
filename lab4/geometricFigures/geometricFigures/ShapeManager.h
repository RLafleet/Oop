#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include "utils.h"
#include "IShape.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "ShapeCreator.h"
#include "CCanvas.h"

class ShapeManager
{
public:
    void ConstructShape(const std::string& line);

    std::shared_ptr<IShape> GetShapeWithMaxArea() const;

    std::shared_ptr<IShape> GetShapeWithMinPerimeter() const;

    void RenderShapes();

private:
    const int WIDTH_WINDOW = 1280;
    const int HEIGHT_WINDOW = 720;
    const std::string STANDARD_WINDOW_NAME = "Window";

    std::vector<std::shared_ptr<IShape>> m_shapes = {};
    std::shared_ptr<CCanvas> m_canvas;
};


#endif //SHAPEMANAGER_H