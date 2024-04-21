#pragma once
#ifndef ISHAPE_H
#define ISHAPE_H	
#include "stdUtils.h"


class IShape 
{
public:
	virtual double GetArea() const = 0;

	virtual double GetPerimeter() const = 0;

	virtual std::string ToString() const = 0;

	virtual uint32_t GetOutlineColor() const = 0;

	virtual ~IShape() = default;


}

#endif // ISHAPE_H