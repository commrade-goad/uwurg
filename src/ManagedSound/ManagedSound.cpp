#include "ManagedSound.hpp"

ManagedSound::ManagedSound(const char *name) {
    mName = name;
    mPlaying = false;
}

ManagedSound::~ManagedSound() {}

bool ManagedSound::load_sound(const char *path) {
    mData = LoadSound(path);
    if (!IsSoundValid(mData)) return false;
    return true;
}
bool ManagedSound::unload_sound() {
    if (!IsSoundValid(mData)) return false;
    UnloadSound(mData);
    return true;
}
void ManagedSound::play_sound() {
    PlaySound(mData);
}

bool ManagedSound::is_playing() {
    IsSoundPlaying(mData);
}
