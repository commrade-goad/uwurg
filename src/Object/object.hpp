#ifndef OBJECT_H_
#define OBJECT_H_

#include <memory>
#include <raylib.h>
#include "../TextureWrapper/texture_wrapper.hpp"

// TODO: Make Texture2D Wrapper that will call UnloadTexture when no one have
// the pointer anymore.
struct Object {
  private:
    Rectangle mRec;
    std::shared_ptr<TextWrapper> mText;

  public:
    Object();
    Object(Rectangle rec);
    Object(Rectangle rec, std::shared_ptr<TextWrapper> text);

    virtual ~Object();

    void set_rec(Rectangle rec);
    Rectangle get_rec();

    void set_text(TextWrapper txt);
    TextWrapper get_text();

    virtual void draw();
    virtual void logic();
};

#endif // OBJECT_H_
