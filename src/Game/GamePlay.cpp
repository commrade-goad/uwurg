#include "GamePlay.hpp"
#include "../Object/ObjBead.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"

PossibleMove::PossibleMove() {
    mBead = nullptr;
    mPossibleMove = -1;
    mExtraTurn = false;
}
PossibleMove::PossibleMove(sptr_t<Object> bead, int possibleMove) {
    mBead = bead;
    mPossibleMove = possibleMove;
    mExtraTurn = false;
    mType = MOVEBEAD;
}

PossibleMove::PossibleMove(sptr_t<Object> bead, int possibleMove,
                           bool ExtraTurn) {
    mBead = bead;
    mPossibleMove = possibleMove;
    mExtraTurn = ExtraTurn;
    mType = MOVEBEAD;
}

PossibleMove::PossibleMove(sptr_t<Object> bead, int possibleMove,
                           bool ExtraTurn, MoveType type) {
    mBead = bead;
    mPossibleMove = possibleMove;
    mExtraTurn = ExtraTurn;
    mType = type;
}

PossibleMove::~PossibleMove() {}

std::vector<PossibleMove> get_possible_move(Game *game) {
    if (game->mDice == 0)
        return std::vector<PossibleMove>();

    std::vector<PossibleMove> result;
    std::vector<sptr_t<ObjBead>> current;
    std::vector<sptr_t<ObjBead>> enemy;
    current.reserve(7);
    enemy.reserve(7);

    for (int i = 0; i < 7; i++) {
        const char *bead_to_search = game->mTurn == GameTurn::PLAYER1
                                         ? TextFormat("bead_p1_%d", i)
                                         : TextFormat("bead_p2_%d", i);
        sptr_t<Object> obj = game->mObjMan.get_object(bead_to_search);
        if (sptr_t<ObjBead> cobj = std::dynamic_pointer_cast<ObjBead>(obj)) {
            if (cobj->mPos >= 15)
                continue;
            current.push_back(cobj);
        }
    }

    for (int i = 0; i < 7; i++) {
        const char *bead_to_search = game->mTurn == GameTurn::PLAYER1
                                         ? TextFormat("bead_p2_%d", i)
                                         : TextFormat("bead_p1_%d", i);
        sptr_t<Object> obj = game->mObjMan.get_object(bead_to_search);
        if (sptr_t<ObjBead> cobj = std::dynamic_pointer_cast<ObjBead>(obj)) {
            if (cobj->mPos >= 15)
                continue;
            enemy.push_back(cobj);
        }
    }

    bool new_bead_done = false;
    for (const auto &bead : current) {
        bool found = false;
        sptr_t<ObjBead> sel_bead = bead;
        int new_pos = bead->mPos + game->mDice;
        MoveType mt = MoveType::MOVEBEAD;
        bool get_extraturn =
            new_pos == 4 || new_pos == 8 || new_pos == 13 ? true : false;

        // Check if possible to place a new bead
        if (!bead->mOut && bead->mPos <= 0 && new_pos <= 4 && !found &&
            !new_bead_done) {
            bool valid = true;
            for (const auto &bead2 : current) {
                if (bead2->mName == bead->mName || !bead2->mOut)
                    continue;

                if (bead2->mPos == new_pos)
                    valid = false;
            }
            if (valid) {
                new_bead_done = true;
                found = true;
                mt = MoveType::NEWBEAD;
            }
        }
        // Check if the new pos is valid (eating other player bead or collide
        // with its own friend)
        // TODO: This is not done yet please be patient
        else if (true) {

        }


        if (found)
            result.push_back(
                PossibleMove(sel_bead, new_pos, get_extraturn, mt));
    }

    return result;
}

void game_change_turn(Game *game) {
    if (game->mTurn == GameTurn::PLAYER1)
        game->mTurn = GameTurn::PLAYER2;
    else
        game->mTurn = GameTurn::PLAYER1;
    game->mPosMove = get_possible_move(game);
}

void game_new_bead_helper(Game *game) {
    bool success = false;
    for (const auto &pmove : game->mPosMove) {
        if (pmove.mType == NEWBEAD) {
            if (sptr_t<ObjBead> cobj =
                    std::dynamic_pointer_cast<ObjBead>(pmove.mBead)) {
                if (!cobj->mOut) {
                    cobj->mOut = true;
                    cobj->mPos = game->mDice;
                    cobj->mShow = true;
                    success = true;
                    break;
                }
            }
        }
    }
    if (success) {
        _ingame_getdice(game);
        game_change_turn(game);
    }
}
