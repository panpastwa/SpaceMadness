#include <SFML/Graphics.hpp>
#include <iostream>

class Bonus {
public:
    int x;
    int y;
    int speed;
    int show_text_counter;
    bool exists = false;
    sf::Texture texture;
    sf::Sprite sFruit;
    sf::Font font;
    sf::Text points_added;


    void create(int location_x, int location_y, int n);
    void move();
};
