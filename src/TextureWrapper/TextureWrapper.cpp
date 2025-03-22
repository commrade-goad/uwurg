#include "TextureWrapper.hpp"
#include <cstring>

TextWrapper::TextWrapper(const char *path) {
    if (path == nullptr || strlen(path) <= 0)
        return;

    mTexture = LoadTexture(path);
    mFilePath = path;
    if (mTexture.height <= 0 || mTexture.width <= 0) {
        mSuccess = false;
        return;
    }
    mSuccess = true;
}

TextWrapper::TextWrapper(const char *name, unsigned char *image,
                         size_t image_len, const char *file_type) {
    if (name == nullptr || strlen(name) <= 0 || file_type == nullptr ||
        strlen(file_type) <= 0) {
        return;
    }
    Image img = LoadImageFromMemory(file_type, image, image_len);
    mTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    mFilePath = name;
    if (mTexture.height <= 0 || mTexture.width <= 0) {
        mSuccess = false;
        return;
    }
    mSuccess = true;
}

TextWrapper::~TextWrapper() {
    if (mSuccess)
        UnloadTexture(mTexture);
}
