#ifndef GAMEBOT_H_
#define GAMEBOT_H_

#include "Game.hpp"

struct GameBot {
  public:
    Game *mGame_ptr;
    std::optional<PossibleMove> mSelectedMove;
    float mTimer;

    GameBot(double delay);
    ~GameBot();
    bool bot_think();
    void bot_move();
};


#endif // GAMEBOT_H_
