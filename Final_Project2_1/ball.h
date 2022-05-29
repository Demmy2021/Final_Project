#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum BallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class Ball
{
private:
    sf::CircleShape shape;
    int type;
    float speed = 6.0;

    void initShape(const sf::RenderWindow& window);

public:
    Ball(const sf::RenderWindow& window, int type);
    virtual ~Ball();

    //Accessor
    const sf::FloatRect getBounds() const;
    const int& getType() const;

    //Functions
    void update();
    void render(sf::RenderTarget& target);
};
