#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "../Object/Object.hpp"
#include "../def.hpp"
#include "GameTurn.hpp"
#include <optional>
#include <vector>

enum class MoveType {
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
void move_bot_wrapper(Game *game);
std::optional<GameTurn> game_check_win(Game *game);

#endif // GAMEPLAY_H_
