#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game.hpp"
#include "../Object/ObjBead.hpp"

// Utility or all of the misc function that used on Game.cpp

void _create_menu_object(Game *game, int &z_index);
void _create_ingame_object(Game *game, int &z_index);
void _create_settings_object(Game *game, int &z_index);
void _create_play_menu_object(Game *game, int &z_index);
void _create_finish_menu_object(Game *game, int &z_index);
void _create_help_object(Game *game, int &z_index);

void _position_menu_object(Game *game);
void _position_settings_object(Game *game);
void _position_play_menu_object(Game *game);
void _position_finish_menu_object(Game *game);
void _position_help_object(Game *game);

void _render_version(Game *game);
void _position_ingame_object(Game *game);
void _change_text_from_obj(Game *game, const char *obj_name,
                           const char *new_str);
void _recalculate_all_pos(Game *game);
void _window_res_helper(Game *game);
void _change_res_helper(Game *game);
void _window_flag_helper(Game *game);

void _start_game(Game *game, bool vsbot);

void _finish_restart_game(Game *game);
void _finish_exit_main(Game *game);

// IN-GAME FUNCTION
void _ingame_next_turn(Game *game);
void _ingame_getdice(Game *game);
void _vsbot_label_toggle(Game *game);
void _ingame_bead_button_helper(sptr_t<ObjBead> bead, Game *game);

void _ingame_reset_state(Game *game);

#endif // GAME_UTILS_H_
