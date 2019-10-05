#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include "Snake.h"
#include "Map.h"
//SFML Headers
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"




//Define
#define SCREEN_HEIGHT 520
#define SCREEN_WIDTH 640



class Game
{
private:
    enum State {STARTED,MENU,HIGH_SCORE,OPTION,SOUND,MAP,SPEED,OVER,NAME,ENDED};
    State gameState;
    sf::RenderWindow Window;
    std::ifstream load;
    std::ofstream save;

    std::string temp_name;

    std::string name[5];
    int score[5];

    sf::Font font;

    sf::Text Name;
    sf::Text menuStrings[4];
    sf::Text optionStrings[5];
    sf::Text lableString[3];
    sf::Text soundStrings[4];
    sf::Text mapStrings[4];
    sf::Text speedStrings[5];
    sf::Text scoreString[6];
    sf::Text snakePoints;
    sf::Text gameOverStrings[4];
    sf::Text pauseString[2];
    sf::Text enterName[4];

    sf::SoundBuffer switchSoundBuffer;
    sf::SoundBuffer selectSoundBuffer;
    sf::Sound switchSound;
    sf::Sound selectSound;

    int snakeSpeed;
    int generateWalls;
    bool gamePaused;
    bool Sound;

    int points;

    std::string pointsText;

    void updateGame();

    void drawMenu();
    void drawOption();
    void drawScore();
    void drawSound();
    void drawMapMenu();
    void drawSpeedMenu();
    void drawGame();
    void gameOver();
    void nameEnter();
    void drawPoint(sf::RenderWindow &window,Snake &aSnake);

public:
    Game();
    void startGame();
};

#endif // GAME_H_INCLUDED
