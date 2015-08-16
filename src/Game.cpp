#include "Game.h"
#include "Snake.h"

#include <ncurses.h>

#include <cstdlib>

using snake::Game;

Game::Game() :
    area{{static_cast<unsigned char>(1 + rand() % (AREA_WIDTH  - 1)),
          static_cast<unsigned char>(1 + rand() % (AREA_HEIGHT - 1))}, new Snake{10, 10}}
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

Game::~Game()
{
    endwin();
}

void Game::generateFood()
{
    while (true)
    {
        area.food.x = 1 + rand() % (AREA_WIDTH  - 1);
        area.food.y = 1 + rand() % (AREA_HEIGHT - 1);

        if (mvinch(area.food.y, area.food.x) != '#')
            return;
    }
}

void Game::update()
{
    timeout(1500 / area.snake->getLength());

    char ch = getch();

    switch (ch)
    {
        case 'w':
            if (snakeDisplacement.y == 1)
                break;

            snakeDisplacement.x =  0;
            snakeDisplacement.y = -1;
            break;
        case 's':
            if (snakeDisplacement.y == -1)
                break;

            snakeDisplacement.x = 0;
            snakeDisplacement.y = 1;
            break;
        case 'a':
            if (snakeDisplacement.x == 1)
                break;

            snakeDisplacement.x = -1;
            snakeDisplacement.y =  0;
            break;
        case 'd':
            if (snakeDisplacement.x == -1)
                break;

            snakeDisplacement.x = 1;
            snakeDisplacement.y = 0;
            break;
    }

    area.snake->move(snakeDisplacement.x, snakeDisplacement.y);

    running = !isSnakeCrashed();

    if (isSnakeEat())
    {
        area.snake->increase();
        generateFood();
    }
}

void Game::draw() const
{
    clear();

    mvaddch(0,                    0, ACS_ULCORNER);
    mvaddch(0,           AREA_WIDTH, ACS_URCORNER);
    mvaddch(AREA_HEIGHT,          0, ACS_LTEE);
    mvaddch(AREA_HEIGHT, AREA_WIDTH, ACS_RTEE);

    mvaddch(AREA_HEIGHT + 2,          0, ACS_LLCORNER);
    mvaddch(AREA_HEIGHT + 2, AREA_WIDTH, ACS_LRCORNER);

    mvaddch(AREA_HEIGHT + 1,          0, ACS_VLINE);
    mvaddch(AREA_HEIGHT + 1, AREA_WIDTH, ACS_VLINE);

    unsigned char i;
    for (i = 1; i < AREA_WIDTH; ++i)
    {
        mvaddch(0,               i, ACS_HLINE);
        mvaddch(AREA_HEIGHT,     i, ACS_HLINE);
        mvaddch(AREA_HEIGHT + 2, i, ACS_HLINE);
    }
    for (i = 1; i < AREA_HEIGHT; ++i)
    {
        mvaddch(i,          0, ACS_VLINE);
        mvaddch(i, AREA_WIDTH, ACS_VLINE);
    }

    mvaddch(area.food.y, area.food.x, '+');
    area.snake->draw();

    mvaddstr(AREA_HEIGHT + 1, 1, "snake length: ");
    printw("%i", area.snake->getLength());

    refresh();
}

void Game::run()
{
    while (running)
    {
        update();
        draw();
    }
}

bool Game::isSnakeCrashed() const
{
    unsigned char snakeX = area.snake->getX();
    unsigned char snakeY = area.snake->getY();

    return snakeX <= 0 || snakeX >= AREA_WIDTH  ||
           snakeY <= 0 || snakeY >= AREA_HEIGHT || area.snake->isCrashed();
}

bool Game::isSnakeEat() const
{
    unsigned char snakeX = area.snake->getX();
    unsigned char snakeY = area.snake->getY();

    return snakeX == area.food.x && snakeY == area.food.y;
}

