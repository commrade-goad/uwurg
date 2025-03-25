#include "ObjectManager.hpp"

ObjectManager::ObjectManager() {
    mData.reserve(20);
    mGame_ptr = nullptr;
}

ObjectManager::~ObjectManager() {}

sptr_t<Object> ObjectManager::add_object(sptr_t<Object> obj) {
    obj->mGame_ptr = mGame_ptr;
    if ((size_t)obj->mZIndex >= mData.size()) {
        mData.push_back(obj);
        return obj;
    }
    mData.insert(mData.begin() + obj->mZIndex, obj);
    return obj;
}

void ObjectManager::rem_object(sptr_t<Object> obj) {
    for (size_t i = 0; i < mData.size(); i++) {
        auto &d = mData[i];
        if (d == obj)
            mData.erase(mData.begin() + i);
        break;
    }
}

void ObjectManager::rem_object(size_t z_index) { mData[z_index] = nullptr; }

void ObjectManager::rem_object(std::string &name) {
    for (size_t i = 0; i < mData.size(); i++) {
        auto &d = mData[i];
        if (d->mName == name)
            mData.erase(mData.begin() + i);
        break;
    }
}

sptr_t<Object> ObjectManager::get_object(const char *name) {
    for (size_t i = 0; i < mData.size(); i++) {
        auto &d = mData[i];
        if (d->mName == name)
            return d;
        break;
    }
    return nullptr;
}
