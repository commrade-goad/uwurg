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

    sptr_t<Object> add_object(sptr_t<Object> obj);
    void rem_object(sptr_t<Object> obj);
    void rem_object(std::string &name);
    void rem_object(size_t z_index);
    sptr_t<Object> get_object(const char *name);
};

#endif // OBJECT_MANAGER_H_
