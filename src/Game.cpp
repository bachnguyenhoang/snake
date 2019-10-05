#include "Game.h"

Game::Game()
{
    Window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Project Snake");
    Window.setVerticalSyncEnabled(true);

    gameState = MENU;

    srand(time(0));

    Sound = true;
    snakeSpeed = 1;
    generateWalls = 1;
    gamePaused = false;
    load.open("DATA.txt");
    for(int i=0; i < 5; i++)
    {
        load >> name[i] >> score[i];
    }
    load.close();

}

// load the sound and font files, and run updateGame()
void Game::startGame()
{
    if(!font.loadFromFile("medias/prstartk.ttf"))
    {
        std::cerr << "Failed to load prstartk!";
        return;
    }
    if(!selectSoundBuffer.loadFromFile("medias/buttonSelect.wav")){
        std::cerr << "Failed to load buttonSelect.wav" << std::endl;
    }
    if(!switchSoundBuffer.loadFromFile("medias/buttonMoveUpDown.wav")){
        std::cerr << "Failed to load buttonMoveUpDown.wav" << std::endl;
    }
    selectSound.setBuffer(selectSoundBuffer);
    switchSound.setBuffer(switchSoundBuffer);

    updateGame();
}

//Handle game states
void Game::updateGame()
{

    switch(gameState)
    {
        case Game::MENU:
            drawMenu();
            break;

        case Game::OPTION:
            drawOption();
            break;

        case Game::HIGH_SCORE:
            drawScore();
            break;

        case Game::SOUND:
            drawSound();
            break;

        case Game::MAP:
            drawMapMenu();
            break;

        case Game::SPEED:
            drawSpeedMenu();
            break;

        case Game::STARTED:
            drawGame();
            break;

        case Game::OVER:
            gameOver();
            break;

        case Game::NAME:
            nameEnter();
            break;

        case Game::ENDED:
            Window.close();
            return;
            break;
    }
}

//Main menu
void Game::drawMenu()
{
    int MenuItem = 0;

    Name.setFont(font);
    Name.setString("SNAKE!");
    Name.setCharacterSize(70);
    Name.setFillColor(sf::Color(255,23,23));
    Name.setPosition(SCREEN_WIDTH/2-Name.getGlobalBounds().width/2, SCREEN_HEIGHT/6 -Name.getGlobalBounds().height/2);

    menuStrings[0].setFont(font);
    menuStrings[0].setString("Start");
    menuStrings[0].setCharacterSize(50);
    menuStrings[0].setFillColor(sf::Color(238,198,67));
    menuStrings[0].setPosition(SCREEN_WIDTH/2-menuStrings[0].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/6 -menuStrings[0].getGlobalBounds().height/2);

    menuStrings[1].setFont(font);
    menuStrings[1].setString("Option");
    menuStrings[1].setCharacterSize(30);
    menuStrings[1].setFillColor(sf::Color(255,255,252));
    menuStrings[1].setPosition(SCREEN_WIDTH/2-menuStrings[1].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/6 -menuStrings[1].getGlobalBounds().height/2);

    menuStrings[2].setFont(font);
    menuStrings[2].setString("High score");
    menuStrings[2].setCharacterSize(30);
    menuStrings[2].setFillColor(sf::Color(255,255,252));
    menuStrings[2].setPosition(SCREEN_WIDTH/2-menuStrings[2].getGlobalBounds().width/2, 4*SCREEN_HEIGHT/6 -menuStrings[2].getGlobalBounds().height/2);

    menuStrings[3].setFont(font);
    menuStrings[3].setString("Exit");
    menuStrings[3].setCharacterSize(30);
    menuStrings[3].setFillColor(sf::Color(255,255,252));
    menuStrings[3].setPosition(SCREEN_WIDTH/2-menuStrings[3].getGlobalBounds().width/2, 5*SCREEN_HEIGHT/6 -menuStrings[3].getGlobalBounds().height/2);


    sf::Event event;

    while(gameState == Game::MENU)
    {
        while ( Window.pollEvent (event) )
        {

            switch ( event.type )
            {
            case sf::Event::KeyReleased:
                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    if(MenuItem - 1 >=0)
                    {
                        menuStrings[MenuItem].setFillColor(sf::Color(255,255,252));
                        menuStrings[MenuItem].setCharacterSize(30);
                        menuStrings[MenuItem].setPosition(SCREEN_WIDTH/2-menuStrings[MenuItem].getGlobalBounds().width/2, (MenuItem+2)*SCREEN_HEIGHT/6 -menuStrings[MenuItem].getGlobalBounds().height/2);
                        MenuItem--;
                        menuStrings[MenuItem].setFillColor(sf::Color(238,198,67));
                        menuStrings[MenuItem].setCharacterSize(50);
                        menuStrings[MenuItem].setPosition(SCREEN_WIDTH/2-menuStrings[MenuItem].getGlobalBounds().width/2, (MenuItem+2)*SCREEN_HEIGHT/6 -menuStrings[MenuItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Down:
                    if(MenuItem + 1 < 5 )
                    {
                        menuStrings[MenuItem].setFillColor(sf::Color(255,255,252));
                        menuStrings[MenuItem].setCharacterSize(30);
                        menuStrings[MenuItem].setPosition(SCREEN_WIDTH/2-menuStrings[MenuItem].getGlobalBounds().width/2, (MenuItem+2)*SCREEN_HEIGHT/6 -menuStrings[MenuItem].getGlobalBounds().height/2);
                        MenuItem++;
                        menuStrings[MenuItem].setFillColor(sf::Color(238,198,67));
                        menuStrings[MenuItem].setCharacterSize(50);
                        menuStrings[MenuItem].setPosition(SCREEN_WIDTH/2-menuStrings[MenuItem].getGlobalBounds().width/2, (MenuItem+2)*SCREEN_HEIGHT/6 -menuStrings[MenuItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Return:
                    if(Sound) selectSound.play();
                    switch(MenuItem)
                    {
                    case 0:
                        gameState = STARTED;
                        break;

                    case 1:
                        gameState = OPTION;
                        break;

                    case 2:
                        gameState = HIGH_SCORE;
                        break;

                    case 3:
                        gameState = ENDED;
                        break;


                    }
                default:
                    break;
                }
                break;

            case sf::Event::Closed:
                Window.close();
                return;
                break;

            default:
                break;
            }
        }

        Window.clear(sf::Color(34,34,34));



        for(int i = 0; i < 4; i++)
            Window.draw(menuStrings[i]);

        Window.draw(Name);



        Window.display();


    }

    updateGame();
}

//high score state
void Game::drawScore()
{


    scoreString[0].setFont(font);
    scoreString[0].setString("Highscore");
    scoreString[0].setCharacterSize(70);
    scoreString[0].setFillColor(sf::Color(255,23,23));
    scoreString[0].setPosition(SCREEN_WIDTH/2-scoreString[0].getGlobalBounds().width/2, SCREEN_HEIGHT/7 -scoreString[0].getGlobalBounds().height/2);


    for (int i=0; i < 5; i++)
    {
        std::ostringstream buffer;
        buffer << i+1 << ". "<< name[i] <<" "<<score[i];
        scoreString[i+1].setFont(font);
        scoreString[i+1].setString(buffer.str());
        scoreString[i+1].setCharacterSize(20);
        scoreString[i+1].setFillColor(sf::Color::White);
        scoreString[i+1].setPosition(SCREEN_WIDTH/2-scoreString[i+1].getGlobalBounds().width/2, (i+2)*SCREEN_HEIGHT/7 -scoreString[i+1].getGlobalBounds().height/2);
    }
    sf::Event event;
    while(gameState == Game::HIGH_SCORE)
    {
        while ( Window.pollEvent (event) )
        {
            switch ( event.type )
            {
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::Escape)
                {
                    if(Sound) selectSound.play();
                    gameState = MENU;
                }
                break;

            case sf::Event::Closed:
                Window.close();
                return;
                break;

            default:
                break;

            }
        }
        Window.clear(sf::Color(34,34,34));



        for(int i = 0; i < 6; i++)
            Window.draw(scoreString[i]);




        Window.display();

    }
    updateGame();
}

//Option
void Game::drawOption()
{
    int OptionItem = 1;

    optionStrings[0].setFont(font);
    optionStrings[0].setString("SETTING");
    optionStrings[0].setCharacterSize(60);
    optionStrings[0].setFillColor(sf::Color(255,23,23));
    optionStrings[0].setPosition(SCREEN_WIDTH/2-optionStrings[0].getGlobalBounds().width/2, SCREEN_HEIGHT/6 -optionStrings[0].getGlobalBounds().height/2);

    optionStrings[1].setFont(font);
    optionStrings[1].setString("Sound:");
    optionStrings[1].setCharacterSize(40);
    optionStrings[1].setFillColor(sf::Color(238,198,67));
    optionStrings[1].setPosition(SCREEN_WIDTH/6-50, 2*SCREEN_HEIGHT/6 -optionStrings[1].getGlobalBounds().height/2);

    optionStrings[2].setFont(font);
    optionStrings[2].setString("Map:");
    optionStrings[2].setCharacterSize(30);
    optionStrings[2].setFillColor(sf::Color(255,255,252));
    optionStrings[2].setPosition(SCREEN_WIDTH/6-50, 3*SCREEN_HEIGHT/6 -optionStrings[2].getGlobalBounds().height/2);

    optionStrings[3].setFont(font);
    optionStrings[3].setString("Speed:");
    optionStrings[3].setCharacterSize(30);
    optionStrings[3].setFillColor(sf::Color(255,255,252));
    optionStrings[3].setPosition(SCREEN_WIDTH/6-50, 4*SCREEN_HEIGHT/6 -optionStrings[3].getGlobalBounds().height/2);

    optionStrings[4].setFont(font);
    optionStrings[4].setString("Back");
    optionStrings[4].setCharacterSize(30);
    optionStrings[4].setFillColor(sf::Color(255,255,252));
    optionStrings[4].setPosition(SCREEN_WIDTH/2-optionStrings[4].getGlobalBounds().width/2, 5*SCREEN_HEIGHT/6 -optionStrings[4].getGlobalBounds().height/2);

    lableString[0].setCharacterSize(40);
    lableString[0].setFillColor(sf::Color(238,198,67));

    lableString[1].setCharacterSize(30);
    lableString[1].setFillColor(sf::Color(255,255,252));

    lableString[2].setCharacterSize(30);
    lableString[2].setFillColor(sf::Color(255,255,252));


    if (Sound)
        lableString[0].setString("On");
    else
        lableString[0].setString("Off");

    switch (generateWalls)
    {
    case 1:
        lableString[1].setString("Blank");
        break;

    case 2:
        lableString[1].setString("Box");
        break;

    default:
        break;
    }

    switch (snakeSpeed)
    {
    case 1:
        lableString[2].setString("Easy");
        break;

    case 2:
        lableString[2].setString("Normal");
        break;

    case 3:
        lableString[2].setString("Hard");
        break;

    default:
        break;
    }

    for (int i = 0; i<3 ; i++)
    {
        lableString[i].setFont(font);
        lableString[i].setPosition(3*SCREEN_WIDTH/4-lableString[i].getGlobalBounds().width+100, (i+2)*SCREEN_HEIGHT/6 - lableString[i].getGlobalBounds().height/2);
    }


    sf::Event event;
    while (gameState == Game::OPTION)
    {
        while ( Window.pollEvent (event) )
        {
            switch ( event.type )
            {
            case sf::Event::KeyReleased:
                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    if(OptionItem - 1 >=1 && OptionItem != 4)
                    {
                        optionStrings[OptionItem].setFillColor(sf::Color(255,255,252));
                        optionStrings[OptionItem].setCharacterSize(30);
                        optionStrings[OptionItem].setPosition(SCREEN_WIDTH/6-50, (OptionItem+1)*SCREEN_HEIGHT/6 -optionStrings[OptionItem].getGlobalBounds().height/2);
                        lableString[OptionItem-1].setFillColor(sf::Color(255,255,252));
                        lableString[OptionItem-1].setCharacterSize(30);
                        lableString[OptionItem-1].setPosition(3*SCREEN_WIDTH/4-lableString[OptionItem-1].getGlobalBounds().width+100, (OptionItem+1)*SCREEN_HEIGHT/6 -lableString[OptionItem-1].getGlobalBounds().height/2);
                        OptionItem--;
                        optionStrings[OptionItem].setFillColor(sf::Color(238,198,67));
                        optionStrings[OptionItem].setCharacterSize(40);
                        optionStrings[OptionItem].setPosition(SCREEN_WIDTH/6-50, (OptionItem+1)*SCREEN_HEIGHT/6 -optionStrings[OptionItem].getGlobalBounds().height/2);
                        lableString[OptionItem-1].setFillColor(sf::Color(238,198,67));
                        lableString[OptionItem-1].setCharacterSize(40);
                        lableString[OptionItem-1].setPosition(3*SCREEN_WIDTH/4-lableString[OptionItem-1].getGlobalBounds().width+100, (OptionItem+1)*SCREEN_HEIGHT/6 -lableString[OptionItem-1].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    if(OptionItem == 4)
                    {
                        optionStrings[OptionItem].setFillColor(sf::Color(255,255,252));
                        optionStrings[OptionItem].setCharacterSize(30);
                        optionStrings[OptionItem].setPosition(SCREEN_WIDTH/2 - optionStrings[OptionItem].getGlobalBounds().width/2, (OptionItem+1)*SCREEN_HEIGHT/6 -optionStrings[OptionItem].getGlobalBounds().height/2);
                        OptionItem--;
                        optionStrings[OptionItem].setFillColor(sf::Color(238,198,67));
                        optionStrings[OptionItem].setCharacterSize(40);
                        optionStrings[OptionItem].setPosition(SCREEN_WIDTH/6-50, (OptionItem+1)*SCREEN_HEIGHT/6 -optionStrings[OptionItem].getGlobalBounds().height/2);
                        lableString[OptionItem-1].setFillColor(sf::Color(238,198,67));
                        lableString[OptionItem-1].setCharacterSize(40);
                        lableString[OptionItem-1].setPosition(3*SCREEN_WIDTH/4-lableString[OptionItem-1].getGlobalBounds().width+100, (OptionItem+1)*SCREEN_HEIGHT/6 -lableString[OptionItem-1].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Down:
                    if(OptionItem  + 1< 5)
                    {
                        optionStrings[OptionItem].setFillColor(sf::Color(255,255,252));
                        optionStrings[OptionItem].setCharacterSize(30);
                        optionStrings[OptionItem].setPosition(SCREEN_WIDTH/6-50, (OptionItem+1)*SCREEN_HEIGHT/6 -optionStrings[OptionItem].getGlobalBounds().height/2);
                        lableString[OptionItem-1].setFillColor(sf::Color(255,255,252));
                        lableString[OptionItem-1].setCharacterSize(30);
                        lableString[OptionItem-1].setPosition(3*SCREEN_WIDTH/4-lableString[OptionItem-1].getGlobalBounds().width+100, (OptionItem+1)*SCREEN_HEIGHT/6 -lableString[OptionItem-1].getGlobalBounds().height/2);
                        OptionItem++;
                        if(OptionItem == 4)
                        {
                            optionStrings[OptionItem].setFillColor(sf::Color(238,198,67));
                            optionStrings[OptionItem].setCharacterSize(40);
                            optionStrings[OptionItem].setPosition(SCREEN_WIDTH/2 - optionStrings[OptionItem].getGlobalBounds().width/2, (OptionItem+1)*SCREEN_HEIGHT/6 -optionStrings[OptionItem].getGlobalBounds().height/2);
                            if(Sound) switchSound.play();
                        }
                        else
                        {
                            optionStrings[OptionItem].setFillColor(sf::Color(238,198,67));
                            optionStrings[OptionItem].setCharacterSize(40);
                            optionStrings[OptionItem].setPosition(SCREEN_WIDTH/6-50, (OptionItem+1)*SCREEN_HEIGHT/6 -optionStrings[OptionItem].getGlobalBounds().height/2);
                            lableString[OptionItem-1].setFillColor(sf::Color(238,198,67));
                            lableString[OptionItem-1].setCharacterSize(40);
                            lableString[OptionItem-1].setPosition(3*SCREEN_WIDTH/4-lableString[OptionItem-1].getGlobalBounds().width+100, (OptionItem+1)*SCREEN_HEIGHT/6 -lableString[OptionItem-1].getGlobalBounds().height/2);
                            if(Sound) switchSound.play();

                        }
                    }

                    break;

                case sf::Keyboard::Return:
                    if(Sound) selectSound.play();
                    switch (OptionItem)
                    {
                    case 1:
                        gameState = SOUND;
                        break;

                    case 2:
                        gameState = MAP;
                        break;

                    case 3:
                        gameState = SPEED;
                        break;

                    case 4:
                        gameState = MENU;
                        break;
                    }
                    break;

                default:
                    break;
                }
                break;

            case sf::Event::Closed:
                Window.close();
                return;
                break;

            default:
                break;
            }
        }
        Window.clear(sf::Color(34,34,34));



        for(int i = 0; i < 5; i++)
            Window.draw(optionStrings[i]);

        for(int i = 0; i < 3; i++)
            Window.draw(lableString[i]);

        Window.display();
    }
    updateGame();
}

//Sound
void Game::drawSound()
{
    int SoundItem = 1;

    soundStrings[0].setFont(font);
    soundStrings[0].setString("SOUND");
    soundStrings[0].setCharacterSize(60);
    soundStrings[0].setFillColor(sf::Color(255,23,23));
    soundStrings[0].setPosition(SCREEN_WIDTH/2-soundStrings[0].getGlobalBounds().width/2, SCREEN_HEIGHT/5 -soundStrings[0].getGlobalBounds().height/2);

    soundStrings[1].setFont(font);
    soundStrings[1].setString("ON");
    soundStrings[1].setCharacterSize(40);
    soundStrings[1].setFillColor(sf::Color(238,198,67));
    soundStrings[1].setPosition(SCREEN_WIDTH/2-soundStrings[1].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/5 -soundStrings[1].getGlobalBounds().height/2);

    soundStrings[2].setFont(font);
    soundStrings[2].setString("OFF");
    soundStrings[2].setCharacterSize(30);
    soundStrings[2].setFillColor(sf::Color(255,255,252));
    soundStrings[2].setPosition(SCREEN_WIDTH/2-soundStrings[2].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/5 -soundStrings[2].getGlobalBounds().height/2);

    soundStrings[3].setFont(font);
    soundStrings[3].setString("Back");
    soundStrings[3].setCharacterSize(30);
    soundStrings[3].setFillColor(sf::Color(255,255,252));
    soundStrings[3].setPosition(SCREEN_WIDTH/2-soundStrings[3].getGlobalBounds().width/2, 4*SCREEN_HEIGHT/5 -soundStrings[3].getGlobalBounds().height/2);

    sf::Event event;
    while (gameState == Game::SOUND)
    {
        while ( Window.pollEvent (event) )
        {
            switch ( event.type )
            {
            case sf::Event::KeyReleased:
                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    if(SoundItem - 1 >=1)
                    {
                        soundStrings[SoundItem].setFillColor(sf::Color(255,255,252));
                        soundStrings[SoundItem].setCharacterSize(30);
                        soundStrings[SoundItem].setPosition(SCREEN_WIDTH/2-soundStrings[SoundItem].getGlobalBounds().width/2, (SoundItem+1)*SCREEN_HEIGHT/5 -soundStrings[SoundItem].getGlobalBounds().height/2);
                        SoundItem--;
                        soundStrings[SoundItem].setFillColor(sf::Color(238,198,67));
                        soundStrings[SoundItem].setCharacterSize(40);
                        soundStrings[SoundItem].setPosition(SCREEN_WIDTH/2-soundStrings[SoundItem].getGlobalBounds().width/2, (SoundItem+1)*SCREEN_HEIGHT/5 -soundStrings[SoundItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Down:
                    if(SoundItem - 1 < 4)
                    {
                        soundStrings[SoundItem].setFillColor(sf::Color(255,255,252));
                        soundStrings[SoundItem].setCharacterSize(30);
                        soundStrings[SoundItem].setPosition(SCREEN_WIDTH/2-soundStrings[SoundItem].getGlobalBounds().width/2, (SoundItem+1)*SCREEN_HEIGHT/5 -soundStrings[SoundItem].getGlobalBounds().height/2);
                        SoundItem++;
                        soundStrings[SoundItem].setFillColor(sf::Color(238,198,67));
                        soundStrings[SoundItem].setCharacterSize(40);
                        soundStrings[SoundItem].setPosition(SCREEN_WIDTH/2-soundStrings[SoundItem].getGlobalBounds().width/2, (SoundItem+1)*SCREEN_HEIGHT/5 -soundStrings[SoundItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Return:
                    if(Sound) selectSound.play();
                    switch (SoundItem)
                    {
                    case 1:
                        Sound = true;
                        gameState = OPTION;
                        break;

                    case 2:
                        Sound = false;
                        gameState = OPTION;
                        break;

                    case 3:
                        gameState = OPTION;
                        break;
                    }
                    break;
                default:
                    break;
                }

                break;

            case sf::Event::Closed:
                Window.close();
                return;
                break;

            default:
                break;
            }
        }
        Window.clear(sf::Color(34,34,34));



        for(int i = 0; i < 4; i++)
            Window.draw(soundStrings[i]);

        Window.display();

    }
    updateGame();

}

//Map menu
void Game::drawMapMenu()
{
    int MapItem = 1;

    mapStrings[0].setFont(font);
    mapStrings[0].setString("Map");
    mapStrings[0].setCharacterSize(70);
    mapStrings[0].setFillColor(sf::Color(255,23,23));
    mapStrings[0].setPosition(SCREEN_WIDTH/2-mapStrings[0].getGlobalBounds().width/2, SCREEN_HEIGHT/5 -mapStrings[0].getGlobalBounds().height/2);

    mapStrings[1].setFont(font);
    mapStrings[1].setString("Blank");
    mapStrings[1].setCharacterSize(50);
    mapStrings[1].setFillColor(sf::Color(238,198,67));
    mapStrings[1].setPosition(SCREEN_WIDTH/2-mapStrings[1].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/5 -mapStrings[1].getGlobalBounds().height/2);

    mapStrings[2].setFont(font);
    mapStrings[2].setString("Box");
    mapStrings[2].setCharacterSize(30);
    mapStrings[2].setFillColor(sf::Color(255,255,252));
    mapStrings[2].setPosition(SCREEN_WIDTH/2-mapStrings[2].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/5 -mapStrings[2].getGlobalBounds().height/2);

    mapStrings[3].setFont(font);
    mapStrings[3].setString("Back");
    mapStrings[3].setCharacterSize(30);
    mapStrings[3].setFillColor(sf::Color(255,255,252));
    mapStrings[3].setPosition(SCREEN_WIDTH/2-mapStrings[3].getGlobalBounds().width/2, 4*SCREEN_HEIGHT/5 -mapStrings[3].getGlobalBounds().height/2);


    sf::Event event;

    while(gameState == Game::MAP)
    {

        while ( Window.pollEvent (event) )
        {
            switch ( event.type )
            {
            case sf::Event::KeyReleased:
                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    if(MapItem - 1 >=1)
                    {
                        mapStrings[MapItem].setFillColor(sf::Color(255,255,252));
                        mapStrings[MapItem].setCharacterSize(30);
                        mapStrings[MapItem].setPosition(SCREEN_WIDTH/2-mapStrings[MapItem].getGlobalBounds().width/2, (MapItem+1)*SCREEN_HEIGHT/5 -mapStrings[MapItem].getGlobalBounds().height/2);
                        MapItem--;
                        mapStrings[MapItem].setFillColor(sf::Color(238,198,67));
                        mapStrings[MapItem].setCharacterSize(50);
                        mapStrings[MapItem].setPosition(SCREEN_WIDTH/2-mapStrings[MapItem].getGlobalBounds().width/2, (MapItem+1)*SCREEN_HEIGHT/5 -mapStrings[MapItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Down:
                    if(MapItem + 1 < 4 )
                    {
                        mapStrings[MapItem].setFillColor(sf::Color(255,255,252));
                        mapStrings[MapItem].setCharacterSize(30);
                        mapStrings[MapItem].setPosition(SCREEN_WIDTH/2-mapStrings[MapItem].getGlobalBounds().width/2, (MapItem+1)*SCREEN_HEIGHT/5 -mapStrings[MapItem].getGlobalBounds().height/2);
                        MapItem++;
                        mapStrings[MapItem].setFillColor(sf::Color(238,198,67));
                        mapStrings[MapItem].setCharacterSize(50);
                        mapStrings[MapItem].setPosition(SCREEN_WIDTH/2-mapStrings[MapItem].getGlobalBounds().width/2, (MapItem+1)*SCREEN_HEIGHT/5 -mapStrings[MapItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Return:
                    if(Sound) selectSound.play();
                    switch(MapItem)
                    {
                    case 1:
                        generateWalls = 1;
                        gameState = OPTION;
                        break;

                    case 2:
                        generateWalls = 2;
                        gameState = OPTION;
                        break;
                    case 3:
                        gameState = OPTION;
                        break;


                    }
                    default:
                        break;
                }
                break;

            case sf::Event::Closed:
                Window.close();
                return;
                break;
            default:
                break;
            }
        }
        Window.clear(sf::Color(34,34,34));



        for(int i = 0; i < 4; i++)
            Window.draw(mapStrings[i]);



        Window.display();

    }

    updateGame();

}

//Speed Menu
void Game::drawSpeedMenu()
{

    int SpeedItem = 1;

    speedStrings[0].setFont(font);
    speedStrings[0].setString("Difficulty");
    speedStrings[0].setCharacterSize(40);
    speedStrings[0].setFillColor(sf::Color(255,23,23));
    speedStrings[0].setPosition(SCREEN_WIDTH/2-speedStrings[0].getGlobalBounds().width/2, SCREEN_HEIGHT/4 -speedStrings[0].getGlobalBounds().height/2);

    speedStrings[1].setFont(font);
    speedStrings[1].setString("Easy");
    speedStrings[1].setCharacterSize(20);
    speedStrings[1].setFillColor(sf::Color(238,198,67));
    speedStrings[1].setPosition(SCREEN_WIDTH/4-speedStrings[1].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[1].getGlobalBounds().height/2);

    speedStrings[2].setFont(font);
    speedStrings[2].setString("Normal");
    speedStrings[2].setCharacterSize(20);
    speedStrings[2].setFillColor(sf::Color(255,255,252));
    speedStrings[2].setPosition(2*SCREEN_WIDTH/4-speedStrings[2].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[2].getGlobalBounds().height/2);

    speedStrings[3].setFont(font);
    speedStrings[3].setString("Hard");
    speedStrings[3].setCharacterSize(20);
    speedStrings[3].setFillColor(sf::Color(255,255,252));
    speedStrings[3].setPosition(3*SCREEN_WIDTH/4-speedStrings[3].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[3].getGlobalBounds().height/2);

    speedStrings[4].setFont(font);
    speedStrings[4].setString("Back");
    speedStrings[4].setCharacterSize(20);
    speedStrings[4].setFillColor(sf::Color(255,255,252));
    speedStrings[4].setPosition(SCREEN_WIDTH/2-speedStrings[4].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/4 -speedStrings[4].getGlobalBounds().height/2);

    sf::Event event;

    while(gameState == Game::SPEED)
    {
        while ( Window.pollEvent (event) )
        {

            switch ( event.type )
            {
            case sf::Event::KeyReleased:
                switch(event.key.code)
                {
                case sf::Keyboard::Left:
                    if(SpeedItem - 1 >=1 && SpeedItem != 4)
                    {
                        speedStrings[SpeedItem].setFillColor(sf::Color(255,255,252));
                        speedStrings[SpeedItem].setCharacterSize(20);
                        speedStrings[SpeedItem].setPosition(SpeedItem*SCREEN_WIDTH/4-speedStrings[SpeedItem].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[SpeedItem].getGlobalBounds().height/2);
                        SpeedItem--;
                        speedStrings[SpeedItem].setFillColor(sf::Color(238,198,67));
                        speedStrings[SpeedItem].setCharacterSize(30);
                        speedStrings[SpeedItem].setPosition(SpeedItem*SCREEN_WIDTH/4-speedStrings[SpeedItem].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[SpeedItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Right:
                    if(SpeedItem + 1 < 4 )
                    {
                        speedStrings[SpeedItem].setFillColor(sf::Color(255,255,252));
                        speedStrings[SpeedItem].setCharacterSize(20);
                        speedStrings[SpeedItem].setPosition(SpeedItem*SCREEN_WIDTH/4-speedStrings[SpeedItem].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[SpeedItem].getGlobalBounds().height/2);
                        SpeedItem++;
                        speedStrings[SpeedItem].setFillColor(sf::Color(238,198,67));
                        speedStrings[SpeedItem].setCharacterSize(30);
                        speedStrings[SpeedItem].setPosition(SpeedItem*SCREEN_WIDTH/4-speedStrings[SpeedItem].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[SpeedItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Down:
                    if(SpeedItem != 4)
                    {
                        speedStrings[SpeedItem].setFillColor(sf::Color(255,255,252));
                        speedStrings[SpeedItem].setCharacterSize(20);
                        speedStrings[SpeedItem].setPosition(SpeedItem*SCREEN_WIDTH/4-speedStrings[SpeedItem].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[SpeedItem].getGlobalBounds().height/2);
                        SpeedItem = 4;
                        speedStrings[SpeedItem].setFillColor(sf::Color(238,198,67));
                        speedStrings[SpeedItem].setCharacterSize(30);
                        speedStrings[SpeedItem].setPosition(SCREEN_WIDTH/2-speedStrings[SpeedItem].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/4 -speedStrings[SpeedItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Up:
                    if(SpeedItem == 4)
                    {
                        speedStrings[SpeedItem].setFillColor(sf::Color(255,255,252));
                        speedStrings[SpeedItem].setCharacterSize(20);
                        speedStrings[SpeedItem].setPosition(SCREEN_WIDTH/2-speedStrings[SpeedItem].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/4 -speedStrings[SpeedItem].getGlobalBounds().height/2);
                        SpeedItem = 1;
                        speedStrings[SpeedItem].setFillColor(sf::Color(238,198,67));
                        speedStrings[SpeedItem].setCharacterSize(30);
                        speedStrings[SpeedItem].setPosition(SpeedItem*SCREEN_WIDTH/4-speedStrings[SpeedItem].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/4 -speedStrings[SpeedItem].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Return:
                    if(Sound) selectSound.play();
                    switch(SpeedItem)
                    {
                    case 1:
                        snakeSpeed = 1;
                        gameState = OPTION;
                        break;

                    case 2:
                        snakeSpeed = 2;
                        gameState = OPTION;
                        break;
                    case 3:
                        snakeSpeed = 3;
                        gameState = OPTION;
                        break;
                    case 4:
                        gameState = OPTION;
                        break;


                    }
                    default:
                        break;
                }
                break;

            case sf::Event::Closed:
                Window.close();
                return;
                break;

            default:
                break;
            }

        }

        Window.clear(sf::Color(34,34,34));



        for(int i = 0; i < 5; i++)
            Window.draw(speedStrings[i]);



        Window.display();
    }

    updateGame();
}

//main game
void Game::drawGame()
{
    snakeMap map2;
    Snake snake1;

    int tempDirection = snake1.getDirection();
    points = 0;

    pauseString[0].setFont(font);
    pauseString[0].setString("Game paused");
    pauseString[0].setCharacterSize(40);
    pauseString[0].setFillColor(sf::Color::White);
    pauseString[0].setPosition(SCREEN_WIDTH/2-pauseString[0].getGlobalBounds().width/2, SCREEN_HEIGHT/2 -pauseString[0].getGlobalBounds().height/2-30);

    pauseString[1].setFont(font);
    pauseString[1].setString("pressed P to continue");
    pauseString[1].setCharacterSize(20);
    pauseString[1].setFillColor(sf::Color::White);
    pauseString[1].setPosition(SCREEN_WIDTH/2-pauseString[1].getGlobalBounds().width/2, SCREEN_HEIGHT/2 -pauseString[1].getGlobalBounds().height/2+30);



    switch(snakeSpeed)
    {
    case 1:
        snake1.setSpeed(sf::milliseconds(180));
        break;

    case 2:
        snake1.setSpeed(sf::milliseconds(120));
        break;

    case 3:
        snake1.setSpeed(sf::milliseconds(50));
        break;
    }

    sf::Event event;
    while (gameState == Game::STARTED)
    {
        while (Window.pollEvent(event))
        {

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            {
                std::cout << "pause direction = " << tempDirection << std:: endl;
                if(!gamePaused)
                {
                    tempDirection = snake1.getDirection();
                    snake1.setDirection(-1);
                    gamePaused = true;

                }
                else
                {
                    gamePaused = false;
                    snake1.setDirection(tempDirection);
                    snake1.snakeMove(Window);
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && gamePaused == false){
                snake1.setDirection(0);
                std::cout << "Up is pressed, snake direction is " << snake1.getDirection() << std::endl;
                snake1.collide(generateWalls);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && gamePaused == false){
                snake1.setDirection(1);
                std::cout << "Down is pressed, snake direction is " << snake1.getDirection() << std::endl;
                snake1.collide(generateWalls);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && gamePaused == false){
                snake1.setDirection(2);
                std::cout << "Left is pressed, snake direction is " << snake1.getDirection() << std::endl;
                snake1.collide(generateWalls);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && gamePaused == false){
                snake1.setDirection(3);
                std::cout << "Right is pressed, snake direction is " << snake1.getDirection() << std::endl;
                snake1.collide(generateWalls);
            }

            if (event.type == sf::Event::Closed)
            {
                gameState = ENDED;
            }

        }
        Window.clear(sf::Color(225,250,249));

        map2.mapInit(Window,snake1);
        snake1.draw(Window);
        map2.box(generateWalls);

        snake1.snakeMove(Window);
        snake1.collide(generateWalls);
        map2.eatFruit(snake1,Sound);

        if(gamePaused)
            for (int i = 0; i <2 ; i++)
            {
            Window.draw(pauseString[i]);
            }
        drawPoint(Window,snake1);

        Window.display();
        if(snake1.getDirection() == 4)
        {
            if(points <= score[4])
            {
                gameState = OVER;
            }
            else gameState = NAME;
            std::cout << "Score: " << points << std::endl;
        }

    }

    updateGame();
}

void Game::gameOver()
{
    int over = 2;
    for(int i = 0; i < 4; i++)
    {
        gameOverStrings[i].setFont(font);
    }

    gameOverStrings[0].setString("GAME OVER");
    gameOverStrings[0].setCharacterSize(60);
    gameOverStrings[0].setPosition(SCREEN_WIDTH/2-gameOverStrings[0].getGlobalBounds().width/2, SCREEN_HEIGHT/5-gameOverStrings[0].getGlobalBounds().height/2);
    gameOverStrings[0].setFillColor(sf::Color(255,23,23));

    //transfer point into string
    std::ostringstream buffer;
    pointsText = "Your points: ";
    buffer << points;
    pointsText += buffer.str();

    gameOverStrings[1].setCharacterSize(30);
    gameOverStrings[1].setString(pointsText);
    gameOverStrings[1].setPosition(SCREEN_WIDTH/2-gameOverStrings[1].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/5-gameOverStrings[1].getGlobalBounds().height/2);
    gameOverStrings[1].setFillColor(sf::Color(101,150,171));

    gameOverStrings[2].setCharacterSize(40);
    gameOverStrings[2].setString("Continue");
    gameOverStrings[2].setPosition(SCREEN_WIDTH/2-gameOverStrings[2].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/5-gameOverStrings[2].getGlobalBounds().height/2);
    gameOverStrings[2].setFillColor(sf::Color(238,198,67));

    gameOverStrings[3].setCharacterSize(20);
    gameOverStrings[3].setString("Exit");
    gameOverStrings[3].setPosition(SCREEN_WIDTH/2-gameOverStrings[3].getGlobalBounds().width/2, 4*SCREEN_HEIGHT/5-gameOverStrings[3].getGlobalBounds().height/2);
    gameOverStrings[3].setFillColor(sf::Color(255,255,252));

    sf::Event event;

    while(gameState == Game::OVER)
    {
        while ( Window.pollEvent (event) )
        {
            switch ( event.type )
            {
            case sf::Event::KeyReleased:
                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    if(over - 1 > 1)
                    {
                        gameOverStrings[over].setFillColor(sf::Color(255,255,252));
                        gameOverStrings[over].setCharacterSize(20);
                        gameOverStrings[over].setPosition(SCREEN_WIDTH/2-gameOverStrings[over].getGlobalBounds().width/2, (over+1)*SCREEN_HEIGHT/5 -gameOverStrings[over].getGlobalBounds().height/2);
                        over--;
                        gameOverStrings[over].setFillColor(sf::Color(238,198,67));
                        gameOverStrings[over].setCharacterSize(40);
                        gameOverStrings[over].setPosition(SCREEN_WIDTH/2-gameOverStrings[over].getGlobalBounds().width/2, (over+1)*SCREEN_HEIGHT/5 -gameOverStrings[over].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Down:
                    if(over + 1 < 4 )
                    {
                        gameOverStrings[over].setFillColor(sf::Color(255,255,252));
                        gameOverStrings[over].setCharacterSize(20);
                        gameOverStrings[over].setPosition(SCREEN_WIDTH/2-gameOverStrings[over].getGlobalBounds().width/2, (over+1)*SCREEN_HEIGHT/5 -gameOverStrings[over].getGlobalBounds().height/2);
                        over++;
                        gameOverStrings[over].setFillColor(sf::Color(238,198,67));
                        gameOverStrings[over].setCharacterSize(40);
                        gameOverStrings[over].setPosition(SCREEN_WIDTH/2-gameOverStrings[over].getGlobalBounds().width/2, (over+1)*SCREEN_HEIGHT/5 -gameOverStrings[over].getGlobalBounds().height/2);
                        if(Sound) switchSound.play();
                    }
                    break;

                case sf::Keyboard::Return:
                    if(Sound) selectSound.play();
                    switch (over)
                    {
                    case 2:
                        gameState = MENU;
                        break;

                    case 3:
                        gameState = ENDED;
                        break;

                    default:
                        break;
                    }

                default:
                    break;
                }
                break;

            case sf::Event::Closed:
                Window.close();
                return;
                break;

            default:
                break;


            }
        }
        Window.clear(sf::Color(34,34,34));



        for(int i = 0; i < 4; i++)
            Window.draw(gameOverStrings[i]);



        Window.display();
    }

    updateGame();
}

//get Name to make highscore
void Game::nameEnter()
{
    score[4]=points;

    for(int i=0; i<4; i++)
        enterName[i].setFont(font);

    enterName[0].setString("Congratulation");
    enterName[0].setCharacterSize(40);
    enterName[0].setPosition(SCREEN_WIDTH/2-enterName[0].getGlobalBounds().width/2, SCREEN_HEIGHT/5-enterName[0].getGlobalBounds().height/2);
    enterName[0].setFillColor(sf::Color(255,23,23));

    enterName[1].setString("You've got in top 5");
    enterName[1].setCharacterSize(20);
    enterName[1].setPosition(SCREEN_WIDTH/2-enterName[1].getGlobalBounds().width/2, 2*SCREEN_HEIGHT/5-enterName[1].getGlobalBounds().height/2);
    enterName[1].setFillColor(sf::Color(238,198,67));

    enterName[3].setString("Enter to continue");
    enterName[3].setCharacterSize(20);
    enterName[3].setPosition(SCREEN_WIDTH/2-enterName[3].getGlobalBounds().width/2, 4*SCREEN_HEIGHT/5-enterName[3].getGlobalBounds().height/2);
    enterName[3].setFillColor(sf::Color(238,198,67));

    enterName[2].setCharacterSize(20);
    enterName[2].setPosition(SCREEN_WIDTH/2-enterName[2].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/5-enterName[2].getGlobalBounds().height/2);
    enterName[2].setFillColor(sf::Color(238,198,67));

    sf::Event event;

    while(gameState == Game::NAME)
    {
        while (Window.pollEvent (event))
        {
            switch ( event.type )
            {
            case sf::Event::Closed:
                Window.close();
                return;
                break;

            case sf::Event::TextEntered:
                 if(event.text.unicode == 8 && temp_name.size()!=0)
                    {
                    temp_name.pop_back();
                    std::cout << temp_name << std::endl;
                    }
                else if (((event.text.unicode <= 90 && event.text.unicode >= 65) || (event.text.unicode <= 122 && event.text.unicode >= 97)) && temp_name.size() < 8)
                    {
                    temp_name.push_back((char)event.text.unicode);
                    std::cout << temp_name << std::endl;
                    }
                enterName[2].setString(temp_name);
                enterName[2].setPosition(SCREEN_WIDTH/2-enterName[2].getGlobalBounds().width/2, 3*SCREEN_HEIGHT/5-enterName[2].getGlobalBounds().height/2);

                break;

            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::Return)
                {
                    name[4] = temp_name;
                    int temp1;
                    std::string temp2;

                    for (int i=0; i <5 ; i++)
                    {
                        for(int j = i+1; j<5;j++)
                        {
                            if (score[i] < score[j])
                            {
                                temp1 = score[i];
                                score[i] = score[j];
                                score[j] = temp1;
                                temp2 = name[i];
                                name[i] = name[j];
                                name[j] = temp2;
                            }
                        }
                    }

                    remove("DATA.txt");

                    save.open("DATA.txt", std::ios::app);
                    for (int i=0; i<5 ; i++)
                    {
                        save << name[i] << " " << score[i] << std::endl;
                    }
                    save.close();

                    gameState = OVER;
                }

                break;
            default:
                break;

            }

        }
        Window.clear(sf::Color(34,34,34));



        for(int i = 0; i < 4; i++)
            Window.draw(enterName[i]);



        Window.display();

    }
    updateGame();

}

void Game::drawPoint(sf::RenderWindow &window,Snake &aSnake){
    std::ostringstream buffer;


    pointsText = "Points: ";
    points = snakeSpeed*(aSnake.getLength() - 3);
    buffer << points;
    pointsText += buffer.str();
    snakePoints.setFont(font);
    snakePoints.setString(pointsText);
    snakePoints.setCharacterSize(20);
    snakePoints.setPosition(10, 490);
    snakePoints.setFillColor(sf::Color(34,85,96));
    window.draw(snakePoints);

}
