#include "Game.hpp"

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
}

Game::~Game() {}

void Game::init() {
    mObjMan.add_object(
        Object("player", Rectangle(0,0,100,100), nullptr)
    );
}

void Game::handle_logic(float dt) {

}

void Game::handle_drawing(float dt) {
    std::vector<Object> *obj_vec = mObjMan.get_all_object();
    for (Object &data: *obj_vec) {
        data.draw();
    }
}

void Game::handle_key(float dt) {}
