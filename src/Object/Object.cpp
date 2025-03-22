#include "Object.hpp"

Object::Object(Rectangle rec, int z_index, const char *name) {
    mRec = rec;
    mZIndex = z_index;
    mName = name;
    mText = nullptr;
}

Object::Object(Rectangle rec, int z_index, const char *name, Texture2D *text) {
    mRec = rec;
    mZIndex = z_index;
    mName = name;
    mText = text;
}

Object::~Object() {}

void Object::render() {
    if (mText != nullptr && mText->width > 0 && mText->height > 0) {
        DrawTextureRec(*mText, Rectangle(0, 0, mText->width, mText->height),
                       Vector2(0, 0), WHITE);
    } else
        DrawRectangleRec(mRec, RED);
}

void Object::logic(float dt) {}
