#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "../def.hpp"
#include "../Object/Object.hpp"
#include <vector>

struct PossibleMove {
  public:
    sptr_t<Object> mBead;
    int mPossibleMove;

    PossibleMove();
    PossibleMove(sptr_t<Object> bead, int possibleMove);
    ~PossibleMove();
};

std::vector<PossibleMove> get_possible_move(Game *game);

#endif // GAMEPLAY_H_
