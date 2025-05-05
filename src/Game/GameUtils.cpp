#include "GameUtils.hpp"
#include "../Object/ObjBead.hpp"
#include "../Object/ObjBeadBtnMan.hpp"
#include "../Object/ObjBtnSkip.hpp"
#include "../Object/ObjButton.hpp"
#include "../Object/ObjDiceRender.hpp"
#include "../Object/ObjScore.hpp"
#include "../Object/ObjText.hpp"
#include "../Object/ObjTurnIndicator.hpp"
#include "../Window/Window.hpp"

void _create_menu_object(Game *game, int &z_index) {
    // Create title
    static const char *title_name = "UwUrg";
    static const int title_font_size = 16 * game->mScale;
    static const int button_font_size = 10 * game->mScale;
    static const char *play_button = "PLAY (P)";
    static const char *settings_button = "SETTINGS (S)";
    static const char *exit_button = "EXIT (Esc)";

    sptr_t<Object> title_obj = game->mObjMan.add_object(
        mk_sptr<ObjText>(Rectangle{}, z_index, "title", title_name,
                         GetColor(0xfffb96FF), title_font_size));
    title_obj->mTag = GameState::MENU;
    z_index++;

    // Create play button
    sptr_t<Object> play_b_obj = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "play_obj", play_button, GetColor(0x153CB4FF),
        WHITE, button_font_size, 10,
        [game]() { game->mStateOrTag = GameState::PLAYMENU; }));
    play_b_obj->mTag = GameState::MENU;
    z_index++;

    // Create settings button
    sptr_t<Object> settings_b_obj = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "settings_obj", settings_button,
        GetColor(0x153CB4FF), WHITE, button_font_size, 10,
        [game]() { game->mStateOrTag = GameState::SETTINGS; }));
    settings_b_obj->mTag = GameState::MENU;
    z_index++;

    // Create Exit button
    sptr_t<Object> exit_b_obj = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "exit_obj", exit_button, GetColor(0xE93479FF),
        WHITE, button_font_size, 10, [game]() { game->exit_game(); }));
    exit_b_obj->mTag = GameState::MENU;
    z_index++;
}

void _create_play_menu_object(Game *game, int &z_index) {
    static const int button_font_size = 10 * game->mScale;
    static const char *back_txt = "BACK (Esc)";
    static const char *vsbot_str = "VS Computer (E)";
    static const char *vsplayer_str = "VS Player (Q)";

    sptr_t<Object> vsbot_but_obj = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "vs_bot", vsbot_str, GetColor(0x153CB4FF), WHITE,
        button_font_size, 10, [game]() { _start_game(game, true); }));
    vsbot_but_obj->mTag = GameState::PLAYMENU;
    z_index++;

    sptr_t<Object> vsplayer_but_obj = game->mObjMan.add_object(
        mk_sptr<ObjButton>(Rectangle{}, z_index, "vs_player", vsplayer_str,
                           GetColor(0x153CB4FF), WHITE, button_font_size, 10,
                           [game]() { _start_game(game, false); }));
    vsplayer_but_obj->mTag = GameState::PLAYMENU;
    z_index++;

    sptr_t<Object> back_button = game->mObjMan.add_object(
        mk_sptr<ObjButton>(Rectangle{}, z_index, "second-back-btn", back_txt,
                           GetColor(0xE93479FF), WHITE, button_font_size, 10,
                           [game]() { game->mStateOrTag = GameState::MENU; }));
    back_button->mTag = GameState::PLAYMENU;
    z_index++;
}

void _position_menu_object(Game *game) {
    Vector2 *wsize = game->mWindow_ptr->get_window_size();
    sptr_t<Object> title = game->mObjMan.get_object("title");
    sptr_t<Object> play_btn = game->mObjMan.get_object("play_obj");
    sptr_t<Object> sett_btn = game->mObjMan.get_object("settings_obj");
    sptr_t<Object> exit_btn = game->mObjMan.get_object("exit_obj");

    if (auto titleText = std::dynamic_pointer_cast<ObjText>(title)) {
        titleText->mSize = 16 * game->mScale;
        titleText->mRec.x = (wsize->x - titleText->get_width()) / 2;
        titleText->mRec.y = titleText->mSize * (game->mScale / 3.0);
    }

    if (auto playButton = std::dynamic_pointer_cast<ObjButton>(play_btn)) {
        playButton->mSize = 10 * game->mScale;
        int text_width = playButton->get_width();
        playButton->mRec = {
            .x = (wsize->x - text_width) / 2,
            .y = (wsize->y - playButton->mSize) / 2,
            .width = (float)text_width,
            .height = (float)playButton->mSize,
        };
    }

    if (auto settButton = std::dynamic_pointer_cast<ObjButton>(sett_btn)) {
        settButton->mSize = 10 * game->mScale;
        int text_width = settButton->get_width();
        settButton->mRec = {.x = (wsize->x - text_width) / 2,
                            .y = play_btn->mRec.y + play_btn->mRec.height +
                                 (10 * 4) + game->mScale * 4,
                            .width = (float)text_width,
                            .height = (float)settButton->mSize};
    }

    if (auto exitButton = std::dynamic_pointer_cast<ObjButton>(exit_btn)) {
        exitButton->mSize = 10 * game->mScale;
        auto textSize = exitButton->get_width();
        exitButton->mRec = {.x = (wsize->x - textSize) / 2,
                            .y = sett_btn->mRec.y + sett_btn->mRec.height +
                                 (10 * 4) + game->mScale * 4,
                            .width = (float)textSize,
                            .height = (float)exitButton->mSize};
    }
}

void _create_ingame_object(Game *game, int &z_index) {
    Texture2D *bead_white_txt =
        game->mTexMan.load_texture("black_bead", "./assets/catto.png");
    Texture2D *bead_black_txt =
        game->mTexMan.load_texture("white_bead", "./assets/white.png");
    Texture2D *board_txt =
        game->mTexMan.load_texture("board_txt", "./assets/board.png");
    Texture2D *dice_txt =
        game->mTexMan.load_texture("dice_txt", "./assets/nayeon.png");

    Color bead_color[2] = {
        GetColor(0xffffffaa),
        GetColor(0x000000aa),
    };

    // Create board
    sptr_t<Object> board_obj = game->mObjMan.add_object(
        mk_sptr<Object>(Object({}, z_index, "board", board_txt)));
    board_obj->mTag = GameState::INGAME;
    z_index++;

    // Create Dice obj
    sptr_t<Object> dice_obj = game->mObjMan.add_object(
        mk_sptr<ObjDiceRender>(ObjDiceRender(Rectangle{}, z_index, "dice")));
    dice_obj->mTag = GameState::INGAME;
    dice_obj->mText = dice_txt;
    z_index++;

    // Create Turn Indicator object
    sptr_t<Object> turn_ind =
        game->mObjMan.add_object(mk_sptr<ObjTurnIndicator>(
            ObjTurnIndicator(Rectangle{}, z_index, "turn_ind")));
    turn_ind->mTag = GameState::INGAME;
    z_index++;

    // Create the bead
    for (int i = 0; i < 7; i++) {
        sptr_t<Object> test_bead = game->mObjMan.add_object(mk_sptr<ObjBead>(
            Rectangle{}, z_index, TextFormat("bead_p1_%d", i), board_obj,
            GameTurn::PLAYER1, bead_color[1], bead_color[0]));

        test_bead->mTag = GameState::INGAME;
        test_bead->mText = bead_white_txt;
        auto a = std::dynamic_pointer_cast<ObjBead>(test_bead);
        a->mOnClick = [game, a]() { _ingame_bead_button_helper(a, game); };
        z_index++;
    }

    for (int i = 0; i < 7; i++) {
        sptr_t<Object> test_bead = game->mObjMan.add_object(mk_sptr<ObjBead>(
            Rectangle{}, z_index, TextFormat("bead_p2_%d", i), board_obj,
            GameTurn::PLAYER2, bead_color[0], bead_color[1]));

        test_bead->mTag = GameState::INGAME;
        test_bead->mText = bead_black_txt;
        auto a = std::dynamic_pointer_cast<ObjBead>(test_bead);
        a->mOnClick = [game, a]() { _ingame_bead_button_helper(a, game); };
        z_index++;
    }

    // Create label for vsbot
    sptr_t<Object> vsbot_title = game->mObjMan.add_object(mk_sptr<ObjText>(
        Rectangle{}, z_index, "vsbot_title", "VS Compumter.", WHITE, 36));
    vsbot_title->mTag = GameState::INGAME;
    vsbot_title->mShow = false;
    z_index++;

    // Create score label
    sptr_t<Object> score_p1 = game->mObjMan.add_object(
        mk_sptr<ObjScore>(Rectangle{}, z_index, "player1_label", "0", WHITE, 36,
                          GameTurn::PLAYER1));
    score_p1->mTag = GameState::INGAME;
    z_index++;

    sptr_t<Object> score_p2 = game->mObjMan.add_object(
        mk_sptr<ObjScore>(Rectangle{}, z_index, "player2_label", "0", WHITE, 36,
                          GameTurn::PLAYER2));
    score_p2->mTag = GameState::INGAME;
    z_index++;

    // Create a button for new bead
    static const int font_size = 20;
    static const char *newBeadBtnString = "New Bead(N)";

    sptr_t<Object> newP1BeadBtn = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "new_bead_button", newBeadBtnString, WHITE, BLACK,
        font_size, 10, [game]() { game_new_bead_helper(game); }));
    newP1BeadBtn->mTag = GameState::INGAME;
    z_index++;

    // Create the new bead button manager
    sptr_t<Object> newBeadBtnMan =
        game->mObjMan.add_object(mk_sptr<ObjBeadBtnMan>(
            Rectangle{}, z_index, "new_bead_button_man", newP1BeadBtn));
    z_index++;

    // Create the skip turn button
    sptr_t<Object> newSkipButton = game->mObjMan.add_object(
        mk_sptr<ObjBtnSkip>(Rectangle{}, z_index, "skip_turn_button",
                            "Skip turn", WHITE, BLACK, font_size, 10, [game]() {
                                _ingame_getdice(game);
                                game_change_turn(game);
                            }));
    newSkipButton->mTag = GameState::INGAME;
    z_index++;
}

void _create_settings_object(Game *game, int &z_index) {
    static const char *title_name = "SETTINGS";
    static const char *back_txt = "BACK (Esc)";
    static const char *res1_text = "720P (E)";
    static const char *fs_button = "WINDOW (Q)";
    static const int title_font_size = 16 * game->mScale;
    static const int button_font_size = 10 * game->mScale;

    // Create title
    sptr_t<Object> settings_title = game->mObjMan.add_object(
        mk_sptr<ObjText>(Rectangle{}, z_index, "settings_text", title_name,
                         GetColor(0xfffb96FF), title_font_size));
    settings_title->mTag = GameState::SETTINGS;
    z_index++;

    // Create fullscreen button
    sptr_t<Object> fullscreen_button = game->mObjMan.add_object(
        mk_sptr<ObjButton>(Rectangle{}, z_index, "fscreen_btn", fs_button,
                           GetColor(0x153CB4FF), WHITE, button_font_size, 10,
                           [game]() { _window_flag_helper(game); }));
    fullscreen_button->mTag = GameState::SETTINGS;
    z_index++;

    // Create the res button
    sptr_t<Object> hd_button = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "res_btn", res1_text, GetColor(0x153CB4FF), WHITE,
        button_font_size, 10, [game]() { _window_res_helper(game); }));
    hd_button->mTag = GameState::SETTINGS;
    z_index++;

    // Create back button
    sptr_t<Object> back_button = game->mObjMan.add_object(
        mk_sptr<ObjButton>(Rectangle{}, z_index, "btm_btn", back_txt,
                           GetColor(0xE93479FF), WHITE, button_font_size, 10,
                           [game]() { game->mStateOrTag = GameState::MENU; }));
    back_button->mTag = GameState::SETTINGS;
    z_index++;
}

void _create_finish_menu_object(Game *game, int &z_index) {
    static const int font_size = 11 * game->mScale;
    static const int font_button_size = 10 * game->mScale;

    // Create label
    sptr_t<Object> winLabel = game->mObjMan.add_object(mk_sptr<ObjText>(
        Rectangle{}, z_index, "win_label", "", WHITE, font_size));
    winLabel->mTag = GameState::FINISHED;
    z_index++;

    // TODO
    // Create button
    sptr_t<Object> restartBtn = game->mObjMan.add_object(
        mk_sptr<ObjButton>(Rectangle{}, z_index, "restart_state_btn", "Restart",
                           WHITE, BLACK, font_button_size, 10, []() {}));
    restartBtn->mTag = GameState::FINISHED;
    z_index++;
}

void _position_finish_menu_object(Game *game) {
    // TODO
}

void _position_play_menu_object(Game *game) {
    static const int settings_button_padding = 10;
    sptr_t<Object> vsbot = game->mObjMan.get_object("vs_bot");
    sptr_t<Object> vsplayer = game->mObjMan.get_object("vs_player");
    sptr_t<Object> back = game->mObjMan.get_object("second-back-btn");
    Vector2 *wsize = game->mWindow_ptr->get_window_size();

    if (auto vsbot_btn = std::dynamic_pointer_cast<ObjButton>(vsbot)) {
        vsbot_btn->mSize = 10 * game->mScale;
        int text_width = vsbot_btn->get_width();
        vsbot_btn->mRec = {.x = (wsize->x - text_width) / 2,
                           .y = (wsize->y - vsbot_btn->mSize) / 2,
                           .width = (float)text_width,
                           .height = (float)vsbot_btn->mSize};
    }
    if (auto vsplayer_btn = std::dynamic_pointer_cast<ObjButton>(vsplayer)) {
        vsplayer_btn->mSize = 10 * game->mScale;
        int text_width = vsplayer_btn->get_width();
        vsplayer_btn->mRec = {.x = (wsize->x - text_width) / 2,
                              .y = vsbot->mRec.y + vsbot->mRec.height +
                                   (settings_button_padding * 4) +
                                   game->mScale * 4,
                              .width = (float)text_width,
                              .height = (float)vsplayer_btn->mSize};
    }
    if (auto back_btn = std::dynamic_pointer_cast<ObjButton>(back)) {
        back_btn->mSize = 10 * game->mScale;
        int text_width = back_btn->get_width();
        back_btn->mRec = {.x = (wsize->x - text_width) / 2,
                          .y = vsplayer->mRec.y + vsplayer->mRec.height +
                               (settings_button_padding * 4) + game->mScale * 4,
                          .width = (float)text_width,
                          .height = (float)back_btn->mSize};
    }
}

void _position_settings_object(Game *game) {
    int settings_button_padding = 10;
    sptr_t<Object> settings_obj = game->mObjMan.get_object("settings_text");
    sptr_t<Object> res1_obj = game->mObjMan.get_object("res_btn");
    sptr_t<Object> fullscreen_obj = game->mObjMan.get_object("fscreen_btn");
    sptr_t<Object> back_obj = game->mObjMan.get_object("btm_btn");

    Vector2 *wsize = game->mWindow_ptr->get_window_size();
    if (auto titleText = std::dynamic_pointer_cast<ObjText>(settings_obj)) {
        titleText->mSize = 16 * game->mScale;
        titleText->mRec.x = (wsize->x - titleText->get_width()) / 2;
        titleText->mRec.y = titleText->mSize * (game->mScale / 3.0);
    }

    if (auto fullscreenButton =
            std::dynamic_pointer_cast<ObjButton>(fullscreen_obj)) {
        fullscreenButton->mSize = 10 * game->mScale;
        int text_width = fullscreenButton->get_width();
        fullscreenButton->mRec = {.x = (wsize->x - text_width) / 2,
                                  .y = (wsize->y - fullscreenButton->mSize) / 2,
                                  .width = (float)text_width,
                                  .height = (float)fullscreenButton->mSize};
    }

    if (auto hdButton = std::dynamic_pointer_cast<ObjButton>(res1_obj)) {
        hdButton->mSize = 10 * game->mScale;
        int text_width = hdButton->get_width();
        hdButton->mRec = {.x = (wsize->x - text_width) / 2,
                          .y = fullscreen_obj->mRec.y +
                               fullscreen_obj->mRec.height +
                               (settings_button_padding * 4) + game->mScale * 4,
                          .width = (float)text_width,
                          .height = (float)hdButton->mSize};
    }

    if (auto backButton = std::dynamic_pointer_cast<ObjButton>(back_obj)) {
        backButton->mSize = 10 * game->mScale;
        int text_width = backButton->get_width();
        backButton->mRec = {.x = (wsize->x - text_width) / 2,
                            .y = res1_obj->mRec.y + res1_obj->mRec.height +
                                 settings_button_padding * 4 + game->mScale * 4,
                            .width = (float)text_width,
                            .height = (float)backButton->mSize};
    }
}

void _render_version(Game *game) {
    static const int font_size = 24;
    static const char *version = VERSION;
    auto wsize = game->mWindow_ptr->get_window_size();
    DrawTextEx(game->mFont, version,
               Vector2(0 + 10, wsize->y - font_size - (font_size * 0.5)),
               font_size, 3, WHITE);
}

void _vsbot_label_toggle(Game *game) {
    sptr_t<Object> vbt = game->mObjMan.get_object("vsbot_title");

    if (auto a = std::dynamic_pointer_cast<ObjText>(vbt)) {
        a->mSize = game->mScale * 11;
    }

    Vector2 *wsize = game->mWindow_ptr->get_window_size();
    if (!game->mVSBot && vbt->mShow) {
        vbt->mShow = false;
        return;
    } else if (!game->mVSBot && !vbt->mShow)
        return;
    if (vbt != nullptr) {
        vbt->mShow = true;
        auto vbtCasted = dynamic_pointer_cast<ObjText>(vbt);
        vbt->mRec = {.x = wsize->x - MeasureTextEx(game->mFont,
                                                   vbtCasted->mText.c_str(),
                                                   vbtCasted->mSize,
                                                   vbtCasted->mSpacing = 0)
                                         .x,
                     .y = 0,
                     .width = 100,
                     .height = 100};
    }
}

void _position_ingame_object(Game *game) {
    // For the board itself
    sptr_t<Object> b = game->mObjMan.get_object("board");
    sptr_t<Object> ti = game->mObjMan.get_object("turn_ind");

    sptr_t<Object> p1l = game->mObjMan.get_object("player1_label");
    sptr_t<Object> p2l = game->mObjMan.get_object("player2_label");

    sptr_t<Object> newBeadBtn = game->mObjMan.get_object("new_bead_button");
    sptr_t<Object> skipTurnBtn = game->mObjMan.get_object("skip_turn_button");

    if (b->mText->width <= 0 && b->mText->height <= 0)
        return;

    Vector2 *wsize = game->mWindow_ptr->get_window_size();
    b->mRec = {(wsize->x - (b->mText->width * game->mScale)) / 2,
               (wsize->y - (b->mText->height * game->mScale)) / 2,
               (float)b->mText->width * game->mScale,
               (float)b->mText->height * game->mScale};

    ti->mRec = {
        .x = 0, .y = 0, .width = wsize->x, .height = (float)2 * game->mScale};

    const int font_size = 11 * game->mScale;
    const int padding = 8 * game->mScale;
    p1l->mRec = {
        .x = wsize->x - MeasureTextEx(game->mFont, "0", font_size, 10).x -
             padding,
        .y = wsize->y - font_size - padding,
        .width = 100,
        .height = 100,
    };
    p2l->mRec = {
        .x = (float)0 + padding,
        .y = (float)0 + padding,
        .width = 100,
        .height = 100,
    };

    if (auto p1 = std::dynamic_pointer_cast<ObjButton>(newBeadBtn)) {
        p1->mSize = 10 * game->mScale;
        int textWidth = p1->get_width();
        p1->mRec = {.x = wsize->x - textWidth - padding,
                    .y = wsize->y / 2.0f,
                    .width = (float)textWidth,
                    .height = (float)p1->mSize};
    }

    if (auto p2 = std::dynamic_pointer_cast<ObjBtnSkip>(skipTurnBtn)) {
        p2->mSize = 10 * game->mScale;
        int textWidth = p2->get_width();
        p2->mRec = {.x = wsize->x - textWidth - padding,
                    .y = wsize->y / 2.0f - p2->mSize - (padding * 2),
                    .width = (float)textWidth,
                    .height = (float)p2->mSize};
    }
}

void _change_text_from_obj(Game *game, const char *obj_name,
                           const char *new_str) {
    sptr_t<Object> obj = game->mObjMan.get_object(obj_name);
    if (auto castedObj = std::dynamic_pointer_cast<ObjText>(obj)) {
        castedObj->mText = new_str;
    }
    if (auto castedObj = std::dynamic_pointer_cast<ObjButton>(obj)) {
        castedObj->mText = new_str;
    }
    _position_settings_object(game);
}

void _recalculate_all_pos(Game *game) {
    _position_ingame_object(game);
    _position_menu_object(game);
    _position_settings_object(game);
    _position_play_menu_object(game);
    _position_finish_menu_object(game);
}

inline void _ingame_next_turn(Game *game) {
    game->mTurn = game->mTurn == GameTurn::PLAYER1 ? GameTurn::PLAYER2
                                                   : GameTurn::PLAYER1;
}

void _ingame_getdice(Game *game) { game->mDice = GetRandomValue(0, 4); }

void _window_flag_helper(Game *game) {
    game->mWindow_ptr->toggle_fullscreen();
    _recalculate_all_pos(game);
    _change_text_from_obj(game, "fscreen_btn",
                          IsWindowFullscreen() ? "FULLSCREEN (E)"
                                               : "WINDOW (E)");
}
void _window_res_helper(Game *game) {
    if (IsWindowFullscreen())
        game->mWindow_ptr->toggle_fullscreen();
    else if (game->mScale == 4)
        game->mWindow_ptr->set_window_size(Vector2(854, 480));
    else
        game->mWindow_ptr->set_window_size(Vector2(1280, 720));
    _recalculate_all_pos(game);
    _change_text_from_obj(game, "fscreen_btn",
                          IsWindowFullscreen() ? "FULLSCREEN (E)"
                                               : "WINDOW (E)");
    _change_text_from_obj(game, "res_btn",
                          game->mScale == 4 ? "720P (Q)" : "480P (Q)");
}

void _start_game(Game *game, bool vsbot) {
    game->mStateOrTag = GameState::INGAME;
    game->mVSBot = vsbot;
    _vsbot_label_toggle(game);
}

void _ingame_bead_button_helper(sptr_t<ObjBead> bead, Game *game) {
    for (const auto &move : game->mPosMove) {
        if (move.mType == MOVEBEAD && move.mBead == bead) {
            size_t jump_for = strlen("bead_p1_");
            const int num = std::atoi(move.mBead->mName.c_str() + jump_for);
            game_move_bead_helper(game, num);
        }
    }
}

void _ingame_reset_state(Game *game) {
    game->mTurn = GameTurn::PLAYER1;
    game->mVSBot = false;
    game->mScore = {0, 0};
    game->mPosMove = {};

    for (int i = 0; i < 7; i++) {
        const char *bead_to_search = TextFormat("bead_p1_%d", i);
        sptr_t<Object> obj = game->mObjMan.get_object(bead_to_search);
        if (sptr_t<ObjBead> cobj = std::dynamic_pointer_cast<ObjBead>(obj)) {
            cobj->mOut = false;
            cobj->mPos = 0;
        }
    }

    for (int i = 0; i < 7; i++) {
        const char *bead_to_search = TextFormat("bead_p2_%d", i);
        sptr_t<Object> obj = game->mObjMan.get_object(bead_to_search);
        if (sptr_t<ObjBead> cobj = std::dynamic_pointer_cast<ObjBead>(obj)) {
            cobj->mOut = false;
            cobj->mPos = 0;
        }
    }
}
