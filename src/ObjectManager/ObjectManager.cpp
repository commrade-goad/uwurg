#include "ObjectManager.hpp"

ObjectManager::ObjectManager() { mData.reserve(20); }

ObjectManager::~ObjectManager() {
    for (auto &data : mData) {
        data.set_text(nullptr);
    }
}

void ObjectManager::add_object(Object obj) { mData.push_back(obj); }

bool ObjectManager::del_object(const char *name) {
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

std::vector<Object> *ObjectManager::get_all_object() { return &mData; }
