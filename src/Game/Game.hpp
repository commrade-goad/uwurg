#ifndef GAME_H_
#define GAME_H_

#include "../ObjectManager/ObjectManager.hpp"
#include "../Shaders/ShadersManager.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "GameState.hpp"
#include "GameTurn.hpp"
#include "Gameplay.hpp"
#include <raylib.h>

struct Window;

struct Game {
  public:
    TextureManager mTexMan;
    ObjectManager mObjMan;
    ShadersManager mSMan;
    Window *mWindow_ptr;
    Font mFont;

    GameState mStateOrTag;
    int mScale;

    Vector2 mCursorPos;
    bool mWantExit;

    // For the ingame
    GameTurn mTurn;
    uint8_t mDice;
    bool mPaused;
    std::vector<PossibleMove> mPosMove;

    Game();
    ~Game();

    void init(Window *w);
    void handle_logic(float dt);
    void handle_drawing(float dt);
    void handle_key(float dt);
    void exit_game();

    void _sync_scale();
};

#endif // GAME_H_
