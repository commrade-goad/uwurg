#ifndef MANAGEDSOUND_H_
#define MANAGEDSOUND_H_

#include <raylib.h>

struct ManagedSound {
public:
    const char *mName;
    Sound mData;
    bool mPlaying;

    ManagedSound(const char *name);
    ~ManagedSound();

    void load_sound(const char *path);
    void unload_sound();
    void play_sound();
};

#endif // MANAGEDSOUND_H_
