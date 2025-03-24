#include "ObjectManager.hpp"

ObjectManager::ObjectManager() {
    mData.reserve(20);
    mGame_ptr = nullptr;
}

ObjectManager::~ObjectManager() {}

sptr_t<Object> ObjectManager::add_object(sptr_t<Object> obj) {
    obj->mGame_ptr = mGame_ptr;
    mData[obj->mZIndex] = obj;
    return obj;
}

void ObjectManager::rem_object(sptr_t<Object> obj) {
    auto ur_pos = mData.find(obj->mZIndex);
    if (ur_pos != mData.end()) {
        mData[obj->mZIndex] = nullptr;
    }
}

void ObjectManager::rem_object(size_t z_index) {
    mData[z_index] = nullptr;
}

void ObjectManager::rem_object(std::string &name) {
    for (auto [z_index, object] : mData) {
        if (object->mName == name) {
            mData[z_index] = nullptr;
            return;
        }
    }
}

sptr_t<Object> ObjectManager::get_object(const char *name) {
    for (const auto& [z_index, object] : mData) {
        if (object->mName == name) {
            return object;
        }
    }
    return nullptr;
}
