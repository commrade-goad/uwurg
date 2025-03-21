#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include "../TextureWrapper/TextureWrapper.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

struct TextureManager {
  private:
    std::vector<std::shared_ptr<TextWrapper>> mData;

  public:
    TextureManager();
    ~TextureManager();

    void add_textwrapper(TextWrapper txt);
    bool del_textrapper(const char *str);
};

#endif // TEXTURE_MANAGER_H_
