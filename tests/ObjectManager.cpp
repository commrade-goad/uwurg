#include "tests.hpp"
#include "../src/ObjectManager/ObjectManager.hpp"
#include "../src/Object/Object.hpp"

int test_object_manager() {
    std::cout << "\n[Suite] ObjectManager\n";

    ObjectManager om;
    TEST(om.mData.empty());

    auto a = om.add_object(std::make_shared<Object>(Rectangle{}, 0, "a"));
    TEST(om.mData.size() == 1);
    TEST(om.mData[0] == a);
    TEST(om.mData[0]->mZIndex == 0);

    auto b = om.add_object(std::make_shared<Object>(Rectangle{}, 10, "b"));
    // Because z_index >= size: it gets pushed at end and z_index set to size()-1
    TEST(om.mData.size() == 2);
    TEST(om.mData[1]->mName == "b");
    TEST(om.mData[1]->mZIndex == 1);

    auto c = om.add_object(std::make_shared<Object>(Rectangle{}, 1, "c"));
    // Insert at index 1, and renumber z-index for items >= 1
    TEST(om.mData.size() == 3);
    TEST(om.mData[1]->mName == "c");
    TEST(om.mData[1]->mZIndex == 1);
    TEST(om.mData[2]->mName == "b");
    TEST(om.mData[2]->mZIndex == 2);

    // get_object by name
    TEST(om.get_object("c") == om.mData[1]);
    TEST(om.get_object("x") == nullptr);

    // remove by name
    std::string nameC = "c";
    om.rem_object(nameC);
    TEST(om.mData.size() == 2);
    TEST(om.get_object("c") == nullptr);

    // remove by index
    om.rem_object((size_t)0);
    TEST(om.mData.size() == 1);
    TEST(om.mData[0]->mName == "b");

    // remove by object pointer
    om.rem_object(om.mData[0]);
    TEST(om.mData.empty());

    return 0;
}
