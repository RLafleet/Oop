#ifndef ICANVASDRAWABLE_H
#define ICANVASDRAWABLE_H

#include "ICanvas.h"

class ICanvasDrawable
{
public:
    // shared_ptr неправильно. Просто ссылка
    // Найти ответ на вопрос что произойдет с текущим объектом когда нарием его на холсте
    virtual void Draw(std::shared_ptr<ICanvas> canvas) = 0;
};

#endif //ICANVASDRAWABLE_H