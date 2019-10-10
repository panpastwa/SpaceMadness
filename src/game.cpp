#include "game.h"

int game(sf::RenderWindow &window, int level, int points_collected)
{
    // Return is window is closed
    if (!window.isOpen())
        return -1;

    // Creating a background and a player
    sf::Texture background, background_over, player, down1, down2, down3, down4;
    background.loadFromFile("background_game.png");
    background_over.loadFromFile("background_over.png");
    player.loadFromFile("player.png");
    down1.loadFromFile("player_down1.png");
    down2.loadFromFile("player_down2.png");
    down3.loadFromFile("player_down3.png");
    down4.loadFromFile("player_down4.png");
    sf::Sprite sBackground, sPlayer;
    sBackground.setTexture(background);
    sPlayer.setTexture(player);
    sPlayer.setOrigin(22, 15);
    sPlayer.setPosition(400-22, 600-20);
    int player_down = 0;
    int points = points_collected;
    int bullet_cooldown = 0;

    // Creating information about current level and points
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text, points_text;

    text.setFont(font);
    text.setCharacterSize(50);
    text.setString("Level " + std::to_string(level));
    text.setFillColor(sf::Color::White);
    text.setPosition(300, 130);

    points_text.setFont(font);
    points_text.setCharacterSize(30);
    points_text.setString(std::to_string(points));
    points_text.setFillColor(sf::Color::White);
    points_text.setPosition(100, 50);

    // Creating an array of enemies
    int number_of_enemies = level *4;
    Enemy array_of_enemies[number_of_enemies];
    for(int i=0; i<number_of_enemies; i++)
    {
        array_of_enemies[i].create();
    }

    // Creating an array of bullets
    struct player_bullets_list{
        player_bullets_list *next;
        Bullet_player shot;
    };
    player_bullets_list *PLAYER_list_of_bullets = NULL;

    Bullet_enemy array_of_enemy_bullets[100];
    int enemy_bullet_counter = 0;

    // Creating an array of bonuses
    Bonus array_of_bonuses[25];
    int bonus_counter = 0;
    int fruits_on_map = 0;

    // Displaying current level
    window.clear();
    window.draw(sBackground);
    window.draw(sPlayer);
    window.draw(text);
    window.display();
    sleep(3);

    while (window.isOpen())
    {
        // Player down, saving score, backing to menu
        if (player_down == 5)
        {
            sleep(1.5);
            sBackground.setTexture(background_over);
            points_text.setCharacterSize(80);
            points_text.setPosition(300, 420);
            window.clear();
            window.draw(sBackground);
            window.draw(points_text);
            window.display();
            std::fstream score_file;
            score_file.open("score.txt", std::ios::in);
            int scores[3];
            std::string line;
            for(int i=0; i<3; i++)
            {
                getline(score_file, line);
                scores[i] = atoi(line.c_str());
                if (points > scores[i])
                {
                    int temp = points;
                    points = scores[i];
                    scores[i] = temp;
                }
            }
            score_file.close();
            score_file.open("score.txt", std::ios::out);
            for(int i=0; i<3; i++)
                score_file << scores[i] << std::endl;
            score_file.close();
            sleep(3);
            return -1;
        }

        // Reducing bullet cooldown
        if (bullet_cooldown > 0)
            bullet_cooldown--;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!bullet_cooldown && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                player_bullets_list *new_bullet = new player_bullets_list;
                new_bullet->shot.create(sPlayer.getPosition().x);
                new_bullet->next = PLAYER_list_of_bullets;
                PLAYER_list_of_bullets = new_bullet;
                bullet_cooldown = 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (sPlayer.getPosition().x > 30)
                    sPlayer.move(-4, 0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (sPlayer.getPosition().x < 799-30)
                    sPlayer.move(4, 0);
            }
        }

        // Movement //
        // Enemy ships
        for(int i=0; i<number_of_enemies; i++)
        {
            // Animation of boom!
            if (array_of_enemies[i].collision_state)
            {
                if (array_of_enemies[i].collision_state == 4)
                    continue;
                else
                {
                    if (array_of_enemies[i].collision_state == 1)
                    {
                        points += 15;
                        points_text.setString(std::to_string(points));
                        if (bonus_counter == 24)
                            bonus_counter = 0;
                        if (rand()%2 == 0)
                            array_of_bonuses[bonus_counter++].create(array_of_enemies[i].x, array_of_enemies[i].y, rand()%3);

                    }
                    array_of_enemies[i].boom_animation(array_of_enemies[i].collision_state++);

                }
            }
            // Checking for collision with a bullet
            else
            {
                player_bullets_list *temp = PLAYER_list_of_bullets;
                while (temp){
                    if (!array_of_enemies[i].check_collision(temp->shot.bullet.getGlobalBounds()))
                        temp = temp->next;
                    else
                        break;
                }
            }
            // Creating a bullet
            if (array_of_enemies[i].shoot_counter == array_of_enemies[i].shoot_frequency)
            {
                array_of_enemies[i].shoot_counter = 0;
                if (enemy_bullet_counter == 99)
                    enemy_bullet_counter = 0;
                array_of_enemy_bullets[enemy_bullet_counter++].create(array_of_enemies[i].x, array_of_enemies[i].y);
            }
            array_of_enemies[i].move();
        }

        // Bullets
        {
            // Player's bullets
            player_bullets_list *temp = PLAYER_list_of_bullets;
            int number_of_bullets = 0;
            while (temp) {
                if (temp->next)
                    // Removes bullets with y < 0
                    if (temp->next->shot.y < 0) {
                        player_bullets_list *x = temp->next->next;
                        temp->next = x;
                        delete temp->next;
                    }
                temp->shot.move();
                number_of_bullets++;
                temp = temp->next;
            }
            std::cout << "Number of bullets = " << number_of_bullets << std::endl;
        }

        // Enemy's bullets
        sf::FloatRect boundingBox = sPlayer.getGlobalBounds();
        for (int i=0; i<100; i++)
            if (array_of_enemy_bullets[i].exists)
            {
                if (boundingBox.intersects(array_of_enemy_bullets[i].sBullet.getGlobalBounds()) && !player_down)
                    player_down = 1;
                array_of_enemy_bullets[i].move();
            }

        // Updating fruits
        fruits_on_map = 0;
        for (int i=0; i<25; i++)
            if (array_of_bonuses[i].exists)
            {
                if (boundingBox.intersects(array_of_bonuses[i].sFruit.getGlobalBounds()))
                {
                    array_of_bonuses[i].exists = false;
                    array_of_bonuses[i].show_text_counter = 7;
                    array_of_bonuses[i].points_added.setPosition(sPlayer.getPosition().x-15, 530);
                    points += array_of_bonuses[i].speed * 5;
                    points_text.setString(std::to_string(points));
                }
                array_of_bonuses[i].move();
                fruits_on_map++;
            }

        // Animation of player down
        if (player_down)
        {
            switch(player_down)
            {
                case 1:
                    sPlayer.setTexture(down1);
                    break;
                case 2:
                    sPlayer.setTexture(down2);
                    break;
                case 3:
                    sPlayer.setTexture(down3);
                    break;
                case 4:
                    sPlayer.setTexture(down4);
                    break;
                default:
                    std::cout << "Error while animating player down\n";
                    break;
            }
            player_down++;
        }

        // Drawing //
        window.clear();
        window.draw(sBackground);

        // Drawing bullets
        player_bullets_list *temp = PLAYER_list_of_bullets;
        while (temp) {
            window.draw(temp->shot.bullet);
            temp = temp->next;
        }
        int draw_bullets = 0;
        for (int i=0; i<100; i++)
        {
            if (array_of_enemy_bullets[i].exists) {
                window.draw(array_of_enemy_bullets[i].sBullet);
                draw_bullets++;
            }
        }
        std::cout << "Draw bullets = " << draw_bullets << std::endl;

        // Drawing enemy ships
        for(int i=0; i<number_of_enemies; i++)
        {
            if (array_of_enemies[i].collision_state != 4)
                window.draw(array_of_enemies[i].sEnemy);
            if (array_of_enemies[i].collision_state > 0 && array_of_enemies[i].collision_state < 4)
                window.draw(array_of_enemies[i].points_added);
        }



        // Drawing fruits
        for (int i=0; i<25; i++)
        {
            if (array_of_bonuses[i].exists)
                window.draw(array_of_bonuses[i].sFruit);
            if (array_of_bonuses[i].show_text_counter > 0)
            {
                window.draw(array_of_bonuses[i].points_added);
                array_of_bonuses[i].show_text_counter--;
            }
        }


        window.draw(sPlayer);
        window.draw(points_text);
        window.display();

        // Returning if level completed
        if (draw_bullets == 0 && fruits_on_map == 0)
        {
            bool level_completed = true;
            for(int i=0; i<number_of_enemies; i++)
                if (array_of_enemies[i].collision_state != 4)
                    level_completed = false;
            if (level_completed)
                return points;
        }
    }
}
