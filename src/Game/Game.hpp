#ifndef GAME_H_
#define GAME_H_

#include "../ObjectManager/ObjectManager.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "GameState.hpp"
#include <raylib.h>

struct Window;

struct Game {
  private:
    // HELPER FUNCTION
    void _center_board(sptr_t<Object> object);
    void _render_version();

    void _sync_scale();

  public:
    TextureManager mTexMan;
    ObjectManager mObjMan;
    Window *mWindow_ptr;
    Font mFont;

    GameState mStateOrTag;
    int mScale;

    Vector2 mCursorPos;
    bool mWantExit;

    Game();
    ~Game();

    void init(Window *w);
    void handle_logic(float dt);
    void handle_drawing(float dt);
    void handle_key(float dt);
    void exit_game();
};

#endif // GAME_H_
