#include "GamePlay.hpp"
#include "../Object/ObjBead.hpp"
#include "Game.hpp"
#include "GameBot.hpp"
#include "GameUtils.hpp"

PossibleMove::PossibleMove() {
    mBead = nullptr;
    mNewPos = -1;
    mExtraTurn = false;
    mEnBead = nullptr;
}
PossibleMove::PossibleMove(sptr_t<Object> bead, int possibleMove) {
    mBead = bead;
    mNewPos = possibleMove;
    mExtraTurn = false;
    mType = MoveType::MOVEBEAD;
    mEnBead = nullptr;
}

PossibleMove::PossibleMove(sptr_t<Object> bead, int possibleMove,
                           bool ExtraTurn) {
    mBead = bead;
    mNewPos = possibleMove;
    mExtraTurn = ExtraTurn;
    mType = MoveType::MOVEBEAD;
    mEnBead = nullptr;
}

PossibleMove::PossibleMove(sptr_t<Object> bead, int possibleMove,
                           bool ExtraTurn, MoveType type) {
    mBead = bead;
    mNewPos = possibleMove;
    mExtraTurn = ExtraTurn;
    mType = type;
    mEnBead = nullptr;
}

PossibleMove::PossibleMove(sptr_t<Object> bead, int possibleMove,
                           bool ExtraTurn, MoveType type,
                           sptr_t<Object> nbead) {
    mBead = bead;
    mNewPos = possibleMove;
    mExtraTurn = ExtraTurn;
    mType = type;
    mEnBead = nbead;
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
        sptr_t<ObjBead> sel_enm_bead = nullptr;
        int new_pos = bead->mPos + game->mDice;
        if (new_pos > 15)
            continue;
        MoveType mt = MoveType::MOVEBEAD;
        bool get_extraturn =
            new_pos == 4 || new_pos == 8 || new_pos == 14 ? true : false;

        // Check if the bead with the new pos is a win
        if (new_pos == 15) {
            mt = MoveType::FINISH;
            found = true;
        }

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
        } else if (bead->mOut && bead->mPos > 0 && !found) {
            // Check if collide with friend beads
            bool valid = true;
            for (const auto &bead2 : current) {
                if (bead2->mPos == new_pos) {
                    valid = false;
                    break;
                }
            }
            // Straight go to the next bead if its already colliding with friend
            // beads
            if (!valid)
                continue;

            // Check if on warzone
            if (new_pos >= 5 && new_pos <= 12) {
                for (const auto &ebead : enemy) {
                    if (ebead->mPos == new_pos && ebead->mPos == 8) {
                        valid = false;
                        break;
                    } else if (ebead->mPos == new_pos) {
                        sel_enm_bead = ebead;
                    }
                }
            }

            if (valid)
                found = true;
        }

        if (found)
            result.push_back(PossibleMove(sel_bead, new_pos, get_extraturn, mt,
                                          sel_enm_bead));
    }

    return result;
}

void game_change_turn(Game *game) {
    if (game->mTurn == GameTurn::PLAYER1)
        game->mTurn = GameTurn::PLAYER2;
    else
        game->mTurn = GameTurn::PLAYER1;
    game->mPosMove = get_possible_move(game);

    if (game->mPosMove.size() < 1) game->mDice = 0;

    if (game->mVSBot && game->mTurn == GameTurn::PLAYER2) {
        game->mBotCanMove = false;
        game->mBot->start_timer();
    }
}

void move_bot_wrapper(Game *game) {
    if (game->mBot->bot_think()) {
        game->mBot->bot_move();
    } else if (game->mDice <= 0 || game->mPosMove.empty()) {
        _ingame_getdice(game);
        game_change_turn(game);
    }
}

bool game_new_bead_helper(Game *game) {
    bool success = false;
    bool extra_turn;
    for (const auto &pmove : game->mPosMove) {
        extra_turn = pmove.mExtraTurn;
        if (pmove.mType == MoveType::NEWBEAD) {
            if (sptr_t<ObjBead> cobj =
                    std::dynamic_pointer_cast<ObjBead>(pmove.mBead)) {
                cobj->mOut = true;
                cobj->mPos = pmove.mNewPos;
                cobj->mShow = true;
                cobj->mSound->play_sound();
                success = true;
                break;
            }
        }
    }
    if (success) {
        _ingame_getdice(game);
        if (!extra_turn)
            game_change_turn(game);
        else
            game->mPosMove = get_possible_move(game);
    }
    return success;
}

bool game_move_bead_helper(Game *game, int nBead) {
    bool success = false;
    bool extra_turn;
    const char *player = game->mTurn == GameTurn::PLAYER1 ? "p1" : "p2";
    const char *bead_name = TextFormat("bead_%s_%d", player, nBead);
    for (const auto &pmove : game->mPosMove) {
        extra_turn = pmove.mExtraTurn;
        if ((pmove.mType == MoveType::MOVEBEAD ||
             pmove.mType == MoveType::FINISH) &&
            bead_name == pmove.mBead->mName) {
            if (sptr_t<ObjBead> cobj =
                    std::dynamic_pointer_cast<ObjBead>(pmove.mBead)) {
                if (pmove.mType == MoveType::FINISH) {
                    cobj->mOut = false;
                    cobj->mPos = 10000;
                    game->mScore[(int)game->mTurn] += 1;
                    cobj->mSound->play_sound();
                    success = true;
                    break;
                }
                if (pmove.mEnBead != nullptr) {
                    if (sptr_t<ObjBead> en_obj =
                            std::dynamic_pointer_cast<ObjBead>(pmove.mEnBead)) {
                        en_obj->mPos = 0;
                        en_obj->mOut = false;
                    }
                }
                if (cobj->mOut) {
                    cobj->mPos = pmove.mNewPos;
                    cobj->mSound->play_sound();
                    success = true;
                    break;
                }
            }
        }
    }
    if (success) {
        _ingame_getdice(game);
        if (!extra_turn)
            game_change_turn(game);
        else
            game->mPosMove = get_possible_move(game);
    }
    return success;
}

std::optional<GameTurn> game_check_win(Game *game) {
    int winning_player = -1;
    for (size_t i = 0; i < game->mScore.size(); i++) {
        if (game->mScore[i] >= 7) {
            winning_player = i;
            break;
        }
    }

    if (winning_player < 0)
        return {};
    game->change_state(GameState::FINISHED);
    return (GameTurn)winning_player;
}
