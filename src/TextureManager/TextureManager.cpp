#include "TextureManager.hpp"

TextureManager::TextureManager() { mData.reserve(20); }
TextureManager::~TextureManager() { mData.clear(); }

void TextureManager::add_textwrapper(TextWrapper txt) {
    mData.push_back(std::make_shared<TextWrapper>(txt));
}

bool TextureManager::del_textrapper(const char *str) {
    int idx = -1;
    for (int i = 0; i < mData.size(); i++) {
        TextWrapper *data = mData[i].get();
        if (data->mFilePath == str) {
            idx = i;
            break;
        }
    }
    if (idx >= 0)
        mData.erase(mData.begin() + idx);
    else
        return false;
    return true;
}
