#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <raylib.h>
#include <string>
#include <unordered_map>

struct TextureManager {
  public:
    std::unordered_map<std::string, Texture2D> mData;

    TextureManager();
    ~TextureManager();

    Texture2D *loadAssets(std::string name, std::string img_path);
    Texture2D *GetTexture(std::string name);
    void unLoadTexture(std::string name);
};

#endif // TEXTURE_MANAGER_H_
