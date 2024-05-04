#include "ShapeController.h"

void ShapeController::ReadShapes()
{
    std::string line;
    while (std::getline(m_in, line))
    {
        if (line.empty())
        {
            break;
        }

        m_shapeManager.ConstructShape(line);
    }
}

void ShapeController::ShapeMaxArea() const
{
    std::shared_ptr<IShape> shape = m_shapeManager.GetShapeWithMaxArea();

    if (shape != nullptr)
    {
        std::cout << "Shape with max area:\n" << shape->Info() << std::endl;
    }
}

void ShapeController::ShapeMinPerimeter() const
{
    std::shared_ptr<IShape> shape = m_shapeManager.GetShapeWithMinPerimeter();

    if (shape != nullptr)
    {
        std::cout << "Shape with min perimeter:\n" << shape->Info() << std::endl;
    }
}

void ShapeController::DrawShapes()
{
    m_shapeManager.RenderShapes();
}