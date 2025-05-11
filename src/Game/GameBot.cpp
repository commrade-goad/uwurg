#include "GameBot.hpp"
#include "../Object/ObjBead.hpp"
#include "GameUtils.hpp"

std::optional<PossibleMove> _ingame_bot_think(Game *game) {
    static const std::array<MoveType, 3> moveRank = {FINISH, MOVEBEAD, NEWBEAD};

    std::vector<PossibleMove> &pm = game->mPosMove;
    if (pm.size() <= 0)
        return {};

    for (const MoveType move : moveRank) {
        for (const PossibleMove &m : pm) {
            if (move == m.mType) {
                return m;
            }
        }
    }
    return {};
}

// TODO: Finish this.
void _ingame_bot_move(Game *game, PossibleMove move) {
    auto a = std::dynamic_pointer_cast<ObjBead>(move.mBead);
    switch (move.mType) {
    case MoveType::FINISH:
        a->mOut = false;
        a->mShow = false;
        a->mPos = 10000;
        game->mScore[(int)game->mTurn] += 1;
        break;
    case MoveType::NEWBEAD:
        a->mPos = move.mNewPos;
        a->mOut = true;
        a->mShow = true;
        break;
    case MoveType::MOVEBEAD:
        a->mPos = move.mNewPos;
        if (sptr_t<ObjBead> en_obj =
                std::dynamic_pointer_cast<ObjBead>(move.mEnBead)) {
            en_obj->mPos = 0;
            en_obj->mOut = false;
        }
        break;
    default:
        if (game->mDice <= 0 || game->mPosMove.empty()) {
            _ingame_getdice(game);
            game_change_turn(game);
        }
        break;
    }
    _ingame_getdice(game);
    if (!move.mExtraTurn)
        game_change_turn(game);
    else
        game->mPosMove = get_possible_move(game);
}
