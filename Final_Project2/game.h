#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game
{
    private:
    //variables
    //window

    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;


    void initializeVariable();

    void initializeWindow();

public: //constructor /destructor
    Game();

    virtual ~ Game();

    //Accessors

    const bool running() const;



    //Functions
    void pollEvents();
    void update();
    void render();

};











#endif // GAME_H
