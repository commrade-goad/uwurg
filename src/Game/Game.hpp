#ifndef GAME_H_
#define GAME_H_

#include "../ObjectManager/ObjectManager.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "GameState.hpp"
#include <raylib.h>

struct Window;

struct Game {
  private:
    void _recalculate_center();

  public:
    TextureManager mTexMan;
    ObjectManager mObjMan;
    Window *mWindow_ptr;
    GameState mState;
    int mScale;

    Game();
    ~Game();

    void init(Window *w);
    void handle_logic(float dt);
    void handle_drawing(float dt);
    void handle_key(float dt);
};

#endif // GAME_H_
