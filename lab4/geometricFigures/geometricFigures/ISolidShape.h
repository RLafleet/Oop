#ifndef ISOLIDSHAPE_H
#define ISOLIDSHAPE_H

#include "IShape.h"

//protected выяснить как работает и поменять на public
class ISolidShape : protected IShape
{
    virtual uint32_t GetFillColor() const = 0;
};


#endif //ISOLIDSHAPE_H