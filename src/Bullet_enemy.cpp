#include "Bullet_enemy.h"

void Bullet_enemy::create(int location_x, int location_y) {
    x = location_x;
    y = location_y;
    exists = true;
    sBullet.setRadius(5);
    sBullet.setPosition(x, y);
    sBullet.setFillColor(sf::Color::Black);
}

void Bullet_enemy::move() {
    y += speed;
    if (y > 610)
        exists = false;
    sBullet.setPosition(x, y);
}