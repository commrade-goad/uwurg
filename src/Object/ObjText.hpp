#ifndef OBJ_TEXT_H_
#define OBJ_TEXT_H_

#include "Object.hpp"

struct ObjText : public Object {
  private:
    std::string mText;
    Color mColor;
    int mSize;

  public:
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
            DrawText(mText.c_str(), mRec.x, mRec.y, mSize, mColor);
        }
    }
    virtual ~ObjText() {};
};

#endif // OBJ_TEXT_H_
