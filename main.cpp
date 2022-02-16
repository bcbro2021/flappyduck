// imports
#include <SFML/Graphics.hpp>
#include <iostream>
#include "classes.h"

int main()
{
    // window
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH,WIN_HEIGHT),"Flappy Duck");
    window.setFramerateLimit(MAX_FPS);

    // bird
    Bird duck;
    // ground
    Ground ground;
    //pipes
    Pipe pipe;

    // score
    sf::Font font;
    if (!font.loadFromFile("assets/font.ttf")){
        std::cout << "Font not loaded!" << std::endl;
    }
    sf::Text scoretext;
    int score;
    int scoreadd = 1;
    sf::Vector2f center(WIN_WIDTH/2-40,WIN_HEIGHT/2);
    scoretext.setFont(font);
    scoretext.setCharacterSize(44);
    scoretext.setFillColor(sf::Color::White);
    scoretext.setPosition(center);
    scoretext.setString(std::to_string(score));

    int state = 1;
    // game loop
    while(window.isOpen())
    {
        if (state == 0){
            // bird update
            duck.update();
            if(duck.collision(ground.getSprite())) state = 1;
            if(duck.collision(pipe.p1)) state = 1;
            if(duck.collision(pipe.p2)) state = 1;
            // pipe update
            pipe.update();

            // events
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            if (scoreadd == 1){
                if (pipe.pos1.x <= duck.pos.x){
                    score += 1;
                    scoretext.setPosition(center);
                    scoretext.setString(std::to_string(score));
                    scoreadd = 0;
                }
            }
            if (pipe.pos1.x > duck.pos.x){
                scoreadd = 1;
            }
            // drawing
            window.clear(sf::Color::Cyan);
            window.draw(scoretext);
            window.draw(duck.sprite);
            window.draw(pipe.p1);
            window.draw(pipe.p2);
            window.draw(ground.getSprite());
            window.display();
        }
        else if (state == 1){
            duck.pos.x = 360;
            duck.pos.y = 270;
            duck.sprite.setScale(4,4);
            duck.sprite.setPosition(duck.pos);

            // mouse clicked on duck?
            if (duck.sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)){
                duck.sprite.setColor(sf::Color(200,200,200));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    score = 0;
                    scoretext.setString(std::to_string(score));
                    duck.sprite.setColor(sf::Color::White);
                    duck.reset();
                    pipe.reset();
                    state = 0;
                }
            }
            else duck.sprite.setColor(sf::Color::White);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            window.clear(sf::Color::Cyan);
            window.draw(duck.sprite);
            window.display();
        }
            
    }
    return 0;
}