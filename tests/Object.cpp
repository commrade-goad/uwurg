#include "tests.hpp"
#include "../src/Object/Object.hpp"
#include "../src/Game/GameState.hpp"
#include <raylib.h>

int test_object_basic() {
    std::cout << "\n[Suite] Object\n";

    Rectangle r{10, 20, 30, 40};
    Object o1(r, 3, "obj1");
    TEST(o1.mName == "obj1");
    TEST(o1.mZIndex == 3);
    TEST(o1.mRec.x == 10);
    TEST(o1.mRec.y == 20);
    TEST(o1.mRec.width == 30);
    TEST(o1.mRec.height == 40);
    TEST(o1.mText == nullptr);
    TEST(o1.mShow == true);
    TEST(o1.mTag == GameState::ALL);

    Object o2(r, 5, "obj2");
    TEST(!(o1 == o2));
    Object o3(r, 5, "obj1");
    TEST(o1 == o3);

    // logic(dt) default should be no-op and not crash
    o1.logic(0.016f);
    TEST(true);

    return 0;
}
