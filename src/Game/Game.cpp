#include "Game.hpp"
#include "../Window/Window.hpp"

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
    mWindow_ptr = nullptr;
    mState = MENU;
    mScale = 0;
}

Game::~Game() {}

void Game::init(Window *w) {
    mWindow_ptr = w;
    _sync_scale();

    Texture2D *board_txt =
        mTexMan.load_texture("board_txt", "./assets/board-real.png");

    sptr_t<Object> obj = mObjMan.add_object(Object({}, 1, "board", board_txt));
    _center_object(obj);
}

void Game::handle_logic(float dt) { (void)dt; }

void Game::handle_drawing(float dt) {
    (void)dt;

    switch (mState) {
    case MENU:
        break;
    case INGAME:
        break;
    case PAUSE:
        break;
    default:
        break;
    }

    for (auto &[_, object] : mObjMan.mData) {
        object->render();
    }
}

void Game::handle_key(float dt) {
    (void)dt;
    if (IsKeyPressed(KEY_F)) {
        if (mScale == 4)
            mWindow_ptr->set_window_size(Vector2(800, 640));
        else
            mWindow_ptr->set_window_size(Vector2(1280, 720));
        _sync_scale();
        _center_object("board");
    }
}

void Game::_center_object(const char *obj_name) {
    Vector2 *wsize = mWindow_ptr->get_window_size();
    auto board = mObjMan.get_object(obj_name);
    board->mRec = {(wsize->x - (board->mText->width * mScale)) / 2,
                   (wsize->y - (board->mText->height * mScale)) / 2,
                   (float)board->mText->width * mScale,
                   (float)board->mText->height * mScale};
}

void Game::_center_object(sptr_t<Object> object) {
    Vector2 *wsize = mWindow_ptr->get_window_size();
    object->mRec = {(wsize->x - (object->mText->width * mScale)) / 2,
                    (wsize->y - (object->mText->height * mScale)) / 2,
                    (float)object->mText->width * mScale,
                    (float)object->mText->height * mScale};
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
