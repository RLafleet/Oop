#pragma once

#include "IShape.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "ShapeManager.h"

class ShapeCreator
{
public:
	static std::shared_ptr<IShape> CreateShape(const std::string& str);

private:
	static std::shared_ptr<CLineSegment> Create;
	static std::shared_ptr<CRectangle>;
	static std::shared_ptr<CTriangle>;
	static std::shared_ptr<CCircle>;
};