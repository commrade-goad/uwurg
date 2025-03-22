#ifndef OBJECT_H_
#define OBJECT_H_

#include <raylib.h>
#include <string>

struct Object {
  public:
    std::string mName;
    Rectangle mRec;
    Texture2D *mText;
    int mZIndex;

    bool operator==(const Object &other) const {
        return mName == other.mName;
    }

    Object(Rectangle rec, int z_index, const char *name);
    Object(Rectangle rec, int z_index, const char *name, Texture2D *text);
    virtual ~Object();
    virtual void render();
    virtual void logic(float dt);
};

#endif // OBJECT_H_
