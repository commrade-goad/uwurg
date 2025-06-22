#ifndef OBJSLIDE_H_
#define OBJSLIDE_H_

#include "../Game/Game.hpp"
#include "Object.hpp"

struct ObjSlide : public Object {
  public:
    std::vector<Texture2D *> mSlide;
    int mIndex;

    ObjSlide(Rectangle rec, int z_index, const char *name)
        : Object(rec, z_index, name) {
        mIndex = 0;
    }
    ~ObjSlide() = default;

    void add_slide(Texture2D *text) { mSlide.push_back(text); }

    void _next_index() {
        if (mIndex + 1 >= (int)mSlide.size()) {
            mShow = false;
            if (mGame_ptr) {
                mGame_ptr->mFirstTime = false;
                toggle_other_object();
            }
            return;
        }
        mIndex++;
    }

    void toggle_other_object() {
        if (!mGame_ptr) return;
        for (auto& item: mGame_ptr->mObjMan.mData) {
            if (item->mTag == GameState::PLAYMENU && item->mName != "slide") {
                item->mShow = !item->mShow;
            }
        }
    }

    void logic(float dt) {
        (void)dt;
        if (mGame_ptr->mWindow_ptr == nullptr || !mShow)
            return;

        if (!mGame_ptr->mFirstTime) {
            toggle_other_object();
            mShow = false;
            return;
        }

        if (mText != mSlide[mIndex])
            mText = mSlide[mIndex];

        if (CheckCollisionPointRec(mGame_ptr->mCursorPos, mRec)) {
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                _next_index();
        }
    }
};

#endif // OBJSLIDE_H_
