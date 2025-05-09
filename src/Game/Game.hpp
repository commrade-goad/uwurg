#ifndef GAME_H_
#define GAME_H_

#include "../ObjectManager/ObjectManager.hpp"
#include "../Shaders/ShadersManager.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "GameState.hpp"
#include "GameTurn.hpp"
#include "GamePlay.hpp"
#include <raylib.h>
#include <array>

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
    std::vector<PossibleMove> mPosMove;

    bool mVSBot;
    std::array<int, 2> mScore;

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
