#include "GameUtils.hpp"
#include "../Window/Window.hpp"

void create_menu_object(Game *game, int *z_index) {
    // Create title
    static const char *title_name = "UwUrg";
    static const int title_font_size = 64;
    static const int button_font_size = 40;
    static const char *play_button = "PLAY";
    static const char *settings_button = "Settings";
    static const char *exit_button = "EXIT";

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
        GetColor(0x153CB4FF), WHITE, button_font_size, 10, [game]() {
            TraceLog(LOG_INFO, "Settings panel is WIP!");
            game->mStateOrTag = GameState::SETTINGS;
        }));
    settings_b_obj->mTag = GameState::MENU;
    z_index++;

    // Create Exit button
    sptr_t<Object> exit_b_obj = game->mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, *z_index, "exit_obj", exit_button, GetColor(0xE93479FF),
        WHITE, button_font_size, 10, [game]() { game->exit_game(); }));
    exit_b_obj->mTag = GameState::MENU;
    z_index++;
}

void position_menu_object(Game *game, Window *w) {
    Vector2 *wsize = w->get_window_size();
    sptr_t<Object> title = game->mObjMan.get_object("title");
    sptr_t<Object> play_btn = game->mObjMan.get_object("play_obj");
    sptr_t<Object> sett_btn = game->mObjMan.get_object("settings_obj");
    sptr_t<Object> exit_btn = game->mObjMan.get_object("exit_obj");

    if (auto titleText = std::dynamic_pointer_cast<ObjText>(title)) {
        titleText->mRec.x = (wsize->x - titleText->get_width()) / 2;
        titleText->mRec.y = titleText->mSize * 2;
    }

    if (auto playButton = std::dynamic_pointer_cast<ObjButton>(play_btn)) {
        int text_width = playButton->get_width();
        playButton->mRec.x = (wsize->x - text_width) / 2;
        playButton->mRec.y = (wsize->y - playButton->mSize) / 2;
        playButton->mRec.width = text_width;
        playButton->mRec.height = playButton->mSize;
    }

    if (auto settButton =
            std::dynamic_pointer_cast<ObjButton>(sett_btn)) {

        int text_width = settButton->get_width();
        settButton->mRec.x = (wsize->x - text_width) / 2;
        settButton->mRec.y =
            play_btn->mRec.y + play_btn->mRec.height + settButton->mSize;
        settButton->mRec.width = text_width;
        settButton->mRec.height = settButton->mSize;
    }

    if (auto exitButton = std::dynamic_pointer_cast<ObjButton>(exit_btn)) {
        auto textSize = exitButton->get_width();
        exitButton->mRec.x = (wsize->x - textSize) / 2;
        exitButton->mRec.y = sett_btn->mRec.y +
                             sett_btn->mRec.height + exitButton->mSize;
        exitButton->mRec.width = textSize;
        exitButton->mRec.height = exitButton->mSize;
    }
}
