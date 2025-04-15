#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "../Object/Object.hpp"
#include "../def.hpp"
#include <vector>

enum MoveType {
    NEWBEAD,
    MOVEBEAD,
    FINISH,
};

struct PossibleMove {
  public:
    sptr_t<Object> mBead;
    sptr_t<Object> mEnBead;
    int mNewPos;
    bool mExtraTurn;
    MoveType mType;

    PossibleMove();
    PossibleMove(sptr_t<Object> bead, int possibleMove);
    PossibleMove(sptr_t<Object> bead, int possibleMove, bool extraTurn);
    PossibleMove(sptr_t<Object> bead, int possibleMove, bool extraTurn,
                 MoveType type);
    PossibleMove(sptr_t<Object> bead, int possibleMove, bool extraTurn,
                 MoveType type, sptr_t<Object> enbead);
    ~PossibleMove();
};

std::vector<PossibleMove> get_possible_move(Game *game);

bool game_new_bead_helper(Game *game);
bool game_move_bead_helper(Game *game, int nBead);
void game_change_turn(Game *game);

#endif // GAMEPLAY_H_
