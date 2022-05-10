#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>

class AnimatedAsset : public sf::Sprite{
public:
    float up_edge, down_edge, left_edge, right_edge, up, down, left, right, t_;
    int speedX, speedY, fps_;
    unsigned int fragments_index = 0;
    std::vector<sf::IntRect> running_frames;

    void setWindowBounds(const float& up_edge_, const float& down_edge_, const float& left_edge_, const float& right_edge_){
        up_edge = up_edge_;
        down_edge = down_edge_;
        left_edge = left_edge_;
        right_edge = right_edge_;
    }

    void setAssetBounds(){
        up = getGlobalBounds().top;
        down = getGlobalBounds().top+getGlobalBounds().height;
        left = getGlobalBounds().left;
        right = getGlobalBounds().left+getGlobalBounds().width;
    }

    void ifEdge(){

        setAssetBounds();

        if(left > right_edge) setPosition(0,getPosition().y);

        else if(left < 0) setPosition(right_edge,getPosition().y);

        if(up<0) setPosition(getPosition().x,down_edge) ;

        else if(up>down_edge) setPosition(getPosition().x,0);
    }



    void VerticalSpeed(const int speed){ speedY = speed; };

    void HorizontalSpeed(const int speed){ speedX = speed; };

    void ContinousAnimation(const sf::Time &elapsed)
    {
        float dt = elapsed.asSeconds();
        t_ = t_ + dt;

        if(t_ > 1.0/fps_)
        {
            fragments_index++;
            t_ = 0.0;
            if(fragments_index == running_frames.size())
            {
                fragments_index = 0;
            }
        }
        setTextureRect(running_frames[fragments_index]);
    }

    void addAnimationFrame(const sf::IntRect& frame)
    {
        if(running_frames.size() >= 6)
        {
            running_frames.erase(running_frames.begin(),running_frames.end());
        }
        running_frames.emplace_back(frame);
    }

    void Animate (const sf::Time &elapsed)
    {
        float dt = elapsed.asSeconds();
        t_ = t_ + dt;

        if(t_ > 1.0/fps_)
        {
            fragments_index++;
            t_ = 0.0;
            if(fragments_index == running_frames.size())
            {
                fragments_index = 0;
            }
        }
        setTextureRect(running_frames[fragments_index]);
    }

};

class Hero : public AnimatedAsset{
public:

    sf::Texture texture_;

    float d_ = 0.0, t_ = 0.0, goalX, goalY;
    int fps_;

    Hero(const int fps, const std::string& path): fps_(fps)
    {
        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << std::endl;
        }
        setTexture(texture_);
        setTextureRect(sf::IntRect(60, 0, 30, 37));
        setPosition(200,200);
    }


    void SetTarget (sf::Vector2i &mouse_position){
        goalX = mouse_position.x;
        goalY = mouse_position.y;


    }

    void GoToTarget(sf::Time &elapsed, int &m){
        sf::FloatRect heroBounds = getGlobalBounds();
        std::cout << heroBounds.top << std::endl;
        float time = elapsed.asSeconds();
        if (heroBounds.top-goalY >= abs(heroBounds.top-goalY)){

            move(0,speedY*time*-1);
       }
        else {
            move(0,speedY*time);
        };

        if (heroBounds.left-goalX >= abs(heroBounds.left-goalX)){
            move(speedX*time*-1,0);
            m = 1;

        }
        else {
            move(speedX*time,0);

            m = 2;
        }
    };
};

class Monster : public AnimatedAsset{
public:

    sf::Texture texture_;

    float d_ = 0.0, t_ = 0.0, goalX, goalY;
    int fps_;

    Monster(const int fps, const std::string& path): fps_(fps)
    {
        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << std::endl;
        }
        setTexture(texture_);
        setTextureRect(sf::IntRect(60, 0, 30, 37));
        setPosition(200,200);
    }



};
class Swamp : public AnimatedAsset{
public:

    sf::Texture texture_;

    float d_ = 0.0, t_ = 0.0, goalX, goalY;
    int fps_;

    Swamp(const int fps, const std::string& path): fps_(fps)
    {
        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << std::endl;
        }
        setTexture(texture_);
        setTextureRect(sf::IntRect(60, 0, 30, 37));
        setPosition(200,200);
    }



};

int main()
{
    bool a = true;
    int m = 0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    sf::Texture texture_wall;
    if(!texture_wall.loadFromFile("C:/Users/agama/Desktop/Szkola/Qt Projects/semester 2/polymorphism_0_textures/wall.png")) { return 1; };



    Hero hero(10, "C:/Users/agama/Desktop/Szkola/Qt Projects/semester 2/build-platformer-Desktop_Qt_6_3_0_MinGW_64_bit-Debug/release/character.png");
    hero.setWindowBounds(0, window.getSize().x, 0, window.getSize().y);
    hero.VerticalSpeed(250);
    hero.HorizontalSpeed(250);

    sf::Clock clock;

    hero.setScale(1.5,1.5);
    hero.addAnimationFrame(sf::IntRect(160, 0, 30, 37));
    hero.addAnimationFrame(sf::IntRect(210, 0, 30, 37));
    hero.addAnimationFrame(sf::IntRect(260, 0, 30, 37));
    hero.addAnimationFrame(sf::IntRect(310, 0, 30, 37));
    hero.addAnimationFrame(sf::IntRect(360, 0, 30, 37));
    hero.addAnimationFrame(sf::IntRect(410, 0, 30, 37));


    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
         sf::Vector2i position = sf::Mouse::getPosition(window);
         if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
         hero.SetTarget(position);
         hero.GoToTarget(elapsed, m);
         }
         hero.ifEdge();
        if(a == true)
        {
             hero.addAnimationFrame(sf::IntRect(40, 0, -30, 37));
             hero.addAnimationFrame(sf::IntRect(40, 0, -30, 37));
             hero.addAnimationFrame(sf::IntRect(40, 0, -30, 37));
             hero.addAnimationFrame(sf::IntRect(40, 0, -30, 37));
             hero.addAnimationFrame(sf::IntRect(40, 0, -30, 37));
             hero.addAnimationFrame(sf::IntRect(40, 0, -30, 37));
        }
        if(m == 2)
        {
            a = false;
            hero.addAnimationFrame(sf::IntRect(160, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(210, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(260, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(310, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(360, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(410, 0, 30, 37));
        }
        else if(m == 1)
        {
            a = true;
            hero.addAnimationFrame(sf::IntRect(190, 0, -30, 37));
            hero.addAnimationFrame(sf::IntRect(240, 0, -30, 37));
            hero.addAnimationFrame(sf::IntRect(290, 0, -30, 37));
            hero.addAnimationFrame(sf::IntRect(340, 0, -30, 37));
            hero.addAnimationFrame(sf::IntRect(390, 0, -30, 37));
            hero.addAnimationFrame(sf::IntRect(440, 0, -30, 37));
        }
        else if(a == false)
        {
            hero.addAnimationFrame(sf::IntRect(10, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(10, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(10, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(10, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(10, 0, 30, 37));
            hero.addAnimationFrame(sf::IntRect(10, 0, 30, 37));
        }

        window.clear(sf::Color::Black);

        sf::Texture texture;
        if (!texture.loadFromFile("C:/Users/agama/Desktop/Szkola/Qt Projects/semester 2/polymorphism_0_textures/grass.png")) {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }

        texture.setRepeated(true);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));

        hero.Animate(elapsed);


        window.draw(sprite);
        window.draw(hero);


        window.display();
    }
    return 0;
}
