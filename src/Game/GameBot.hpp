#ifndef GAMEBOT_H_
#define GAMEBOT_H_

#include "Game.hpp"

struct GameBot {
  public:
    Game *mGame_ptr;
    std::optional<PossibleMove> mSelectedMove;
    double mTimer;
    double mCurrentTime, mStartTime;

    GameBot(double delay);
    ~GameBot();
    bool bot_think();
    void bot_move();

    bool check_timer();
    void start_timer();
    void reset_timer();
};


#endif // GAMEBOT_H_
