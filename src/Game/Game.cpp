#include "Game.hpp"

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
    mWindow_ptr = nullptr;
}

Game::~Game() {}

void Game::init(Window *w) {
    mWindow_ptr = w;
    Texture2D *white = mTexMan.loadAssets("white_beads", "./assets/white.png");
    sptr_t<Object> obj =
        mObjMan.addObject(Object({0, 0, 100, 100}, 1, "player1", white));
}

void Game::handle_logic(float dt) {
    (void) dt;
}

void Game::handle_drawing(float dt) {
    (void) dt;
    for (auto &[_, object] : mObjMan.mData) {
        object->render();
    }
}

void Game::handle_key(float dt) {
    (void) dt;
    /*if (IsKeyPressed(KEY_F)) SetWindowState(FLAG_FULLSCREEN_MODE);*/
}
