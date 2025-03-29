#ifndef OBJ_BEAD_H_
#define OBJ_BEAD_H_

#include "../Game/Game.hpp"
#include "Object.hpp"

struct ObjBead : public Object {
  private:
    Vector2 _xy_gen_helper() {
        Vector2 res = {mBoard->mRec.x, mBoard->mRec.y};
        if (mPos > 0 && mPos <= 4) {
            res.x += (20 * mGame_ptr->mScale) * (3 + mPos);
        } else if (mPos >= 5 && mPos <= 12) {
            res.x += (20 * mGame_ptr->mScale) * (12 - mPos);
            res.y += 20 * mGame_ptr->mScale;
        } else {
            res.x += (20 * mGame_ptr->mScale) * (mPos - 13);
            res.y += (20 * mGame_ptr->mScale) * 2;
        }
        return res;
    }
    sptr_t<Object> mBoard;

  public:
    int mPos;
    bool mOut;

    ObjBead(Rectangle rec, int z_index, const char *name, sptr_t<Object> board)
        : Object(rec, z_index, name) {
        mPos = 1;
        mOut = false;
        mBoard = board;
    }

    virtual void render() {
        if (!mShow)
            return;

        Vector2 new_pos = _xy_gen_helper();
        mRec.x = new_pos.x;
        mRec.y = new_pos.y;

        if (mText != nullptr && mText->width > 0 && mText->height > 0) {
            DrawTexturePro(*mText, Rectangle(0, 0, mText->width, mText->height),
                           mRec, Vector2(0, 0), 0.0f, WHITE);
        } else {
            DrawRectangleRec(mRec, RED);
        }
    }

    virtual void logic(float dt) { (void)dt; }

    virtual ~ObjBead() {}
};

#endif // OBJ_BEAD_H_
