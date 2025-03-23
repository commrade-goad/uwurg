#ifndef GAMEUTILS_H_
#define GAMEUTILS_H_

#include "Game.hpp"
#include "../Window/Window.hpp"

void Game::_center_n_resize_2_texture_object(const char *obj_name);
void Game::_center_n_resize_2_texture_object(sptr_t<Object> object);
void Game::_sync_scale();

#endif // GAMEUTILS_H_

