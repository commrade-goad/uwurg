#ifndef OBJ_DICERENDER_H_
#define OBJ_DICERENDER_H_

#include "Object.hpp"

struct ObjDiceRender : public Object {
  public:
    uint8_t mDice;

    ObjDiceRender(Rectangle rec, int z_index, const char *name)
        : Object(rec, z_index, name) {
        mDice = 0;
    }

    // Need custom render method to draw `mDice` amount of the sprite.
    virtual void render() {
        if (!mShow)
            return;

        if (mText != nullptr && mText->width > 0 && mText->height > 0) {
            DrawTexturePro(*mText, Rectangle(0, 0, mText->width, mText->height),
                           mRec, Vector2(0, 0), 0.0f, WHITE);
        } else {
            DrawRectangleRec(mRec, RED);
        }
    }
    ~ObjDiceRender();
};

#endif // OBJ_DICERENDER_H_
