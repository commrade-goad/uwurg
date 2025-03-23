#include "Game.hpp"
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

    Texture2D *board_txt =
        mTexMan.load_texture("board_txt", "./assets/board-real.png");

    sptr_t<Object> board_obj =
        mObjMan.add_object(mk_sptr<Object>(Object({}, 1, "board", board_txt)));
    _center_board(board_obj);
    board_obj->mTag = GameState::INGAME | GameState::MENU;

    sptr_t<Object> title_obj = mObjMan.add_object(mk_sptr<ObjText>(
        Rectangle{0, 0, 0, 0}, 2, "title", "UwUrg", WHITE, 40));
    title_obj->mTag = GameState::MENU;
}

void Game::handle_logic(float dt) { (void)dt; }

void Game::handle_drawing(float dt) {
    (void)dt;

    for (auto &[_, object] : mObjMan.mData) {
        if (has_flag(object->mTag, mStateOrTag))
            object->render();
    }
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
