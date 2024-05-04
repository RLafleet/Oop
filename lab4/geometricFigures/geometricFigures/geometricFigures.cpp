#include "ShapeController.h"
#include "ShapeManager.h"



int main(int argc, char* argv[])
{
    try
    {
        ShapeManager shapeService;
        ShapeController shapeController = 
        { 
            std::cin, 
            std::cout, 
            shapeService 
        };

        shapeController.ReadShapes();
        shapeController.ShapeMaxArea();
        shapeController.ShapeMinPerimeter();
        shapeController.DrawShapes();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}