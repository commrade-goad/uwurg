#include "GameBot.hpp"
#include "../Object/ObjBead.hpp"
#include "GameUtils.hpp"

GameBot::GameBot() {
    mSelectedMove = {};
}

GameBot::~GameBot() {}

void GameBot::bot_move() {
    if (!mSelectedMove.has_value()) {
        return;
    }

    PossibleMove move = mSelectedMove.value();
    auto a = std::dynamic_pointer_cast<ObjBead>(move.mBead);
    switch (move.mType) {
    case MoveType::FINISH:
        a->mOut = false;
        a->mShow = false;
        a->mPos = 10000;
        mGame_ptr->mScore[(int)mGame_ptr->mTurn] += 1;
        break;
    case MoveType::NEWBEAD:
        a->mPos = move.mNewPos;
        a->mOut = true;
        a->mShow = true;
        TraceLog(LOG_INFO, "doing new bead move");
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
        break;
    }
    _ingame_getdice(mGame_ptr);
    if (!move.mExtraTurn)
        game_change_turn(mGame_ptr);
    else
        mGame_ptr->mPosMove = get_possible_move(mGame_ptr);
}

bool GameBot::bot_think() {
    static const MoveType moveRank[3] = {FINISH, MOVEBEAD, NEWBEAD};

    if (!mGame_ptr) {
        TraceLog(LOG_FATAL, "Game pointer is null");
        return false;
    }
    std::vector<PossibleMove> pm = mGame_ptr->mPosMove;
    if (pm.size() <= 0) {
        mSelectedMove = {};
        return false;
    }

    for (const MoveType move : moveRank) {
        for (const PossibleMove &m : pm) {
            if (move == m.mType) {
                mSelectedMove = m;
                return true;
            }
        }
    }
    mSelectedMove = {};
    return false;
}
