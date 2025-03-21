#ifndef GAME_H_
#define GAME_H_

#include "../ObjectManager/ObjectManager.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "../Message/Message.hpp"
#include <raylib.h>

struct Game {
  public:
    TextureManager mTexMan;
    ObjectManager mObjMan;
    // TODO: Msg is still wip will take care other stuff first.
    Message mMsg;

    Game();
    ~Game();

    void init();
    void handle_logic();
    void handle_drawing();
    void handle_key();
};

#endif // GAME_H_
