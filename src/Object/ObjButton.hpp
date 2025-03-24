#ifndef OBJ_BUTTON_H_
#define OBJ_BUTTON_H_

#include "Object.hpp"
#include "../Game/Game.hpp"
#include <iostream>

struct ObjButton : public Object {
  public:
    std::string mText;
    Color mColor;
    Color mBgColor;
    Color mHoverColor;
    Color mHoverBgColor;
    int mPad;
    int mSize;
    bool mHovered;

    ObjButton(Rectangle rec, int z_index, const char *name)
        : Object(rec, z_index, name) {
        mSize = 24;
        mText = "";
        mColor = WHITE;
        mBgColor = BLACK;
        mHoverColor = BLACK;
        mHoverBgColor = WHITE;
        mPad = 20;
        mHovered = false;
    }

    ObjButton(Rectangle rec, int z_index, const char *name, const char *text,
              Color color, Color bg_color, int size, int padding)
        : Object(rec, z_index, name) {
        mText = text;
        mColor = color;
        mBgColor = bg_color;
        mHoverColor = bg_color;
        mHoverBgColor = color;
        mSize = size;
        mPad = padding;
        mHovered = false;
    }

    ObjButton(Rectangle rec, int z_index, const char *name, const char *text,
              Color color, Color bg_color, Color hover_color,
              Color hover_bg_color, int size, int padding)
        : Object(rec, z_index, name) {
        mText = text;
        mColor = color;
        mBgColor = bg_color;
        mHoverColor = hover_color;
        mHoverBgColor = hover_bg_color;
        mSize = size;
        mPad = padding;
        mHovered = false;
    }

    virtual void render() override {
        if (!mShow)
            return;

        Color &fgcolor = mHovered ? mBgColor : mColor;
        Color &bgcolor = mHovered ? mColor   : mBgColor;
        if (mRec.width > 0 && mRec.height > 0)
            DrawRectangleRec(Rectangle(mRec.x, mRec.y, mRec.width + (mPad * 2),
                                       mRec.height + (mPad * 2)),
                             bgcolor);

        if (mText != "") {
            DrawText(mText.c_str(), mRec.x + mPad, mRec.y + mPad, mSize,
                     fgcolor);
        }
    }

    virtual void logic(float dt) override {
        (void)dt;
        if (mGame_ptr->mWindow_ptr == nullptr) return;
        Rectangle calculated_rec = Rectangle(mRec.x, mRec.y, mRec.width + (mPad * 2), mRec.height + (mPad * 2));
        if (CheckCollisionPointRec(mGame_ptr->mCursorPos, calculated_rec)) {
            mHovered = true;
        } else {
            mHovered = false;
        }
    };

    virtual ~ObjButton() {};
};

#endif // OBJ_BUTTON_H_
