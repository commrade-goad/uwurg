#include "texture_wrapper.hpp"

TextWrapper::TextWrapper(const char *path) {
    mTexture = LoadTexture(path);
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
