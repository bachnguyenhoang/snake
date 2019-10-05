#include "Snake.h"

Snake::Snake()
{
    //ctor
    for(int i = 0;i < snakeLength;i++){
        theSnake[i].loc_x = 32/2-i;
        theSnake[i].loc_y = 24/2;
        theSnake[i].direction = 3;
        if(i==0){
            theSnake[i].snakeBlock.setFillColor(sf::Color(237,240,96));
            theSnake[0].direction = -1;
        }
        else theSnake[i].snakeBlock.setFillColor(sf::Color(34,85,96));

        theSnake[i].snakeBlock.setSize(sf::Vector2f(20,20));
        theSnake[i].snakeBlock.setPosition(sf::Vector2f(theSnake[i].loc_x*20,theSnake[i].loc_y*20));
        theSnake[i].snakeBlock.setOutlineColor(sf::Color(45,35,39));
        theSnake[i].snakeBlock.setOutlineThickness(-2);


    }

    std::cout << "Snake length = " << snakeLength << std::endl;
}

Snake::~Snake()
{
    //dtor
}

// draw the snake on the window
void Snake::draw(sf::RenderWindow &window){
    for(int i = 0;i< snakeLength;i++)
        window.draw(theSnake[i].snakeBlock);

    }

//move the snake in direction
void Snake::snakeMove(sf::RenderWindow &window){
    // set the direction of the snake head. If the direction of the snake head
    // is in reverse with this->direction, the snake's direction doesn't change
    switch(this->direction){
    case 0:
        if(theSnake[0].direction == 1) theSnake[0].direction = 1;
        else theSnake[0].direction = this->direction;
        break;
    case 1:
        if(theSnake[0].direction == 0) theSnake[0].direction = 0;
        else theSnake[0].direction = this->direction;
        break;
    case 2:
        if(theSnake[0].direction == 3 || theSnake[0].direction == -1) theSnake[0].direction = 3;
        else theSnake[0].direction = this->direction;
        break;
    case 3:
        if(theSnake[0].direction == 2) theSnake[0].direction = 2;
        else theSnake[0].direction = this->direction;
        break;
    default:
        return;
    }
    // set the location of the snake base on its parts' direction
    for(int i = 0;i < snakeLength; i++){
        switch(theSnake[i].direction){
        case 0:
            if(theSnake[i].loc_y > 0)
                theSnake[i].loc_y--;
            else theSnake[i].loc_y = 23;
            break;
        case 1:
            if(theSnake[i].loc_y < 23)
                theSnake[i].loc_y++;
            else theSnake[i].loc_y = 0;
            break;
        case 2:
            if(theSnake[i].loc_x > 0)
                theSnake[i].loc_x--;
            else theSnake[i].loc_x = 31;
            break;
        case 3:
            if(theSnake[i].loc_x < 31)
                theSnake[i].loc_x++;
            else theSnake[i].loc_x = 0;
            break;
        }
    }
    for(int i = 0;i < snakeLength; i++){
        theSnake[i].snakeBlock.setPosition(sf::Vector2f(theSnake[i].loc_x*20,theSnake[i].loc_y*20));
        window.draw(theSnake[i].snakeBlock);
    }
    //set the direction for each part of the snake by reassign the direction of each part, from tail to head,
    // to its front part.
    for(int i = snakeLength-1; i >0;i--){
        theSnake[i].direction = theSnake[i-1].direction;
    }
    //delay the function for an interval equal to "speed"
    sf::sleep(speed);
}

void Snake::setDirection(int direction){
    this->direction = direction;
}
int Snake::getDirection(){
    return this->direction;
}
// check if the snake collide with the box' boundary or itself
void Snake::collide(int mapType){
    switch(mapType){
    //for map box
    case 2:
        if (theSnake[0].loc_x <= 0 || theSnake[0].loc_x >= 31 || theSnake[0].loc_y <= 0 || theSnake[0].loc_y >= 23){
            this->setDirection(4);
            std::cout << "Collision!" <<std::endl;
        }
        for(int i = 1;i <snakeLength;i++){
            if (theSnake[0].loc_x == theSnake[i].loc_x && theSnake[0].loc_y == theSnake[i].loc_y){
                this->setDirection(4);
                std::cout << "Collision!" <<std::endl;
            }
        }
        break;
    //for map blank
    case 1:
        for(int i = 1;i <snakeLength;i++){
            if (theSnake[0].loc_x == theSnake[i].loc_x && theSnake[0].loc_y == theSnake[i].loc_y){
                this->setDirection(4);
                std::cout << "Collision!" <<std::endl;
            }
        }
        break;
    }

}

int Snake::getLength(){
    return this->snakeLength;
    }

void Snake::setSpeed(sf::Time snakeSpeed){
    this->speed = snakeSpeed;
}
