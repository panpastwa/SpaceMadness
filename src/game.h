#ifndef KOLEJNAGRA_GAME_H
#define KOLEJNAGRA_GAME_H

#endif //KOLEJNAGRA_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include "Enemy.h"
#include "Bullet_player.h"
#include "Bullet_enemy.h"
#include "Bonus.h"
#include "menu.h"


int game(sf::RenderWindow &window, int level, int points_collected);