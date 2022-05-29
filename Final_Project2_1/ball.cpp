#include <ball.h>


void Ball::initShape(const sf::RenderWindow& window)
{
    this->shape.setRadius(static_cast<float>(rand()%10+10));

        sf::Color color;
    sf::Texture texture_heart;

    switch (this->type)
    {
    case DEFAULT:
        color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
        break;
    case DAMAGING:
        color = sf::Color::Red;
        this->shape.setOutlineColor(sf::Color::White);
        this->shape.setOutlineThickness(2.f);
        break;
    case HEALING:
        color = sf::Color::Green;
        this->shape.setOutlineColor(sf::Color::White);
        this->shape.setOutlineThickness(2.f);
        break;
    }

    this->shape.setFillColor(color);
    this->shape.setPosition(
        sf::Vector2f(
            static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
            static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)
        )

    );
    this->shape.move(0.f, this->speed);
}

Ball::Ball(const sf::RenderWindow& window, int type)
    : type(type)
{
    this->initShape(window);
}

Ball::~Ball()
{

}

const sf::FloatRect Ball::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const int & Ball::getType() const
{
    return this->type;
}

void Ball::update()
{
 this->shape.move(0.f, 5.f);
}

void Ball::render(sf::RenderTarget & target)
{
    target.draw(this->shape);
}
