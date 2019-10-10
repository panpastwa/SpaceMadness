#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet_player {
public:
    int x;
    int y;
    int speed = 5;
    sf::RectangleShape bullet;

    void create(int x);
    void move();
};
