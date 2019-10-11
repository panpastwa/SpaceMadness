#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"
#include "game.h"

int main()
{
    // Rendering window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
    window.setFramerateLimit(30);

    // Playing music
    sf::Music music;
    music.openFromFile("data/music.wav");
    music.setLoop(true);
    music.play();

    // Game loop
    while (window.isOpen())
    {
        menu(window);
        int points = 0;
        for(int i=0; i<10; i++)
            if (points != -1)
                points = game(window, i+1, points);
    }
    return 0;
}
