#include "ObjText.hpp"

ObjText::ObjText(Rectangle rec, int z_index, const char *name)
    : Object(rec, z_index, name) {
    mText = "";
    mColor = WHITE;
    mSize = 24;
}

ObjText::ObjText(Rectangle rec, int z_index, const char *name, const char *text, Color color, int size)
    : Object(rec, z_index, name) {
    mText = text;
    mColor = color;
    mSize = size;
}

void ObjText::render() {
    if (!mShow)
        return;

    if (mText != "") {
        DrawText(mText.c_str(), mRec.x, mRec.y, mSize, mColor);
    }
}

ObjText::~ObjText() {}
