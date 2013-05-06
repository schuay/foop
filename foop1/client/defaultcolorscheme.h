#ifndef DEFAULTCOLORSCHEME_H
#define DEFAULTCOLORSCHEME_H

#include "colorscheme.h"

/**
 * @brief The DefaultColorScheme class
 * Handles the priority/color-association
 */

class DefaultColorScheme : public ColorScheme
{
public:
    /**
     * @brief colorForPriority assigns the color
     * to the priority
     * @param priority of the snake
     * @return color-code
     */
    QColor colorForPriority(Snake::Priority priority) const;
};

#endif // DEFAULTCOLORSCHEME_H
