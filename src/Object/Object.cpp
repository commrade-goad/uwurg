#include "Object.hpp"

Object::Object(std::string name) {
    mName = name;
    mRec = {0, 0, 0, 0};
    mText = nullptr;
}

Object::Object(std::string name, Rectangle rec) {
    mName = name;
    mRec = rec;
    mText = nullptr;
}

Object::Object(std::string name, Rectangle rec,
               std::shared_ptr<TextWrapper> text) {
    mName = name;
    mRec = rec;
    mText = text;
}

Object::~Object() { mText = nullptr; }

void Object::set_rec(Rectangle rec) { mRec = rec; }

Rectangle *Object::get_rec() { return &mRec; }

void Object::set_text(std::shared_ptr<TextWrapper> text) { mText = text; }
std::shared_ptr<TextWrapper> Object::get_text() { return mText; }

void Object::set_name(const char *name) { mName = name; }
const char *Object::get_name() { return mName.c_str(); }

void Object::logic() {
    // TODO: do object logic here...
}
void Object::draw() { DrawRectangleRec(mRec, RED); }
