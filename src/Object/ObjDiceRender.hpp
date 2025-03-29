#ifndef OBJ_DICERENDER_H_
#define OBJ_DICERENDER_H_

#include "Object.hpp"

struct ObjDiceRender : public Object {
    public:
        uint8_t mDice;

    ObjDiceRender(Rectangle rec, int z_index, const char *name)
        : Object(rec, z_index, name) {

    }

    // Need custom render method to draw `mDice` amount of the sprite.
    virtual void render() {
        if (!mShow) return;
    }
    ~ObjDiceRender();
};

#endif // OBJ_DICERENDER_H_
