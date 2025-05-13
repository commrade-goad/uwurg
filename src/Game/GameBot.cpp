#include "GameBot.hpp"
#include "../Object/ObjBead.hpp"
#include "GameUtils.hpp"

GameBot::GameBot(double delay) {
    mSelectedMove = {};
    mTimer = delay;
}

GameBot::~GameBot() {}

void GameBot::bot_move() {
    if (!mGame_ptr->mBotCanMove)
        return;
    if (mGame_ptr->mDice <= 0) {
        _ingame_getdice(mGame_ptr);
        game_change_turn(mGame_ptr);
        mGame_ptr->mPosMove = get_possible_move(mGame_ptr);
        return;
    }
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
        mGame_ptr->mScore[(int)GameTurn::PLAYER2] += 1;
        TraceLog(
            LOG_INFO,
            TextFormat(
                "Bot do the finish move with the bead name %s to this pos %d",
                move.mBead->mName.c_str(), move.mNewPos));
        break;
    case MoveType::NEWBEAD:
        a->mPos = move.mNewPos;
        a->mOut = true;
        a->mShow = true;
        TraceLog(
            LOG_INFO,
            TextFormat(
                "Bot do the new bead move with the bead name %s to this pos %d",
                move.mBead->mName.c_str(), move.mNewPos));
        break;
    case MoveType::MOVEBEAD:
        a->mPos = move.mNewPos;
        if (sptr_t<ObjBead> en_obj =
                std::dynamic_pointer_cast<ObjBead>(move.mEnBead)) {
            en_obj->mPos = 0;
            en_obj->mOut = false;
        }
        TraceLog(
            LOG_INFO,
            TextFormat(
                "Bot do the bead move with the bead name %s to this pos %d",
                move.mBead->mName.c_str(), move.mNewPos));
        break;
    default:
        break;
    }
    _ingame_getdice(mGame_ptr);
    if (!move.mExtraTurn)
        game_change_turn(mGame_ptr);
    else {
        TraceLog(LOG_INFO, "Bot get an extra turn .");
        mGame_ptr->mPosMove = get_possible_move(mGame_ptr);

        // IDK WTF is wrong ima just copy it.
        if (mGame_ptr->mVSBot && mGame_ptr->mTurn == GameTurn::PLAYER2) {
            if (mGame_ptr->mBot->bot_think()) {
                mGame_ptr->mBot->bot_move();
            } else if (mGame_ptr->mDice <= 0 || mGame_ptr->mPosMove.empty()) {
                _ingame_getdice(mGame_ptr);
                game_change_turn(mGame_ptr);
            }
        }
    }
}

bool GameBot::bot_think() {
    if (!mGame_ptr->mBotCanMove)
        return false;
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

bool GameBot::check_timer() {
    mCurrentTime = GetTime();
    return mCurrentTime - mStartTime >= mTimer;
}

void GameBot::start_timer() {
    mStartTime = GetTime();
    mCurrentTime = GetTime();
}

void GameBot::reset_timer() {
    this->start_timer();
}
