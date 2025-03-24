#ifndef SHADERS_MANAGER_H_
#define SHADERS_MANAGER_H_

#include <raylib.h>
#include <string>
#include <unordered_map>

// TODO: Finish shaders manager
struct ShadersManager {
  private:
    std::unordered_map<std::string, Shader> mData;

  public:
    ShadersManager();
    ~ShadersManager();

    void add_shader(std::string, const char *file_path);
    Shader *get_shader(std::string);
};

#endif // SHADERS_MANAGER_H_
