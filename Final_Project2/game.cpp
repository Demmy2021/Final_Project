#include "game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


void Game::initializeVariable(){

    this-> window = nullptr;
}

void Game::initializeWindow(){

    this ->videoMode.height = 600;
    this ->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Project Game", sf::Style::Titlebar | sf::Style::Close);

}

Game::Game()
{

    this ->initializeVariable();
    this->initializeWindow();

}

Game:: ~Game(){

 delete this->window;
}

//Function

//Game window rendering


 sf::Event event;

         while (window.isOpen()) {

            return this->window->isOpen();

            void Game::pollEvents(){

                while (this-> window -> pollEvent(this->event))
            {

     switch (this ->event.type) {

     case sf::Event::Closed:
         this->window.close();
         break;

     case sf::Event::KeyPressed:
         if(event.key.code == sf::Keyboard::Escape)
                  this->window.close();
             break;
               }

              }
            }



      }

void Game::update(){


}

void Game::render(){


    this->window->clear(sf::Color::Black);

     this->window->display();
}
