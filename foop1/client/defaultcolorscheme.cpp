#include "defaultcolorscheme.h"

/**
 * @brief DefaultColorScheme::colorForPriority
 * Just a default color sheme for the game, with
 * red the lowest and yellow the highest priority,
 * takes the priority of the snake and returns the
 * assigned color-code
 * @param priority Priority of the Snake
 * @return Color-Code
 */

QColor DefaultColorScheme::colorForPriority(Snake::Priority priority) const
{
    //Assigns snake's priority to a color-code
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
