#include "tests.hpp"
#include "../src/Shaders/ShadersManager.hpp"

// Headless: avoid actual shader loading. Just validate that get_shader returns nullptr when missing.
int test_shaders_manager() {
    std::cout << "\n[Suite] ShadersManager\n";

    ShadersManager sm;
    TEST(sm.get_shader("missing") == nullptr);

    return 0;
}
