#include "ObjectManager.hpp"

ObjectManager::ObjectManager() {
    mData.reserve(20);
}

ObjectManager::~ObjectManager() {}

sptr_t<Object> ObjectManager::addObject(Object obj) {
    mData[obj.mZIndex] = std::make_shared<Object>(obj);
    return mData[obj.mZIndex];
}

void ObjectManager::remObject(sptr_t<Object> obj) {
    auto ur_pos = mData.find(obj->mZIndex);
    if (ur_pos != mData.end()) {
        mData[obj->mZIndex] = nullptr;
    }
}

void ObjectManager::remObject(size_t z_index) {
    mData[z_index] = nullptr;
}

void ObjectManager::remObject(std::string &name) {
    for (auto [z_index, object] : mData) {
        if (object->mName == name) {
            mData[z_index] = nullptr;
            return;
        }
    }
}

sptr_t<Object> ObjectManager::getObject(std::string &name) {
    for (const auto& [z_index, object] : mData) {
        if (object->mName == name) {
            return object;
        }
    }
    return nullptr;
}
