#ifndef ISHAPE_H
#define ISHAPE_H

#include "utils.h"
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable 
{
public:
    virtual uint32_t GetOutlineColor() const = 0;

    virtual ~IShape() = default;

    virtual double GetArea() const = 0;

    virtual double GetPerimeter() const = 0;

    //Все методы чисто виртуальные. Ввести промежуточный класс shape и наследоваться от него
    virtual std::string Info() const
    {
        std::stringstream ss;
        ss << "Perimeter: " << GetPerimeter() << std::endl;
        ss << "Area: " << GetArea() << std::endl;
        ss << "OutlineColor: " << std::hex << std::setw(6) << std::setfill('0') << GetOutlineColor() << std::endl;
        return ss.str();
    };

};


#endif //ISHAPE_H