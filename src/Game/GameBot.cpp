#include "GameBot.hpp"

std::optional<PossibleMove> _ingame_bot_think(Game *game) {

    std::array<MoveType, 3> moveRank = {FINISH, MOVEBEAD, NEWBEAD};

    // Only do stuff if player2
    // NOTE: For now this will be enabled but in the future handle this
    // outside of this function because its make sense.
    if (game->mTurn != GameTurn::PLAYER2 || !game->mVSBot)
        return {};

    std::vector<PossibleMove> &pm = game->mPosMove;
    if (pm.size() <= 0)
        return {};

    for (const MoveType move: moveRank) {
        for (const PossibleMove &m : pm) {
            if (move == m.mType) {
                return m;
            }
        }
    }
    return {};
}

void _ingame_bot_move(Game *game, PossibleMove move) {}
