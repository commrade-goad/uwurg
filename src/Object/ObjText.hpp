#ifndef OBJ_TEXT_H_
#define OBJ_TEXT_H_

#include "../Game/Game.hpp"
#include "Object.hpp"

struct ObjText : public Object {

  public:
    std::string mText;
    Color mColor;
    int mSize;

    ObjText(Rectangle rec, int z_index, const char *name)
        : Object(rec, z_index, name) {
        mSize = 24;
        mText = "";
        mColor = WHITE;
    }

    ObjText(Rectangle rec, int z_index, const char *name, const char *text,
            Color color, int size)
        : Object(rec, z_index, name) {
        mText = text;
        mColor = color;
        mSize = size;
    }

    virtual void render() override {
        if (!mShow)
            return;

        if (mText != "") {
            // RIPPED from raylib straight up.
            int defaultFontSize = 10;
            if (mSize < defaultFontSize)
                mSize = defaultFontSize;
            int spacing = mSize / defaultFontSize;

            DrawTextPro(mGame_ptr->mFont, mText.c_str(),
                        Vector2(mRec.x, mRec.y), Vector2(0, 0), 0.0f, mSize,
                        spacing, mColor);
        }
    }
    virtual ~ObjText() {};
};

#endif // OBJ_TEXT_H_
