#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

class AnimatedSprite : public sf::Sprite {
public:
    AnimatedSprite(const int fps, const std::string& path) : fps_(fps)//make an initializer list for fps_
    {
        sf::Texture texture;
        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << path << std::endl;
        }
        setTexture(texture_);
        setTextureRect(sf::IntRect(50, 0, 50, 37));
    }
    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }
    void animate(const sf::Time &elapsed){
        bouncce();
        float dt = elapsed.asSeconds();
        move(x_speed_*dt,y_speed_*dt);
        rotate(ro_speed_*dt);
    }
    void jump(const sf::Time &elapsed) {
        float dt = elapsed.asSeconds();
        int g = -20;
        bouncce();
        move(0,0.5 * g * pow(dt,2));
    }
    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }
    void add_animation_frame(const sf::IntRect& frame){
        running_frames.emplace_back(frame);
    }
    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key, std::vector<sf::Sprite> &hearts)  {
        float dt = elapsed.asSeconds();
        if(key == sf::Keyboard::Up) {
            y_speed_ = -1*abs(y_speed_);
            bouncce();
            hearts.size();
            move(0, y_speed_ * dt);
        }
        else if(key == sf::Keyboard::Down)  {
            y_speed_ = abs(y_speed_);
            bouncce();
            move(0, y_speed_ * dt);
        }
        else if(key == sf::Keyboard::Left)  {
            t_ += dt;
            if(t_ > 1.0/fps_){
                fragments_index++;
                t_ = 0.0;
            }
            if(fragments_index == running_frames.size()){
                fragments_index = 0;
            }
            setTextureRect(running_frames[fragments_index]);
            x_speed_ = -1*abs(x_speed_);
            //            bouncce();
            move(x_speed_ * dt, 0);
        }
        else if(key == sf::Keyboard::Right)  {
            t_ += dt;
            if(t_ > 1.0/fps_){
                fragments_index++;
                t_ = 0.0;
            }
            if(fragments_index == running_frames.size()){
                fragments_index = 0;
            }
            setTextureRect(running_frames[fragments_index]);
            x_speed_ = abs(x_speed_);
            bouncce();
            move(x_speed_ * dt, 0);
        }
    }
private:
    sf::Texture texture_;
    int fps_;
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;
    float t_ = 0.0;
    unsigned int fragments_index = 0;
    std::vector<sf::IntRect> running_frames;

    void bouncce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();
        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }
        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
        }
        if(rectangle_bounds.left <= l_bound_ ){
            x_speed_ = abs(x_speed_);
        }
        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) ;
        }
    }
};
int main()
{
    srand(time(NULL));
//    float move_rocket = 0.8;
    float move_background = 0.08;
    float scale;
    int level = 0;
    float score = 0;
    //    int fiu = 0;
    sf::SoundBuffer buffer, screen, collide, game_over;
    buffer.loadFromFile("bonus.wav");
    screen.loadFromFile("intro.wav");
    collide.loadFromFile("collide.wav");
    game_over.loadFromFile("gameover.wav");

    sf::Sound sound_buffer, sound_screen, sound_collide, sound_gameover;
    sound_buffer.setBuffer(buffer);
    sound_screen.setBuffer(screen);
    sound_collide.setBuffer(collide);
    sound_gameover.setBuffer(game_over);

    sf::Texture texture, texture_rock, texture_heart, texture_diamond, texture_gameover;
    texture.loadFromFile("background.png");
    texture_rock.loadFromFile("rocks.png");
    texture_diamond.loadFromFile("diamond.png");
    texture_gameover.loadFromFile("gameover.png");
    texture_heart.loadFromFile("heart.png");

    std::vector<sf::Sprite> hearts;
    sf::Sprite heart;
    heart.scale(0.06, 0.06);
    heart.setTexture(texture_heart);

    heart.setPosition(sf::Vector2f(850, 35));
    hearts.push_back(heart);
    heart.setPosition(sf::Vector2f(880, 35));
    hearts.push_back(heart);
    heart.setPosition(sf::Vector2f(910, 35));
    hearts.push_back(heart);
    heart.setPosition(sf::Vector2f(940, 35));
    hearts.push_back(heart);

    sf::Sprite gameover;
    gameover.setTexture(texture_gameover);
    gameover.setScale(2.8, 2.6);

    sf::Sprite background;
    sf::Vector2f background_position(0, -2950);
    background.setPosition(background_position);
    background.setTexture(texture);
    background.setScale(sf::Vector2f(3.67, 3.16));

    sf::Sprite rock[800];
    for (int i = 0; i < 800; i++) {
        scale = (rand() % 14 + 4) * 0.006;
        rock[i].setTexture(texture_rock);
        rock[i].setScale(scale, scale);
        rock[i].setPosition(sf::Vector2f(rand() % 1000, rand() % 90000000 * (-1)));
    }
    sf::Sprite diamond[25];
    for (int i = 0; i < 25; i++) {
        diamond[i].setTexture(texture_diamond);
        diamond[i].setScale(sf::Vector2f(0.1, 0.1));
        diamond[i].setPosition(sf::Vector2f(rand() % 1000, rand() % 900000 * (-1)));
    }
    sf::Font font;
    font.loadFromFile("fn.otf");

    sf::Text text, score_, point_, points, scores;
    text.setFont(font);
    text.setString("WELCOME. LET'S RIDE!!! press Enter");
    text.setCharacterSize(50);
    text.setPosition(50, 700);
    text.setFillColor(sf::Color::Red);

    score_.setFont(font);
    score_.setFillColor(sf::Color::Red);
    score_.setCharacterSize(50);
    score_.setString("SCORE:");
    score_.setPosition(180, 820);

    point_.setFont(font);
    point_.setCharacterSize(50);
    point_.setFillColor(sf::Color::Blue);
    point_.setPosition(480, 820);

    points.setFont(font);
    points.setCharacterSize(20);
    points.setFillColor(sf::Color::Blue);
    points.setPosition(800, 10);
    points.setString("POINTS:");

    scores.setFont(font);
    scores.setCharacterSize(20);
    scores.setFillColor(sf::Color::Red);
    scores.setPosition(900, 10);

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(1000, 900), "Dodge and Kill");
    std::srand(std::time(nullptr));
    sf::FloatRect new_Pos_;
    sf::Vector2f vel_;

    AnimatedSprite hero(10, "Character\\character.png");
    hero.setBounds(0, window.getSize().x, 0, window.getSize().y);
    hero.setSpeed(350,350,150);
    hero.setPosition(440, 750);

    hero.add_animation_frame(sf::IntRect(150, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(200, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(250, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(300, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(350, 0, 50, 37)); // hero running frame 1
    hero.add_animation_frame(sf::IntRect(400, 0, 50, 37)); // hero running frame 1

    while (window.isOpen()) {
        hero.setTextureRect(sf::IntRect(50, 0, 50, 37));
        hero.setScale(1.8,1.8);
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Keyboard::Key pressed;
        if(event.type == sf::Event::KeyPressed) {
            pressed = event.key.code;
            sf::FloatRect heroBounds = hero.getGlobalBounds();
            new_Pos_ = heroBounds;
            heroBounds.left += vel_.x;
            heroBounds.top += vel_.y;
            if (heroBounds.left >= window.getSize().x) {
                hero.setPosition(10, heroBounds.top);
            }
            if (heroBounds.left <= 0) {
                hero.setPosition(window.getSize().x, heroBounds.top);
            }
                    hero.moveInDirection(elapsed,pressed,hearts);
        }
        background_position.y = background_position.y + move_background;
        background.setPosition(background_position);
        window.clear(sf::Color::Black);
        for (size_t j = 0; j < hearts.size(); j--) {
            if (level == 0) {
                sound_screen.play();
                window.draw(background);
                window.draw(hero);
                window.draw(text);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && level < 2) level = 1;
            if (level == 1) {
            for (int i = 0; i < 800; i++)  {
                rock[i].getGlobalBounds();
                if (rock[i].getGlobalBounds().intersects(hero.getGlobalBounds())) {
                    rock[i].setPosition(1000,1000);
                    hearts.pop_back();
                    sound_collide.play();
                    break;
                }
            }
                for (int i = 0; i < 25; i++) {
                    diamond[i].getGlobalBounds();
                    if (diamond[i].getGlobalBounds().intersects(hero.getGlobalBounds())) {
                        score = score + 100;
                        diamond[i].scale(0.0001, 0.0001);
                        hearts.push_back(heart);
                        sound_buffer.play();
                        break;
                    }
                }
                score = score + 0.01;
                window.draw(background);
                window.draw(hero);
                for (int k = 0; k < 800; k++) {
                    sf::Vector2f rock_position(rock[k].getPosition());
                    rock[k].setPosition(rock_position.x, rock_position.y + 0.8);
                    window.draw(rock[k]);
                }
                for (int k = 0; k < 25; k++) {
                    sf::Vector2f diamond_position(diamond[k].getPosition());
                    diamond[k].setPosition(diamond_position.x, diamond_position.y + 0.8);
                    window.draw(diamond[k]);
                }
                for(auto &heart_ : hearts) {
                    window.draw(heart_);
                }
                window.draw(points);
                scores.setString(std::to_string(score));
                window.draw(scores);
                if (hearts.size() == 0) {
                    sound_gameover.play();
                    break;
                }
            }
        }
        if (hearts.size() == 0) {
            window.draw(background);
            window.draw(gameover);
            window.draw(score_);
            point_.setString(std::to_string(score));
            window.draw(point_);
//            sound_gameover.play();
            // AFTER ENTER SOUND
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && hearts.size() == 0) {
            while (true) {
                window.close();
            }
        }
        window.display();
    }
    return 0;
}

