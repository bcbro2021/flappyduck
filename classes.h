#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

// constants
int WIN_WIDTH = 800;
int WIN_HEIGHT = 600;
int MAX_FPS = 60;

class Bird{
    public:
        sf::Sprite sprite;
        sf::Texture tex;
        sf::Texture tex2;
        sf::Vector2f pos;
        int vel = 0;
        int dead = 0;
        Bird(){
            reset();
        }
        void reset(){
            // bird texture
            tex.loadFromFile("assets/bird1.png");
            tex2.loadFromFile("assets/bird2.png");
            // bird sprite
            pos.x = 150.f;
            pos.y = 300.f;
            sprite.setScale(1.8,1.8);
            sprite.setTexture(tex);
        }
        void update()
        {
            // update bird position
            if (dead == 0)
            {
                if (vel < 5)
                {
                    vel += 1;
                }
                else 
                {
                    vel = 5;
                    sprite.setTexture(tex2);
                }

                if (pos.y > 0)
                {
                    if (pos.y >= WIN_HEIGHT - sprite.getScale().y) 
                    {
                        kill();
                    }
                    else 
                    {
                        if (0 <= vel && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        {
                            vel = -10;
                            sprite.setTexture(tex);
                        }
                    }
                }
                pos.y += vel;
            }
            else 
            {
                std::cout << "dead" << std::endl;
            }
            sprite.setPosition(pos);
        }
        int collision(sf::Sprite rect)
        {
            if (sprite.getGlobalBounds().intersects(rect.getGlobalBounds())) return 1;
            else return 0;
        }

        void kill()
        {
            vel = 0;
            dead = 1;
        }
};

class Ground
{
    public:
        sf::Vector2f pos;
        sf::Texture groundtex;
        sf::Sprite ground;
        Ground()
        {
            groundtex.loadFromFile("assets/ground.png");
            ground.setTexture(groundtex);
            pos.x = 0;
            pos.y = WIN_HEIGHT-50;
            ground.setPosition(pos);
        }
        sf::Sprite getSprite()
        {
            return ground;
        }
};

class Pipe
{
    public:
        sf::Vector2f pos1;
        sf::Vector2f pos2;
        sf::Texture pipetex;
        sf::Sprite p1;
        sf::Sprite p2;
        int gap = 150;
        int min = 150;
        int max = 450;
        Pipe()
        {
            reset();
        }
        void reset()
        {
            pipetex.loadFromFile("assets/pipe.png");
            p1.setTexture(pipetex);
            p2.setTexture(pipetex);
            p1.setScale(1,-1);
            pos1.x = WIN_WIDTH + 51;
            pos2.x = WIN_WIDTH + 51;

            int pos = min + static_cast <int> (rand()) / ( static_cast <int> (RAND_MAX/(max-min)));
            pos1.y = pos - gap;
            pos2.y = pos;
        }
        void update()
        {
            pos1.x -= 7;
            pos2.x -= 7;

            int pos = min + static_cast <int> (rand()) / ( static_cast <int> (RAND_MAX/(max-min)));
            if (pos1.x <= 0 - 51) {
                pos1.x = WIN_WIDTH + 51;
                pos2.x = WIN_WIDTH + 51;
                pos1.y = pos - gap;
                pos2.y = pos;
            }

            p1.setPosition(pos1);
            p2.setPosition(pos2);
        }
};