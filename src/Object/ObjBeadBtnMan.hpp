#ifndef OBJBEADBTNMAN_H_
#define OBJBEADBTNMAN_H_

#include "ObjButton.hpp"
#include "Object.hpp"

struct ObjBeadBtnMan : public Object {
  public:
    sptr_t<ObjButton> mManagedBtn;

    ObjBeadBtnMan(Rectangle rec, int z_index, const char *name,
                  sptr_t<Object> btn_obj)
        : Object(rec, z_index, name) {
        if (auto a = std::dynamic_pointer_cast<ObjButton>(btn_obj)) {
            mManagedBtn = a;
        }
    }

    virtual ~ObjBeadBtnMan() {}
    virtual void render() {}
    virtual void logic(float _) {
        if (mGame_ptr->mVSBot && mGame_ptr->mTurn == GameTurn::PLAYER2)
            mManagedBtn->mShow = false;
        else
            mManagedBtn->mShow = true;
    }
};

#endif // OBJBEADBTNMAN_H_
