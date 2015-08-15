#ifndef GAME_H
#define GAME_H

#include "NonCopyable.h"

namespace snake
{
    constexpr unsigned char AREA_WIDTH  = 40;
    constexpr unsigned char AREA_HEIGHT = 18;

    class Snake;
    class Game final : private NonCopyable
    {
        struct
        {
            struct
            {
                unsigned char x, y;
            } food;

            Snake* snake;
        } area;

        struct
        {
            signed char x, y;
        } snakeDisplacement{-1, 0};

        bool running = true;

        void generateFood();
        void update();
        void draw() const;

        bool isSnakeCrashed() const;
        bool isSnakeEat() const;

    public:
        Game();
        ~Game();

        void run();
    };
}

#endif
