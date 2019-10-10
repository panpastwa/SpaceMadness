#ifndef KOLEJNAGRA_BULLET_PLAYER_H
#define KOLEJNAGRA_BULLET_PLAYER_H

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

#endif //KOLEJNAGRA_BULLET_PLAYER_H
