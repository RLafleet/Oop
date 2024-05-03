#pragma once
#include "ICanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(std::shared_ptr<ICanvas> canvas) = 0;
};