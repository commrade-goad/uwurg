#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game.hpp"
#include "../Object/ObjButton.hpp"
#include "../Object/ObjText.hpp"

// Utility or all of the misc function that used on Game.cpp

void _create_menu_object(Game *game, int *z_index);
void _position_menu_object(Game *game);
void _create_settings_object(Game *game, int *z_index);
void _render_version(Game *game);
void _center_board(Game *game, sptr_t<Object> object);

#endif // GAME_UTILS_H_
