#ifndef DEFAULTCOLORSCHEME_H
#define DEFAULTCOLORSCHEME_H

#include "colorscheme.h"

class DefaultColorScheme : public ColorScheme
{
public:
    QColor colorForPriority(Snake::Priority priority) const;
};

#endif // DEFAULTCOLORSCHEME_H
