#include "Enemy.h"

void Enemy::create(){
    x = rand()%600 + 100;
    y = rand()%250 + 50;
    speed = rand()%11 - 5;
    collision_state = 0;
    shoot_frequency = rand()% 20 + 50;
    shoot_counter = 0;
    enemy.loadFromFile("data/enemy0.png");
    boomA.loadFromFile("data/boom0A.png");
    boomB.loadFromFile("data/boom0B.png");
    boomC.loadFromFile("data/boom0C.png");
    boomD.loadFromFile("data/boom0D.png");
    font.loadFromFile("data/arial.ttf");
    points_added.setString("+ 15");
    points_added.setFont(font);
    points_added.setCharacterSize(20);
    points_added.setFillColor(sf::Color::White);
    sEnemy.setTexture(enemy);
    sEnemy.setPosition(x, y);
}

bool Enemy::check_collision(sf::FloatRect entity){
    sf::FloatRect boundingBox = sEnemy.getGlobalBounds();
    if (boundingBox.intersects(entity))
    {
        std::cout << "Collision with entity!\n";
        collision_state = 1;
        return true;
    }
    return false;
}

void Enemy::move() {
    x += speed;
    shoot_counter++;
    if (x < 10)
        speed *= -1;
    if (x > 800 - 37 - 10)
        speed *= -1;
    sEnemy.setPosition(x, y);
}

void Enemy::boom_animation(int n) {
    points_added.setPosition(x, y-20);
    switch (n){
        case 1:
            sEnemy.setTexture(boomA);
            break;
        case 2:
            sEnemy.setTexture(boomB);
            break;
        case 3:
            sEnemy.setTexture(boomC);
            break;
        case 4:
            sEnemy.setTexture(boomD);
            break;
        default:
            std::cout << "Error! Wrong value to boom animation!\n";
            break;
    }
}
