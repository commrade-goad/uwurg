#include "GameUtils.hpp"
#include "../Window/Window.hpp"

void _create_menu_object(Game *game, int *z_index) {
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

void _position_menu_object(Game *game) {
    Vector2 *wsize = game->mWindow_ptr->get_window_size();
    sptr_t<Object> title = game->mObjMan.get_object("title");
    sptr_t<Object> play_btn = game->mObjMan.get_object("play_obj");
    sptr_t<Object> sett_btn = game->mObjMan.get_object("settings_obj");
    sptr_t<Object> exit_btn = game->mObjMan.get_object("exit_obj");

    if (auto titleText = std::dynamic_pointer_cast<ObjText>(title)) {
        titleText->mRec.x = (wsize->x - titleText->get_width()) / 2;
        titleText->mRec.y = titleText->mSize * (game->mScale / 3.0);
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

void _create_settings_object(Game *game, int *z_index) {
    // TODO: make it dynamic and generate the font size using the mScale value
    Texture2D *board_txt = game->mTexMan.load_texture("board_txt", "./assets/board-real.png");
    sptr_t<Object> board_obj = game->mObjMan.add_object(
        mk_sptr<Object>(Object({}, *z_index, "board", board_txt)));
    _center_board(game, board_obj);
    board_obj->mTag = GameState::INGAME;
    z_index++;
}

void _render_version(Game *game) {
    static const int font_size = 16;
    static const char *version = "Ver 0.0.1-development";
    auto wsize = game->mWindow_ptr->get_window_size();
    DrawText(version, 0 + 10, wsize->y - font_size - (font_size * 0.5),
             font_size, WHITE);
}

void _center_board(Game *game, sptr_t<Object> object) {
    if (object->mText->width <= 0 && object->mText->height <= 0)
        return;

    Vector2 *wsize = game->mWindow_ptr->get_window_size();
    object->mRec = {(wsize->x - (object->mText->width * game->mScale)) / 2,
                    (wsize->y - (object->mText->height * game->mScale)) / 2,
                    (float)object->mText->width * game->mScale,
                    (float)object->mText->height * game->mScale};
}
