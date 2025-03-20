#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include "../Object/Object.hpp"
#include <vector>

struct ObjectManager {
  private:
    std::vector<Object> mData;

  public:
    ObjectManager();
    ~ObjectManager();

    bool add_object(Object *obj);
    bool delete_object(const char *name);

    Object *get_object(const char *name);
};

#endif // OBJECT_MANAGER_H_
