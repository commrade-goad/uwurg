#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include "../Object/Object.hpp"
#include <unordered_map>
#include <vector>

// TODO: add z-index
struct ObjectManager {
  private:
    std::vector<Object> mData;

  public:
    std::unordered_map<int, Object> mPubData;

    ObjectManager();
    ~ObjectManager();

    void add_object(Object obj);
    bool del_object(const char *name);

    Object *get_object(const char *name);
    std::vector<Object> *get_all_object();
};

#endif // OBJECT_MANAGER_H_
