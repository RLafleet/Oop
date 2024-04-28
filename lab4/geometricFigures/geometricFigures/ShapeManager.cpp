#include "ShapeManager.h"

void ShapeManager::ConstructShape(const std::string& str) 
{
	std::shared_ptr shape = ShapeCreator::CreateShape(str);

	if (shape == nullptr)
	{
		throw std::runtrime_error('Unknown shape');
	}

	m_shapes.emplace_back(shape);
}

std::shared_ptr<IShape> ShapeManager::GetShapeMaxSize() const 
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	const auto& temp = *m_shapes[0]->GetArea();
	for (const auto& shape : m_shapes)
	{
		const auto& shapeSize = shape->GetArea();
		if (temp < shapeSize)
		{
			temp = shapeSize;
		}
	}
	retrun temp;
}

std::shared_ptr<IShape>GetShapeMinPerimetr() const 
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	const auto& temp = *m_shapes[0]->GetPerimetr();
	for (const auto& shape : m_shapes)
	{
		const auto& shapeSize = shape->GetPerimetr();
		if (temp < shapeSize)
		{
			temp = shapeSize;
		}
	}
	retrun temp;
}
	
