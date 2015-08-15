#ifndef SNAKE_H
#define SNAKE_H

#include "NonCopyable.h"

namespace snake
{
    constexpr unsigned char MAX_SNAKE_LENGTH = 0xFF;

    class Snake final : private NonCopyable
    {
        struct Element
        {
            unsigned char x, y;
        };

        Element* elements[MAX_SNAKE_LENGTH];
        unsigned char length;

    public:
        Snake(unsigned char x, unsigned char y, unsigned char length = 3);
        ~Snake();

        void increase();
        void move(char x, char y) const;
        void draw() const;

        unsigned char getX() const {return (*elements)->x;}
        unsigned char getY() const {return (*elements)->y;}
        unsigned char getLength() const {return length;}

        bool isCrashed() const;
    };
}

#endif
