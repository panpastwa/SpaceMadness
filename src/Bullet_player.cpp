#include "Bullet_player.h"

void Bullet_player::create(int location_x){
    x = location_x;
    y = 600-31;
    bullet.setSize(sf::Vector2f(3, 10));
    bullet.setPosition(x, y);
}

void Bullet_player::move(){
    y -= speed;
    bullet.setPosition(x, y);
}