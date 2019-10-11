#include "menu.h"

void menu(sf::RenderWindow &window)
{
    // Variable controlling the flow of information
    std::string showing_now = "menu";

    // Loading best scores from text file
    std::fstream score_file;
    score_file.open("data/score.txt", std::ios::in);
    std::string best_score, line;
    for(int i=0; i<3; i++){
        getline(score_file, line);
        best_score += std::to_string(i+1)+ ".\t" + line + "\n";
    }

    // Loading font
    sf::Font font;
    font.loadFromFile("data/arial.ttf");

    // Preparing best scores texts to show
    sf::Text text;
    text.setFont(font);
    text.setString(best_score);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(280, 130);
    text.setStyle(sf::Text::Bold);

    // Loading and assigning a texture
    sf::Texture background_menu,background_scores;
    background_menu.loadFromFile("data/background_menu.png");
    background_scores.loadFromFile("data/background_scores.png");
    sf::Sprite sBackground(background_menu);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // Getting position of a cursor
                sf::Vector2i position = sf::Mouse::getPosition(window);

                // Act accordingly if in menu section
                if (showing_now == "menu")
                {
                    if (position.x > 280 && position.x < 200+280 && position.y > 170 && position.y < 170 + 90) {
                        showing_now = "game";
                        return;
                    }
                    if (position.x > 220 && position.x < 220+370 && position.y > 285 && position.y < 285 + 85)
                    {
                        showing_now = "scores";
                        sBackground.setTexture(background_scores);
                    }
                    if(position.x > 300 && position.x < 300+150 && position.y > 400 && position.y < 400+75)
                    {
                        window.close();
                    }
                }
                // Act accordingly if in best scores section
                else if (showing_now == "scores")
                {
                    if (position.x > 56 && position.x < 182 + 56 && position.y > 377 &&
                        position.y < 112 + 377){
                        showing_now = "game";
                        return;
                    }
                    if (position.x > 538 && position.x < 162 + 538 && position.y > 387 &&
                        position.y < 387 + 91) {
                        window.close();
                    }
                }
            }
        }
        // Drawing //
        window.clear();
        window.draw(sBackground);
        if (showing_now == "scores")
            window.draw(text);
        window.display();
    }
}
