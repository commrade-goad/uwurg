#include "Game.hpp"

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
}

Game::~Game() {}

void Game::init() {
    Texture2D *white = mTexMan.loadAssets("white_beads", "./assets/white.png");
    sptr_t<Object> obj = mObjMan.addObject(Object({0,0,100,100}, 1, "player1"));
    obj->mText = white;
}

void Game::handle_logic(float dt) {}

void Game::handle_drawing(float dt) {
    for (auto& [_, object] : mObjMan.mData) {
        object->render();
    }
}

void Game::handle_key(float dt) {}
