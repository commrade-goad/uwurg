#ifndef TEXTURE_WRAPPER_H_
#define TEXTURE_WRAPPER_H_

#include <cstddef>
#include <raylib.h>

struct TextWrapper {
  public:
    const char *mFilePath;
    Texture2D mTexture;
    bool mSuccess;

    TextWrapper(const char *path);
    TextWrapper(const char *name, unsigned char *image, size_t image_len,
                const char *file_type);
    ~TextWrapper();
};

#endif // TEXTURE_WRAPPER_H_
