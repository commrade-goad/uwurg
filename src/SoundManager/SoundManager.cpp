#include "SoundManager.hpp"

SoundManager::SoundManager() {
    mData.reserve(20);
}
SoundManager::~SoundManager() {
    for (size_t i = 0; i < mData.size(); i++) {
        mData[i].unload_sound();
    }
}

void SoundManager::add_sound(const char *fp, const char *name) {
    ManagedSound s = ManagedSound(name);
    s.load_sound(fp);
}
// void add_music(const char *fp, const char *name) {}

ManagedSound *SoundManager::get_sound(const char *name) {
    for (size_t i = 0; i < mData.size(); i++) {
        auto &current = mData[i];
        if (current.mName == name) {
            return &current;
        }
    }
    return nullptr;
}
// ManagedSound get_music(const char *name) {}
