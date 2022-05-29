#include "game.h"

void Game::initVariables()
{
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxBalls = 10;
    this->points = 0;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Dudge and Kill Prep-Stage 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("PixellettersFull.ttf"))
    {
        std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
    }
}

void Game::initText()
{
    //Gui text init
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(32);

    //End game text
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setPosition(sf::Vector2f(20, 100));
    this->endGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
}

//Constructors and Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
}

Game::~Game()
{
    delete this->window;
}

const bool & Game::getEndGame() const
{
    return this->endGame;
}

//Functions
bool Game::running() const
{
    return this->window->isOpen() /*&& this->endGame == false*/;
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
        default:
            break;
        }
    }
}

void Game::spawnBalls()
{

        //Timer
    if (this->spawnTimer < this->spawnTimerMax)
        this->spawnTimer += 0.5f;
    else
    {
        if (this->Balls.size() < this->maxBalls)
        {
            this->Balls.push_back(Ball(*this->window, this->randBallType()));

            this->spawnTimer = 0.f;
        }
    }
}

int Game::randBallType() const
{
    int type = BallTypes::DEFAULT;

    int randValue = rand() % 100 + 1;
    if (randValue > 60 && randValue <= 80)
        type = BallTypes::DAMAGING;
    else if (randValue > 80 && randValue <= 100)
        type = BallTypes::HEALING;

    return type;
}

void Game::updatePlayer()
{
    this->player.update(this->window);

    if (this->player.getHp() <= 0)
        this->endGame = true;
}

void Game::updateCollision()
{
    //Check the collision
    for (size_t i = 0; i < this->Balls.size(); i++)
    {
        this->Balls[i].update();
        if (this->player.getShape().getGlobalBounds().intersects(this->Balls[i].getBounds()))
        {
            switch (this->Balls[i].getType())
            {
            case BallTypes::DEFAULT:
                this->points++;
                break;
            case BallTypes::DAMAGING:
                this->player.takeDamage(1);
                break;
            case BallTypes::HEALING:
                this->player.gainHealth(1);
                break;
            }

            //Remove the ball
            this->Balls.erase(this->Balls.begin() + i);
        }
    }
}

void Game::updateGui()
{
    std::stringstream ss;

    ss << " - Points: " << this->points << "\n"
        << " - Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";

    this->guiText.setString(ss.str());
}

void Game::update()
{
    this->pollEvents();

    this->player.update(this->window);

    if (this->endGame == false)
    {
        this->spawnBalls();
        this->updatePlayer();
        this->updateCollision();
        this->updateGui();
    }
}

void Game::renderGui(sf::RenderTarget* target)
{
    target->draw(this->guiText);
}

void Game::render()
{
    this->window->clear();

    //Render stuff
    this->player.render(this->window);

    for (auto i : this->Balls)
    {
        i.render(*this->window);
    }

    //Render gui
    this->renderGui(this->window);

    //Render end text
    if(this->endGame == true)
        this->window->draw(this->endGameText);

    this->window->display();
}

//Functions
