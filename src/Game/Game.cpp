#include "Game.hpp"

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
}

Game::~Game() {}

void Game::init() {
    // additional stuff inside `mTexMan` and `mObjMan` that
    // need to be initialized.
}

void Game::handle_logic() {}

void Game::handle_drawing() {}

void Game::handle_key() {}
