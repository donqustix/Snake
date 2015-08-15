#include "Snake.h"

#include <ncurses.h>

using snake::Snake;

Snake::Snake(unsigned char x, unsigned char y, unsigned char length) :
    length{length} 
{
    for (unsigned char i = 0; i < length; ++i)
        *(elements + i) = new Element{static_cast<unsigned char>(x + i), y};
}

Snake::~Snake()
{
    for (unsigned char i = 0; i < length; ++i)
        delete *(elements + i);
}

void Snake::increase()
{
    if (length >= MAX_SNAKE_LENGTH)
        return;

    *(elements + length) = new Element{(*(elements + length - 1))->x,
                                       (*(elements + length - 1))->y};
    ++length;
}

void Snake::move(char x, char y) const
{
    for (unsigned i = length - 1; i != 0; --i)
    {
        (*(elements + i))->x = (*(elements + i - 1))->x;
        (*(elements + i))->y = (*(elements + i - 1))->y;
    }
    (*elements)->x += x;
    (*elements)->y += y;
}

void Snake::draw() const
{
    for (unsigned char i = 0; i < length; ++i)
        mvaddch((*(elements + i))->y, (*(elements + i))->x, '#');
}

bool Snake::isCrashed() const
{
    for (unsigned char i = 1; i < length; ++i)
    {
        if ((*elements)->x == (*(elements + i))->x &&
            (*elements)->y == (*(elements + i))->y)
            return true;
    }

    return false;
}

