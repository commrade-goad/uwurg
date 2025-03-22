#ifndef GAME_H_
#define GAME_H_

#include "../Message/Message.hpp"
#include "../ObjectManager/ObjectManager.hpp"
#include "../TextureManager/TextureManager.hpp"
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
    void handle_logic(float dt);
    void handle_drawing(float dt);
    void handle_key(float dt);
};

#endif // GAME_H_
