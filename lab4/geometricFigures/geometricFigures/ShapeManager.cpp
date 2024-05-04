#include "ShapeManager.h"
#include "IShape.h"
#include <memory>

void ShapeManager::ConstructShape(const std::string& line) 
{
    std::shared_ptr<IShape> shape = ShapeCreator::CreateShape(line);

    if (shape == nullptr) 
    {
        throw std::runtime_error("Unknown shape");
    }

    m_shapes.emplace_back(shape);
}

std::shared_ptr<IShape> ShapeManager::GetShapeWithMaxArea() const 
{
    if (m_shapes.empty()) 
    {
        return nullptr;
    }

    auto maxAreaShape = *std::max_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& first, const auto& second) { 
            return first->GetArea() < second->GetArea(); 
        });

    return maxAreaShape;
}

std::shared_ptr<IShape> ShapeManager::GetShapeWithMinPerimeter() const 
{
    if (m_shapes.empty()) 
    {
        return nullptr;
    }

    auto minPerimeterShape = *std::min_element(m_shapes.begin(), m_shapes.end(),
        [](const auto& first, const auto& second) 
        {
            return first->GetPerimeter() < second->GetPerimeter();
        });

    return minPerimeterShape;
}

void ShapeManager::RenderShapes()
{
    auto window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW),
        STANDARD_WINDOW_NAME);
    m_canvas = std::make_shared<CCanvas>(window);

    while (window->isOpen())
    {
        sf::Event event{};
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window->close();
            }
        }
        window->clear(sf::Color::White);

        for (auto const& shape : m_shapes)
        {
            shape->Draw(m_canvas);
        }
        window->display();
    }
}