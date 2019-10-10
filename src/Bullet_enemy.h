#ifndef KOLEJNAGRA_BULLET_ENEMY_H
#define KOLEJNAGRA_BULLET_ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet_enemy {
public:
    int x;
    int y;
    int speed = 5;
    bool exists = false;
    sf::CircleShape sBullet;

    void create(int location_x, int location_y);
    void move();
};


#endif //KOLEJNAGRA_BULLET_ENEMY_H
