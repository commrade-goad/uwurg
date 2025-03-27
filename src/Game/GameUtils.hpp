#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game.hpp"
#include "../Object/ObjButton.hpp"
#include "../Object/ObjText.hpp"

// Utility or all of the misc function that used on Game.cpp

void _create_menu_object(Game *game, int *z_index);
void _create_ingame_object(Game *game, int *z_index);
void _create_settings_object(Game *game, int *z_index);

void _position_menu_object(Game *game);
void _position_settings_object(Game *game);

void _render_version(Game *game);
void _center_board(Game *game);
void _change_text_from_obj(Game *game, const char *obj_name, const char *new_str);

#endif // GAME_UTILS_H_
