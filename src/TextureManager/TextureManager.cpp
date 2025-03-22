#include "TextureManager.hpp"

TextureManager::TextureManager() { mData.reserve(20); }
TextureManager::~TextureManager() { mData.clear(); }

std::shared_ptr<TextWrapper> TextureManager::add_textwrapper(TextWrapper txt) {
    for (auto &data : mData) {
        if (data.get()->mFilePath == txt.mFilePath)
            return nullptr;
    }
    std::shared_ptr<TextWrapper> new_texture =
        std::make_shared<TextWrapper>(txt);
    mData.push_back(new_texture);
    return new_texture;
}

bool TextureManager::del_textrapper(const char *str) {
    int idx = -1;
    for (size_t i = 0; i < mData.size(); i++) {
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

void TextureManager::cleanup_texture() {
    std::vector<size_t> idx;
    idx.reserve(mData.size());

    for (size_t i = 0; i < mData.size(); i++) {
        if (mData[i]->mFilePath == nullptr || mData[i]->mFilePath[0] == '\0' ||
            mData[i]->mSuccess == false)
            idx.insert(idx.begin(), i);
    }

    for (const auto &i : idx) {
        mData.erase(mData.begin() + i);
    }
}
