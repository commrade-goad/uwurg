#ifndef OBJ_TEXT_H_
#define OBJ_TEXT_H_

#include "Object.hpp"

struct ObjText : public Object {
  private:
    std::string mText;
    Color mColor;
    int mSize;

  public:
    ObjText(Rectangle rec, int z_index, const char *name);
    ObjText(Rectangle rec, int z_index, const char *name, const char *text,
            Color color, int size);
    virtual void render() override;
    virtual ~ObjText();
};

#endif // OBJ_TEXT_H_
