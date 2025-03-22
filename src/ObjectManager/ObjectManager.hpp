#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include "../Object/Object.hpp"
#include "../def.hpp"
#include <unordered_map>

struct ObjectManager {
  public:
    std::unordered_map<int, sptr_t<Object>> mData;

    ObjectManager();
    ~ObjectManager();

    sptr_t<Object> addObject(Object obj);
    void remObject(sptr_t<Object> obj);
    void remObject(std::string &name);
    void remObject(size_t z_index);
    sptr_t<Object> getObject(std::string &name);
};

#endif // OBJECT_MANAGER_H_
