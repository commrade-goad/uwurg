#include "ManagedSound.hpp"

ManagedSound::ManagedSound(const char *name) {
    mName = name;
    mPlaying = false;
}

ManagedSound::~ManagedSound() {}

void ManagedSound::load_sound(const char *path) { mData = LoadSound(path); }
void ManagedSound::unload_sound() { UnloadSound(mData); }
void ManagedSound::play_sound() { PlaySound(mData); }
