#include "Game.hpp"
#include "../Object/ObjButton.hpp"
#include "../Object/ObjText.hpp"
#include "../Window/Window.hpp"

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
    mWindow_ptr = nullptr;
    mStateOrTag = GameState::MENU;
    mScale = 0;
    mFont = Font();
    mCursorPos = Vector2();
    mWantExit = false;
}

Game::~Game() { UnloadFont(mFont); }

void Game::init(Window *w) {
    mWindow_ptr = w;
    mObjMan.mGame_ptr = this;
    int z_index = 1;

    mFont =
        LoadFontEx("./assets/Pixelify_Sans/PixelifySans-VariableFont_wght.ttf",
                   96, NULL, 95);

    _sync_scale();

    // TODO: make it dynamic and generate the font size using the mScale value
    Vector2 *wsize = w->get_window_size();
    Texture2D *board_txt =
        mTexMan.load_texture("board_txt", "./assets/board-real.png");

    sptr_t<Object> board_obj = mObjMan.add_object(
        mk_sptr<Object>(Object({}, z_index, "board", board_txt)));
    _center_board(board_obj);
    board_obj->mTag = GameState::INGAME;

    z_index++;

    static const char *title_name = "UwUrg";
    static const int title_font_size = 64;
    static const float title_text_len =
        (float)MeasureText(title_name, title_font_size);
    sptr_t<Object> title_obj = mObjMan.add_object(
        mk_sptr<ObjText>(Rectangle{(wsize->x - title_text_len) / 2,
                                   wsize->y - title_text_len / 2,
                                   title_text_len, title_font_size},
                         z_index, "title", title_name, WHITE, title_font_size));
    title_obj->mTag = GameState::MENU;

    z_index++;

    static const int button_font_size = 40;
    static const char *play_button = "PLAY";
    static const float play_button_size =
        (float)MeasureText(play_button, button_font_size);

    sptr_t<Object> play_b_obj = mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{(wsize->x - play_button_size) / 2,
                  (wsize->y - button_font_size) / 2, play_button_size,
                  button_font_size},
        z_index, "play_obj", play_button, PURPLE, WHITE, button_font_size, 10,
        [this]() { this->mStateOrTag = GameState::INGAME; }));
    play_b_obj->mTag = GameState::MENU;

    z_index++;

    static const char *exit_button = "EXIT";
    static const float exit_button_size =
        (float)MeasureText(exit_button, button_font_size);

    sptr_t<Object> exit_b_obj = mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{(wsize->x - exit_button_size) / 2,
                  play_b_obj->mRec.y + play_b_obj->mRec.height +
                      button_font_size,
                  exit_button_size, button_font_size},
        z_index, "exit_obj", exit_button, RED, WHITE, button_font_size, 10,
        [this]() { this->exit_game(); }));

    exit_b_obj->mTag = GameState::MENU;

    z_index++;
}

void Game::handle_logic(float dt) {
    (void)dt;

    for (auto &d : mObjMan.mData) {
        if (has_flag(d->mTag, mStateOrTag))
            d->logic(dt);
    }
}

void Game::handle_drawing(float dt) {
    (void)dt;

    for (auto &d : mObjMan.mData) {
        if (has_flag(d->mTag, mStateOrTag))
            d->render();
    }
    _render_version();
}

void Game::handle_key(float dt) {
    (void)dt;
    /*
    if (IsKeyPressed(KEY_F)) {
        if (mScale == 4)
            mWindow_ptr->set_window_size(Vector2(854, 480));
        else
            mWindow_ptr->set_window_size(Vector2(1280, 720));
        _sync_scale();
        sptr_t<Object> b = mObjMan.get_object("board");
        _center_board(b);
    } */
}

void Game::_sync_scale() {
    Vector2 *wsize = mWindow_ptr->get_window_size();
    if (wsize->y <= 640)
        mScale = 3;
    if (wsize->y == 720)
        mScale = 4;
    if (wsize->y >= 1080)
        mScale = 5;
}

inline void Game::_render_version() {
    static const char *version = "0.1";
    auto wsize = mWindow_ptr->get_window_size();
    DrawText(version, 0 + 10, wsize->y - MeasureText(version, 28) - 10, 28,
             WHITE);
}

void Game::_center_board(sptr_t<Object> object) {
    if (object->mText->width <= 0 && object->mText->height <= 0)
        return;

    Vector2 *wsize = mWindow_ptr->get_window_size();
    object->mRec = {(wsize->x - (object->mText->width * mScale)) / 2,
                    (wsize->y - (object->mText->height * mScale)) / 2,
                    (float)object->mText->width * mScale,
                    (float)object->mText->height * mScale};
}

void Game::exit_game() { mWantExit = true; }
