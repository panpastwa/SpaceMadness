#include "Bonus.h"

void Bonus::create(int location_x, int location_y, int n) {
    x = location_x;
    y = location_y;
    speed = (n + 1) * 3;
    exists = true;
    show_text_counter = 0;
    font.loadFromFile("arial.ttf");
    points_added.setString("+ " + std::to_string(speed * 5));
    points_added.setFont(font);
    points_added.setCharacterSize(20);
    points_added.setFillColor(sf::Color::White);
    switch (n)
    {
        case 0:
            texture.loadFromFile("fruit0.png");
            break;
        case 1:
            texture.loadFromFile("fruit1.png");
            break;
        case 2:
            texture.loadFromFile("fruit2.png");
            break;
        default:
            std::cout << "Wrong argument to create fruit!\n";
            break;
    }
    sFruit.setTexture(texture);
    sFruit.setPosition(x, y);
}

void Bonus::move() {
    y += speed;
    sFruit.setPosition(x, y);
    if (y > 610)
        exists = false;
}