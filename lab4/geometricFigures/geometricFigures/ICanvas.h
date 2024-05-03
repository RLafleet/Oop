#pragma once
#include "CPoint.h"
class ICanvas
{
public:
	virtual void DrawBorder(Cpoint pointFrom, Cpoint pointTo, uint32_t borderColor) = 0;
	
	virtual void FillShape(std::vector<Cpoint>, uint32_t borderColor, uint32_t fillColor) = 0;
	
	virtual void DrawCircle(CPoint center, double radius, uint32_t borderColor) = 0;
	
	virtual void FillCircleCPoint center, double radius, uint32_t fillColor) = 0;

};