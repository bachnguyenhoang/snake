#ifndef MAP_H
#define MAP_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Snake.h"
#include <vector>
#include <iostream>
#include <time.h>

struct mapBrick{
public:
    int x,y; //coordinate of the brick
    sf::RectangleShape brickImg; //visual
};

class snakeMap
{
private:
    std::vector<mapBrick> brick = std::vector<mapBrick>(768);
    mapBrick fruit;
    bool fruitCount = 0;
public:
    snakeMap();
    virtual ~snakeMap();

    void mapInit(sf::RenderWindow &window,Snake &aSnake);
    void box(int mapType);
    void initFruitPosition(sf::RenderWindow &window,Snake &aSnake);
    void setFruitCount(int fruitCount);
    void eatFruit(Snake &aSnake, bool Sound);

    sf::SoundBuffer eatSoundBuffer;
    sf::Sound eatSound;

};

#endif // MAP_H
