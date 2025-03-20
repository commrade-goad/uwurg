#ifndef OBJECT_H_
#define OBJECT_H_

#include "../TextureWrapper/TextureWrapper.hpp"
#include <memory>
#include <raylib.h>

// TODO: add z index later.
struct Object {
  private:
    std::string mName;
    Rectangle mRec;
    std::shared_ptr<TextWrapper> mText;

  public:

    Object(std::string name);
    Object(std::string name, Rectangle rec);
    Object(std::string name, Rectangle rec, std::shared_ptr<TextWrapper> text);

    virtual ~Object();

    void set_rec(Rectangle rec);
    Rectangle *get_rec();

    void set_text(std::shared_ptr<TextWrapper> text);
    std::shared_ptr<TextWrapper> get_text();

    void set_name(const char *name);
    const char *get_name();

    virtual void draw();
    virtual void logic();
};

#endif // OBJECT_H_
