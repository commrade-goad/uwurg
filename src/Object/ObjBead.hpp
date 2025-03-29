#ifndef OBJ_BEAD_H_
#define OBJ_BEAD_H_

#include "Object.hpp"

struct ObjBead : public Object {
  private:
    Vector2 _render_helper() {
        Vector2 res = {};
        return res;
    }

  public:
    int mPos;
    bool mOut;

    ObjBead(Rectangle rec, int z_index, const char *name)
        : Object(rec, z_index, name) {
        mPos = -1;
        mOut = false;
    }

    virtual void render() {
        if (!mShow)
            return;

        Vector2 xy_grid = _render_helper();
        mRec.x = xy_grid.x;
        mRec.y = xy_grid.y;

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
