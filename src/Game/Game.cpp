#include "Game.hpp"
#include "../Window/Window.hpp"

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
    mWindow_ptr = nullptr;
    mState = MENU;
    // Change it later..
    mScale = 4;
}

Game::~Game() {}

void Game::init(Window *w) {
    mWindow_ptr = w;
    Vector2 wsize = mWindow_ptr->get_window_size();
    Texture2D *board_txt =
        mTexMan.load_texture("board_txt", "./assets/board-real.png");
    sptr_t<Object> obj = mObjMan.add_object(
        Object({(wsize.x - (board_txt->width * mScale)) / 2,
                (wsize.y - (board_txt->height * mScale)) / 2,
                (float)board_txt->width * mScale, (float)board_txt->height * mScale},
               1, "board", board_txt));
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
        if (mWindow_ptr->get_window_size().x == 1280) {
            mWindow_ptr->set_window_size(Vector2(800, 600));
            mScale = 3;
        } else {
            mWindow_ptr->set_window_size(Vector2(1280, 720));
            mScale = 4;
        }
        _recalculate_center();
    }
}

void Game::_recalculate_center() {
    Vector2 wsize = mWindow_ptr->get_window_size();
    auto board = mObjMan.get_object("board");
    board->mRec = {(wsize.x - (board->mText->width * mScale)) / 2,
                   (wsize.y - (board->mText->height * mScale)) / 2,
                   (float)board->mText->width * mScale,
                   (float)board->mText->height * mScale};
}
