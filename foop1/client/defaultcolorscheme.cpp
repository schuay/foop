#include "defaultcolorscheme.h"

QColor DefaultColorScheme::colorForPriority(Snake::Priority priority) const
{
    switch (priority) {
    case Snake::PRI_0:
        return Qt::red;
    case Snake::PRI_1:
        return Qt::green;
    case Snake::PRI_2:
        return Qt::blue;
    case Snake::PRI_3:
        return Qt::yellow;
    case Snake::PRI_4:
    default:
        return Qt::black;
    }
}
