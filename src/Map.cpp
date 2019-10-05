#include "Map.h"

snakeMap::snakeMap()
{
    //ctor
    if(!eatSoundBuffer.loadFromFile("medias/eatSound.flac")){
        std::cerr << "Can't load eatSound.flac" << std::endl;
    }
    eatSound.setBuffer(eatSoundBuffer);
    std::cout << "Arrow keys to move. Avoid the obstacles, don't bite yourself, and eat the fruits!" << std::endl;
    for(int i=0;i<768;i++){
        brick[i].x = i%32;
        brick[i].y = i/32;
        brick[i].brickImg.setSize(sf::Vector2f(20,20));

        brick[i].brickImg.setPosition(0+20*brick[i].x,0+brick[i].y*20);
    }
}

snakeMap::~snakeMap()
{
    //dtor
}

// draw the map in the window
void snakeMap::mapInit(sf::RenderWindow &window,Snake &aSnake){
    for(int i=0;i<768;i++){
        window.draw(brick[i].brickImg);
    }
    snakeMap::initFruitPosition(window,aSnake);
}

// set the color of the bricks in mapBrick
// if the player choose "Box" in option, mapType = 2
// if the player choose "Blank" in option, mapType = 1
void snakeMap::box(int mapType){
    switch(mapType){
    case 2:
        for(int i = 0;i < 32;i++){
            brick[i].brickImg.setFillColor(sf::Color(225,250,249));
            brick[i].brickImg.setOutlineColor(sf::Color(45,35,39));
            brick[i].brickImg.setOutlineThickness(-2);
        }
        for(int i = 32;i < 736;i++){
            if ((i%32 == 0)||((i+1)%32 == 0)){
                brick[i].brickImg.setFillColor(sf::Color(225,250,249));
                brick[i].brickImg.setOutlineColor(sf::Color(45,35,39));
                brick[i].brickImg.setOutlineThickness(-2);
            }
            else brick[i].brickImg.setFillColor(sf::Color(45,35,39));
        }
        for(int i = 736;i < 768;i++){
            brick[i].brickImg.setFillColor(sf::Color(225,250,249));
            brick[i].brickImg.setOutlineColor(sf::Color(45,35,39));
            brick[i].brickImg.setOutlineThickness(-2);
        }
        brick[fruit.y*32 + fruit.x].brickImg.setFillColor(sf::Color(240,128,60));
        break;
    case 1:
        for(int i=0;i<768;i++){
            brick[i].x = i%32;
            brick[i].y = i/32;
            brick[i].brickImg.setFillColor(sf::Color(45,35,39));
        }
        brick[fruit.y*32 + fruit.x].brickImg.setFillColor(sf::Color(240,128,60));
        break;
    }
}

// randomly create a fruit on the map
// also check if the fruit is over the snake and recreate the fruit when it is
void snakeMap::initFruitPosition(sf::RenderWindow &window,Snake &aSnake){
    srand(time(NULL));
    if(fruitCount > 0) return;
    else {
        fruit.y = rand() % 21 + 1;
        fruit.x = rand() % 30 + 1;
        while(fruitCount == 0){
            this->setFruitCount(1);
            for(int i = 0; i < aSnake.getLength();i++){
                if( aSnake.theSnake[i].loc_x == fruit.x && aSnake.theSnake[i].loc_y == fruit.y){
                    fruit.y = rand() % 21 + 1;
                    fruit.x = rand() % 30 + 1;
                    this->setFruitCount(0);
                }
            }
        }
        }
        std::cout << "Fruit created x: " << fruit.x << " y: " << fruit.y << std::endl;
    }

void snakeMap::setFruitCount(int fruitCount){
    this->fruitCount = fruitCount;
}

void snakeMap::eatFruit(Snake &aSnake, bool Sound){
    if(aSnake.theSnake[0].loc_x == fruit.x && aSnake.theSnake[0].loc_y == fruit.y){
        setFruitCount(0);
        aSnake.snakeLength++;
        aSnake.theSnake[aSnake.snakeLength-1].direction = aSnake.theSnake[aSnake.snakeLength-2].direction;

        switch(aSnake.theSnake[aSnake.snakeLength-1].direction){
        case 0:
            aSnake.theSnake[aSnake.snakeLength-1].loc_x = aSnake.theSnake[aSnake.snakeLength-2].loc_x;
            aSnake.theSnake[aSnake.snakeLength-1].loc_y = aSnake.theSnake[aSnake.snakeLength-2].loc_y + 1;
            break;
        case 1:
            aSnake.theSnake[aSnake.snakeLength-1].loc_x = aSnake.theSnake[aSnake.snakeLength-2].loc_x;
            aSnake.theSnake[aSnake.snakeLength-1].loc_y = aSnake.theSnake[aSnake.snakeLength-2].loc_y - 1;
            break;
        case 2:
            aSnake.theSnake[aSnake.snakeLength-1].loc_x = aSnake.theSnake[aSnake.snakeLength-2].loc_x + 1;
            aSnake.theSnake[aSnake.snakeLength-1].loc_y = aSnake.theSnake[aSnake.snakeLength-2].loc_y;
            break;
        case 3:
            aSnake.theSnake[aSnake.snakeLength-1].loc_x = aSnake.theSnake[aSnake.snakeLength-2].loc_x - 1;
            aSnake.theSnake[aSnake.snakeLength-1].loc_y = aSnake.theSnake[aSnake.snakeLength-2].loc_y;
            break;
            }

        aSnake.theSnake[aSnake.snakeLength-1].snakeBlock.setSize(sf::Vector2f(20,20));
        aSnake.theSnake[aSnake.snakeLength-1].snakeBlock.setFillColor(sf::Color(34,85,96));
        aSnake.theSnake[aSnake.snakeLength-1].snakeBlock.setOutlineColor(sf::Color(45,35,39));
        aSnake.theSnake[aSnake.snakeLength-1].snakeBlock.setOutlineThickness(-2);
        if(Sound) eatSound.play();
        std::cout << "Snake length = " << aSnake.snakeLength << std::endl;
    }
}
