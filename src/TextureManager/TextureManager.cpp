#include "TextureManager.hpp"

TextureManager::TextureManager() { mData.reserve(20); };

Texture2D *TextureManager::GetTexture(const char *name) {
    for (auto &data : mData) {
        if (data.first == name) {
            return &data.second;
        }
    }
    return nullptr;
};

Texture2D *TextureManager::loadAssets(std::string name, std::string img_path) {
    Texture2D *ctxt = GetTexture(name.c_str());
    if (ctxt != nullptr) {
        return nullptr;
    }
    Texture2D txt = LoadTexture(img_path.c_str());
    mData.insert_or_assign(name, txt);
    return &mData[name];
}

void TextureManager::unLoadTexture(const char *name) {
    Texture2D *ctxt = GetTexture(name);
    if (ctxt != nullptr) {
        for (auto &data : mData) {
            if (data.first == name) {
                UnloadTexture(data.second);
                break;
            }
        }
        mData.erase(name);
    }
}

TextureManager::~TextureManager() {
    for (auto &data : mData) {
        UnloadTexture(data.second);
    }
};
