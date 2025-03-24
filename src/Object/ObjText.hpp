#ifndef OBJ_TEXT_H_
#define OBJ_TEXT_H_

#include "Object.hpp"

struct ObjText : public Object {

  public:
    std::string mText;
    Color mColor;
    Color mBgColor;
    int mPad;
    int mSize;

    ObjText(Rectangle rec, int z_index, const char *name)
        : Object(rec, z_index, name) {
        mSize = 24;
        mText = "";
        mColor = WHITE;
        mBgColor = BLACK;
        mPad = 20;
    }

    ObjText(Rectangle rec, int z_index, const char *name, const char *text,
            Color color, int size)
        : Object(rec, z_index, name) {
        mText = text;
        mColor = color;
        mSize = size;
        mBgColor = BLACK;
        mPad = 20;
    }

    ObjText(Rectangle rec, int z_index, const char *name, const char *text,
            Color color, Color bg_color, int size)
        : Object(rec, z_index, name) {
        mText = text;
        mColor = color;
        mSize = size;
        mBgColor = bg_color;
        mPad = 20;
    }

    ObjText(Rectangle rec, int z_index, const char *name, const char *text,
            Color color, Color bg_color, int size, int padding)
        : Object(rec, z_index, name) {
        mText = text;
        mColor = color;
        mSize = size;
        mBgColor = bg_color;
        mPad = padding;
    }

    virtual void render() override {
        if (!mShow)
            return;

        if (mRec.width > 0 && mRec.height > 0)
            DrawRectangleRec(Rectangle(mRec.x, mRec.y,
                                       mRec.width + (mPad * 2),
                                       mRec.height + (mPad * 2)),
                             mBgColor);

        if (mText != "") {
            DrawText(mText.c_str(), mRec.x + mPad, mRec.y + mPad, mSize, mColor);
        }
    }
    virtual ~ObjText() {};
};

#endif // OBJ_TEXT_H_
