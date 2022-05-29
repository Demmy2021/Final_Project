#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include "player.h"
#include "ball.h"

class Game
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    bool endGame;
    sf::Event event;

    Player player;

    int points;

    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    std::vector<Ball> Balls;

    float spawnTimerMax;
    float spawnTimer;
    size_t maxBalls;

    void initVariables();
    void initWindow();
    void initFonts();
    void initText();

public:
    //Constructors and Destructors
    Game();
    ~Game();

    //Accessors
    const bool& getEndGame() const;

    //Modifiers

    //Functions
    bool running() const;
    void pollEvents();

    void spawnBalls();
    int randBallType() const;
    void updatePlayer();
    void updateCollision();
    void updateGui();
    void update();

    void renderGui(sf::RenderTarget* target);
    void render();
};
