#include "GameBot.hpp"

std::optional<PossibleMove> _ingame_bot_think(Game *game) {

    std::array<MoveType, 3> moveRank = {
        FINISH,
        MOVEBEAD,
        NEWBEAD
    };

    // Only do stuff if player2
    // NOTE: For now this will be enabled but in the future handle this
    // outside of this function because its make sense.
    if (game->mTurn != GameTurn::PLAYER2 || !game->mVSBot)
        return {};

    MoveType moveTarget = moveRank[0];
    std::vector<PossibleMove> &pm = game->mPosMove;
    for (const auto &m: pm) {
        if (m.mType == moveTarget) {}
    }
    return {};
}
