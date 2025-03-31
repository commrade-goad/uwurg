#include "Gameplay.hpp"
#include "../Object/ObjBead.hpp"
#include "Game.hpp"

PossibleMove::PossibleMove() {
    mBead = nullptr;
    mPossibleMove = -1;
}
PossibleMove::PossibleMove(sptr_t<Object> bead, int possibleMove) {
    mBead = bead;
    mPossibleMove = possibleMove;
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

    // Get the Current player beads
    for (int i = 0; i < 7; i++) {
        const char *bead_to_search = game->mTurn == GameTurn::PLAYER1
                                         ? TextFormat("bead_p1_%d", i)
                                         : TextFormat("bead_p2_%d", i);
        sptr_t<Object> obj = game->mObjMan.get_object(bead_to_search);
        if (sptr_t<ObjBead> cobj = std::dynamic_pointer_cast<ObjBead>(obj)) {
            // Beads already finished SKIP.
            if (cobj->mPos >= 15)
                continue;
            // Only add beads that are already in play
            if (cobj->mOut)
                current.push_back(cobj);
        }
    }

    // Get the Current Enemy beads
    for (int i = 0; i < 7; i++) {
        const char *bead_to_search = game->mTurn == GameTurn::PLAYER1
                                         ? TextFormat("bead_p2_%d", i)
                                         : TextFormat("bead_p1_%d", i);
        sptr_t<Object> obj = game->mObjMan.get_object(bead_to_search);
        if (sptr_t<ObjBead> cobj = std::dynamic_pointer_cast<ObjBead>(obj)) {
            // Beads already finished SKIP.
            if (cobj->mPos >= 15)
                continue;
            // Only add beads that are already in play
            if (cobj->mOut)
                enemy.push_back(cobj);
        }
    }

    // Check if a new bead can be entered into the game
    bool canEnterNewBead = true;
    // Find the first available bead not in play
    sptr_t<ObjBead> newBead = nullptr;
    for (int i = 0; i < 7 && newBead == nullptr; i++) {
        const char *bead_to_search = game->mTurn == GameTurn::PLAYER1
                                         ? TextFormat("bead_p1_%d", i)
                                         : TextFormat("bead_p2_%d", i);
        sptr_t<Object> obj = game->mObjMan.get_object(bead_to_search);
        if (sptr_t<ObjBead> cobj = std::dynamic_pointer_cast<ObjBead>(obj)) {
            if (!cobj->mOut && cobj->mPos < 15) {
                newBead = cobj;
            }
        }
    }

    // Check if the new position (which is dice value) has a friendly bead
    if (newBead != nullptr) {
        int spawnPos = game->mDice;
        for (const auto &fbead : current) {
            if (fbead->mPos == spawnPos) {
                canEnterNewBead = false;
                break;
            }
        }

        // If we can spawn a new bead, add it to results
        if (canEnterNewBead) {
            result.push_back(PossibleMove{newBead, spawnPos});
        }
    }

    // Process existing beads
    for (const auto &cbead : current) {
        int new_pos = cbead->mPos + game->mDice;

        // check if the new pos more than 15 (finish line)
        if (new_pos > 15) {
            continue;
        }

        bool validMove = true;

        // check if the bead will collide with a friendly bead
        for (const auto &fbead : current) {
            if (fbead->mName == cbead->mName)
                continue;
            if (fbead->mPos == new_pos) {
                validMove = false;
                break;
            }
        }

        if (!validMove) {
            continue;
        }

        // if the bead is moving to the warzone (positions 5-12)
        if (new_pos >= 5 && new_pos <= 12) {
            for (const auto &enm : enemy) {
                if (enm->mPos == new_pos && new_pos != 8) {
                }
            }
        }

        result.push_back(PossibleMove{cbead, new_pos});
    }

    return result;
}
