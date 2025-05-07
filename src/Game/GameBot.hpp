#ifndef GAMEBOT_H_
#define GAMEBOT_H_

#include "Game.hpp"

std::optional<PossibleMove> _ingame_bot_think(Game *game);
void _ingame_bot_move(Game *game, PossibleMove posMove);

#endif // GAMEBOT_H_
