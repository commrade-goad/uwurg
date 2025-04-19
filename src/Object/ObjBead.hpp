#ifndef OBJ_BEAD_H_
#define OBJ_BEAD_H_

#include "../Game/Game.hpp"
#include "../Game/GameTurn.hpp"
#include "Object.hpp"
#include <cstring>

struct ObjBead : public Object {
  private:
    Vector2 _xy_gen_helper() {
        Vector2 res = {mBoard->mRec.x, mBoard->mRec.y};
        if (mPos > 0 && mPos <= 4) {
            res.x += (20 * mGame_ptr->mScale) * (3 + mPos);
            if (mGroup == GameTurn::PLAYER1)
                res.y += (20 * mGame_ptr->mScale) * 2;
        } else if (mPos >= 5 && mPos <= 12) {
            res.x += (20 * mGame_ptr->mScale) * (12 - mPos);
            res.y += 20 * mGame_ptr->mScale;
        } else {
            res.x += (20 * mGame_ptr->mScale) * (mPos - 13);
            if (mGroup == GameTurn::PLAYER1)
                res.y += (20 * mGame_ptr->mScale) * 2;
        }
        return res;
    }
    sptr_t<Object> mBoard;
    int mIndex;

  public:
    int mPos;
    bool mOut;
    GameTurn mGroup;

    ObjBead(Rectangle rec, int z_index, const char *name, sptr_t<Object> board,
            GameTurn group)
        : Object(rec, z_index, name) {
        mPos = 0;
        mOut = false;
        mBoard = board;
        mGroup = group;
        mIndex = atoi(name + strlen("bead_p1_"));
    }

    // TODO: Add bead index rendering
    virtual void render() {
        if (!mShow || !mOut)
            return;

        Vector2 new_pos = _xy_gen_helper();
        mRec.x = new_pos.x;
        mRec.y = new_pos.y;

        mRec.width = 20 * mGame_ptr->mScale;
        mRec.height = 20 * mGame_ptr->mScale;

        if (mText != nullptr && mText->width > 0 && mText->height > 0) {
            DrawTexturePro(*mText, Rectangle(0, 0, mText->width, mText->height),
                           mRec, Vector2(0, 0), 0.0f, WHITE);
            DrawTextPro(mGame_ptr->mFont, TextFormat("%d", mIndex), Vector2(mRec.x, mRec.y), Vector2(0,0), 0.0f, 32, 10, RED);
        } else {
            DrawRectangleRec(mRec, RED);
        }
    }

    virtual void logic(float dt) { (void)dt; }

    virtual ~ObjBead() {}
};

#endif // OBJ_BEAD_H_
