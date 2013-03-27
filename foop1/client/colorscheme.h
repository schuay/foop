#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QColor>

#include "snake.h"

class ColorScheme
{
public:
    virtual ~ColorScheme() { }
    virtual QColor colorForPriority(Snake::Priority priority) const = 0;
};

#endif // COLORSCHEME_H
