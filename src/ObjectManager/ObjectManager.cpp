#include "ObjectManager.hpp"

ObjectManager::ObjectManager() { mData.reserve(20); }

ObjectManager::~ObjectManager() {
    for (Object &data : mData) {
        data.set_text(nullptr);
    }
}

bool ObjectManager::add_object(Object *obj) {
    if (obj == nullptr)
        return false;
    mData.push_back(*obj);
    return true;
}

bool ObjectManager::delete_object(const char *name) {
    int idx = -1;
    for (size_t i = 0; i < mData.size(); i++) {
        Object *obj = &mData[i];
        if (obj->get_name() == name) {
            idx = i;
            break;
        }
    }
    if (idx >= 0)
        mData.erase(mData.begin() + idx);
    else
        return false;
    return true;
}

Object *ObjectManager::get_object(const char *name) {
    for (size_t i = 0; i < mData.size(); i++) {
        Object *obj = &mData[i];
        if (obj->get_name() == name) {
            return obj;
        }
    }
    return nullptr;
}
