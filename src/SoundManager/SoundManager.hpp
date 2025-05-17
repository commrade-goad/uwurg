#ifndef SOUND_MANAGER_H_
#define SOUND_MANAGER_H_

#include "../ManagedSound/ManagedSound.hpp"

#include <raylib.h>
#include <vector>

struct SoundManager {
    std::vector<ManagedSound> mData;
  public:
    SoundManager();
    ~SoundManager();

    bool add_sound(const char *fp, const char *name);
    // void add_music(const char *fp, const char *name);

    ManagedSound *get_sound(const char *name);
    // ManagedSound get_music(const char *name);
};

#endif // SOUND_MANAGER_H_
