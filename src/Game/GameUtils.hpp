#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game.hpp"
#include "../Object/ObjButton.hpp"
#include "../Object/ObjText.hpp"

// Utility or all of the misc function that used on Game.cpp

void create_menu_object(Game *game, int *z_index);
void position_menu_object(Game *game, Window *w);

#endif // GAME_UTILS_H_
