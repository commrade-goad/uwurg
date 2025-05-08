#include "GameBot.hpp"
#include "../Object/ObjBead.hpp"
#include "GameUtils.hpp"

std::optional<PossibleMove> _ingame_bot_think(Game *game) {
    TraceLog(LOG_INFO, "called the _ingame_bot_think");
    static const std::array<MoveType, 3> moveRank = {FINISH, MOVEBEAD, NEWBEAD};

    // Only do stuff if player2
    // NOTE: For now this will be enabled but in the future handle this
    // outside of this function because its make sense.
    if (game->mTurn != GameTurn::PLAYER2 || !game->mVSBot)
        return {};

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
        TraceLog(LOG_INFO, "WIP: Still didnt work.");
        break;
    case MoveType::NEWBEAD:
        a->mPos = move.mNewPos;
        a->mOut = true;
        a->mShow = true;
        break;
    case MoveType::MOVEBEAD:
        TraceLog(LOG_INFO, "WIP: Still didnt work.");
        break;
    default:
        break;
    }
    _ingame_getdice(game);
    if (!move.mExtraTurn)
        game_change_turn(game);
    else
        game->mPosMove = get_possible_move(game);
}
