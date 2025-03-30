#ifndef OBJ_DICERENDER_H_
#define OBJ_DICERENDER_H_

#include "Object.hpp"
#include "../Game/Game.hpp"
#include "../Window/Window.hpp"

struct ObjDiceRender : public Object {
  public:
    uint8_t mDice;

    ObjDiceRender(Rectangle rec, int z_index, const char *name)
        : Object(rec, z_index, name) {
        mDice = 0;
    }

    virtual void render() {
        if (!mShow)
            return;

        if (mText != nullptr && mText->width > 0 && mText->height > 0) {
            Vector2 *wsize = mGame_ptr->mWindow_ptr->get_window_size();
            mRec = {
                .x = wsize->x / 2.0f,
                .y = mGame_ptr->mScale * 6.0f,
                .width = (float)mText->width   * (mGame_ptr->mScale - 2),
                .height = (float)mText->height * (mGame_ptr->mScale - 2)
            };

            mRec.x -= (mGame_ptr->mDice * mGame_ptr->mScale * 7 + mRec.width) / 2.0f;

            for (int i = 0; i < mGame_ptr->mDice; i++) {
                Rectangle transform_rec(mRec.x + (i * mGame_ptr->mScale * 7), mRec.y, mRec.width, mRec.height);
                DrawTexturePro(*mText, Rectangle(0, 0, mText->width, mText->height),
                               transform_rec, Vector2(0, 0), 0.0f, WHITE);
            }
        } else {
            DrawRectangleRec(mRec, RED);
        }
    }
    virtual ~ObjDiceRender() {}
};

#endif // OBJ_DICERENDER_H_
