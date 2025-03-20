#include "object.hpp"

Object::Object() {
    mRec = {0, 0, 0, 0};
    mText = nullptr;
}

Object::Object(Rectangle rec) {
    mRec = rec;
    mText = nullptr;
}

Object::Object(Rectangle rec, std::shared_ptr<TextWrapper> text) {
    mRec = rec;
    mText = text;
}

Object::~Object() { mText = nullptr; }

void Object::set_rec(Rectangle rec) { mRec = rec; }

Rectangle Object::get_rec() { return mRec; }

void Object::set_text(TextWrapper txt) {
    mText = std::make_shared<TextWrapper>(txt);
}
TextWrapper Object::get_text() { return *mText; }

void Object::logic() {
    // do object logic here...
}
void Object::draw() {
    DrawRectangleRec(mRec, RED);
}
