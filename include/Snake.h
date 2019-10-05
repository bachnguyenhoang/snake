#ifndef SNAKE_H
#define SNAKE_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include <vector>
#include <iostream>

struct snakePart
{
    public:
        int direction; // 0 up 1 down 3 right 2 left
        int loc_x, loc_y; // coordinate of the square
        sf::RectangleShape snakeBlock; //visual
};

class Snake
{
    public:
        Snake();
        virtual ~Snake();

        void snakeMove(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        void setDirection(int direction);
        int getDirection();

        void collide(int mapType);

        int getLength();

        void setSpeed(sf::Time snakeSpeed);
    protected:

    private:
        friend class snakeMap;

        int snakeLength = 3;
        int direction = -1;

        std::vector<snakePart> theSnake = std::vector<snakePart>(768);

        sf::Time speed;


};

#endif // SNAKE_H
