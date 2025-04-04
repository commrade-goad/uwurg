#include "GameUtils.hpp"
#include "../Object/ObjBead.hpp"
#include "../Object/ObjButton.hpp"
#include "../Object/ObjDiceRender.hpp"
#include "../Object/ObjText.hpp"
#include "../Window/Window.hpp"

#include <cmath>

void _create_menu_object(Game *game, int *z_index) {
    // Create title
    static const char *title_name = "UwUrg";
    static const int title_font_size = 16 * game->mScale;
    static const int button_font_size = 10 * game->mScale;
    static const char *play_button = "PLAY (P)";
    static const char *settings_button = "SETTINGS (S)";
    static const char *exit_button = "EXIT (E)";

    sptr_t<Object> title_obj = game->mObjMan.add_object(
        mk_sptr<ObjText>(Rectangle{}, *z_index, "title", title_name,
                         GetColor(0xfffb96FF), title_font_size));
    title_obj->mTag = GameState::MENU;
    z_index++;

    // Create play button
    sptr_t<Object> play_b_obj = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, *z_index, "play_obj", play_button, GetColor(0x153CB4FF),
        WHITE, button_font_size, 10,
        [game]() { game->mStateOrTag = GameState::INGAME; }));
    play_b_obj->mTag = GameState::MENU;
    z_index++;

    // Create settings button
    sptr_t<Object> settings_b_obj = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, *z_index, "settings_obj", settings_button,
        GetColor(0x153CB4FF), WHITE, button_font_size, 10,
        [game]() { game->mStateOrTag = GameState::SETTINGS; }));
    settings_b_obj->mTag = GameState::MENU;
    z_index++;

    // Create Exit button
    sptr_t<Object> exit_b_obj = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, *z_index, "exit_obj", exit_button, GetColor(0xE93479FF),
        WHITE, button_font_size, 10, [game]() { game->exit_game(); }));
    exit_b_obj->mTag = GameState::MENU;
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

void _create_ingame_object(Game *game, int *z_index) {
    Texture2D *bead_white_txt =
        game->mTexMan.load_texture("black_bead", "./assets/black.png");
    Texture2D *bead_black_txt =
        game->mTexMan.load_texture("white_bead", "./assets/white.png");
    Texture2D *board_txt =
        game->mTexMan.load_texture("board_txt", "./assets/board.png");
    Texture2D *dice_txt =
        game->mTexMan.load_texture("dice_txt", "./assets/nayeon.png");

    // Create board
    sptr_t<Object> board_obj = game->mObjMan.add_object(
        mk_sptr<Object>(Object({}, *z_index, "board", board_txt)));
    board_obj->mTag = GameState::INGAME;
    z_index++;

    // Create Dice obj
    sptr_t<Object> dice_obj = game->mObjMan.add_object(
        mk_sptr<ObjDiceRender>(ObjDiceRender(Rectangle{}, *z_index, "dice")));
    dice_obj->mTag = GameState::INGAME;
    dice_obj->mText = dice_txt;
    z_index++;

    for (int i = 0; i < 7; i++) {
        sptr_t<Object> test_bead = game->mObjMan.add_object(
            mk_sptr<ObjBead>(Rectangle{}, *z_index, TextFormat("bead_p1_%d", i),
                             board_obj, GameTurn::PLAYER1));

        test_bead->mTag = GameState::INGAME;
        test_bead->mText = bead_white_txt;
        z_index++;
    }

    for (int i = 0; i < 7; i++) {
        sptr_t<Object> test_bead = game->mObjMan.add_object(
            mk_sptr<ObjBead>(Rectangle{}, *z_index, TextFormat("bead_p2_%d", i),
                             board_obj, GameTurn::PLAYER2));

        test_bead->mTag = GameState::INGAME;
        test_bead->mText = bead_black_txt;
        z_index++;
    }
}

void _create_settings_object(Game *game, int *z_index) {
    static const char *title_name = "SETTINGS";
    static const char *back_txt = "BACK (B)";
    static const char *res1_text = "720P (R)";
    static const char *fs_button = "WINDOW (F)";
    static const int title_font_size = 16 * game->mScale;
    static const int button_font_size = 10 * game->mScale;

    // Create title
    sptr_t<Object> settings_title = game->mObjMan.add_object(
        mk_sptr<ObjText>(Rectangle{}, *z_index, "settings_text", title_name,
                         GetColor(0xfffb96FF), title_font_size));
    settings_title->mTag = GameState::SETTINGS;
    z_index++;

    // Create fullscreen button
    sptr_t<Object> fullscreen_button = game->mObjMan.add_object(
        mk_sptr<ObjButton>(Rectangle{}, *z_index, "fscreen_btn", fs_button,
                           GetColor(0x153CB4FF), WHITE, button_font_size, 10,
                           [game]() { _window_res_helper(game); }));
    fullscreen_button->mTag = GameState::SETTINGS;
    z_index++;

    // Create the res button
    sptr_t<Object> hd_button = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, *z_index, "res_btn", res1_text, GetColor(0x153CB4FF),
        WHITE, button_font_size, 10, [game]() { _window_res_helper(game); }));
    hd_button->mTag = GameState::SETTINGS;
    z_index++;

    // Create back button
    sptr_t<Object> back_button = game->mObjMan.add_object(
        mk_sptr<ObjButton>(Rectangle{}, *z_index, "btm_btn", back_txt,
                           GetColor(0xE93479FF), WHITE, button_font_size, 10,
                           [game]() { game->mStateOrTag = GameState::MENU; }));
    back_button->mTag = GameState::SETTINGS;
    z_index++;
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

void _position_ingame_object(Game *game) {
    // For the board itself
    sptr_t<Object> b = game->mObjMan.get_object("board");
    sptr_t<Object> bead = game->mObjMan.get_object("test_bead");
    if (b->mText->width <= 0 && b->mText->height <= 0)
        return;

    Vector2 *wsize = game->mWindow_ptr->get_window_size();
    b->mRec = {(wsize->x - (b->mText->width * game->mScale)) / 2,
               (wsize->y - (b->mText->height * game->mScale)) / 2,
               (float)b->mText->width * game->mScale,
               (float)b->mText->height * game->mScale};
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
}

void _ingame_next_turn(Game *game) {
    game->mTurn = game->mTurn == GameTurn::PLAYER1 ? GameTurn::PLAYER2
                                                   : GameTurn::PLAYER1;
}

void _ingame_getdice(Game *game) { game->mDice = GetRandomValue(0, 4); }

void _window_flag_helper(Game *game) {
    game->mWindow_ptr->toggle_fullscreen();
    _recalculate_all_pos(game);
    _change_text_from_obj(game, "fscreen_btn",
                          IsWindowFullscreen() ? "FULLSCREEN (F)"
                                               : "WINDOW (F)");
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
                          IsWindowFullscreen() ? "FULLSCREEN (F)"
                                               : "WINDOW (F)");
    _change_text_from_obj(game, "res_btn",
                          game->mScale == 4 ? "720P (R)" : "480P (R)");
}
