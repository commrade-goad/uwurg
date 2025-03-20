#ifndef TEXTURE_WRAPPER_H_
#define TEXTURE_WRAPPER_H_

#include <raylib.h>

struct TextWrapper {
  public:
    const char *mFilePath;
    Texture2D mTexture;
    bool mSuccess;

    TextWrapper(const char *path);
    ~TextWrapper();
};

#endif // TEXTURE_WRAPPER_H_
