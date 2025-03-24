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
}

Game::~Game() {}

void Game::init(Window *w) {
    mWindow_ptr = w;
    _sync_scale();

    Vector2 *wsize = w->get_window_size();
    Texture2D *board_txt =
        mTexMan.load_texture("board_txt", "./assets/board-real.png");

    sptr_t<Object> board_obj =
        mObjMan.add_object(mk_sptr<Object>(Object({}, 1, "board", board_txt)));
    _center_board(board_obj);
    board_obj->mTag = GameState::INGAME;

    static const char *name = "UwUrg";
    static const int font_size = 48;
    static const float text_len = (float)MeasureText(name, font_size);
    sptr_t<Object> title_obj = mObjMan.add_object(mk_sptr<ObjText>(
        Rectangle{(wsize->x - text_len) / 2, text_len, text_len, font_size}, 2, "title",
        name, WHITE, PURPLE, font_size, 10));
    title_obj->mTag = GameState::MENU;

    static const char *play = "Play";
    sptr_t<Object> button_ojb = mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{200, 200, (float)MeasureText(play, 40), 40}, 3, "button_obj",
        play, PURPLE, WHITE, 40, 10));
}

void Game::handle_logic(float dt, Vector2 curpos) {
    (void)dt;

    for (auto &[_, object] : mObjMan.mData) {
        if (has_flag(object->mTag, mStateOrTag))
            object->logic(dt, curpos);
    }
}

void Game::handle_drawing(float dt) {
    (void)dt;

    for (auto &[_, object] : mObjMan.mData) {
        if (has_flag(object->mTag, mStateOrTag))
            object->render();
    }
    _render_version();
}

void Game::handle_key(float dt) {
    (void)dt;
    /*if (IsKeyPressed(KEY_F)) {*/
    /*    if (mScale == 4)*/
    /*        mWindow_ptr->set_window_size(Vector2(854, 480));*/
    /*    else*/
    /*        mWindow_ptr->set_window_size(Vector2(1280, 720));*/
    /*    _sync_scale();*/
    /*    sptr_t<Object> b = mObjMan.get_object("board");*/
    /*    _center_board(b);*/
    /*}*/
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

void Game::_center_board(sptr_t<Object> object) {
    if (object->mText->width <= 0 && object->mText->height <= 0)
        return;

    Vector2 *wsize = mWindow_ptr->get_window_size();
    object->mRec = {(wsize->x - (object->mText->width * mScale)) / 2,
                    (wsize->y - (object->mText->height * mScale)) / 2,
                    (float)object->mText->width * mScale,
                    (float)object->mText->height * mScale};
}

inline void Game::_render_version() {
    static const char *version = "0.1";
    auto wsize = mWindow_ptr->get_window_size();
    DrawText(version, 0 + 10, wsize->y - MeasureText(version, 28) - 10, 28,
             WHITE);
}
