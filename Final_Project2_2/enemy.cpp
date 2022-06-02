#include "enemy.h"

void Enemy::initVariables()
{
    this->pointCount = rand() % 8 + 3; //min = 3 max = 10
    this->type		= 0;
    this->speed		= static_cast<float>(this->pointCount/3);
    this->hpMax		= static_cast<int>(this->pointCount);
    this->hp		= this->hpMax;
    this->damage	= this->pointCount;
    //this->heal	= this->pointCount;
    this->points	= this->pointCount;
}

void Enemy::initShape()
{
    this->shape.setRadius(this->pointCount * 5);
    this->shape.setPointCount(this->pointCount);
    this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));

//    sf::Color color;
//sf::Texture texture_heart;

//switch (this->type)
//{
//case DEFAULT:
//    color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
//    break;
//case DAMAGING:
//    color = sf::Color::Red;
//    this->shape.setOutlineColor(sf::Color::White);
//    this->shape.setOutlineThickness(2.f);
//    break;
//case HEALING:
//    color = sf::Color::Green;
//    this->shape.setOutlineColor(sf::Color::White);
//    this->shape.setOutlineThickness(2.f);
//    break;
//}
}

Enemy::Enemy(float pos_x, float pos_y)
{
    this->initVariables();
    this->initShape();

    this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const int & Enemy::getPoints() const
{
    return this->points;
}

const int & Enemy::getDamage() const
{
    return this->damage;
}

//const int & Enemy::getHeal() const
//{
//    return this->heal;
//}

//Functions
void Enemy::update()
{
    this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}
