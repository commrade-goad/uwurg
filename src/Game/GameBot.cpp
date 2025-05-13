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
        TraceLog(LOG_INFO, TextFormat("Bot do the finish move with the bead name %s to this pos %d", move.mBead->mName.c_str(), move.mNewPos));
        break;
    case MoveType::NEWBEAD:
        a->mPos = move.mNewPos;
        a->mOut = true;
        a->mShow = true;
        TraceLog(LOG_INFO, TextFormat("Bot do the new bead move with the bead name %s to this pos %d", move.mBead->mName.c_str(), move.mNewPos));
        break;
    case MoveType::MOVEBEAD:
        a->mPos = move.mNewPos;
        if (sptr_t<ObjBead> en_obj =
                std::dynamic_pointer_cast<ObjBead>(move.mEnBead)) {
            en_obj->mPos = 0;
            en_obj->mOut = false;
        }
        TraceLog(LOG_INFO, TextFormat("Bot do the bead move with the bead name %s to this pos %d", move.mBead->mName.c_str(), move.mNewPos));

        // TODO: add point to the bot.
        if (a->mPos == 15) {
            mGame_ptr->mScore[(int)GameTurn::PLAYER2] += 1;
        }
        break;
    default:
        break;
    }
    _ingame_getdice(mGame_ptr);
    if (!move.mExtraTurn)
        game_change_turn(mGame_ptr);
    else {
        mGame_ptr->mPosMove = get_possible_move(mGame_ptr);
        if (this->bot_think()) {
            this->bot_move();
        }
    }
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
