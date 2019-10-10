#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Enemy {
public:
    int x;
    int y;
    int speed;
    int collision_state;
    int shoot_frequency;
    int shoot_counter;
    sf::Texture enemy;
    sf::Sprite sEnemy;
    sf::Texture boomA, boomB, boomC, boomD;
    sf::Font font;
    sf::Text points_added;

    void create();
    bool check_collision(sf::FloatRect entity);
    void move();
    void boom_animation(int n);

};
