#include "tests.hpp"
#include "../src/TextureManager/TextureManager.hpp"
// #include <string>

// This suite avoids actual texture loading to keep tests headless and deterministic.
// We validate the logic paths around get/unload when nothing loaded.
int test_texture_manager() {
    std::cout << "\n[Suite] TextureManager\n";

    TextureManager tm;
    // Initially, get_texture should return nullptr
    TEST(tm.get_texture("missing") == nullptr);

    // load_texture() returns a pointer to stored texture; however, it calls LoadTexture,
    // which requires assets and a GPU context. We only test that calling it twice prevents duplicates.
    // If you want an integration test with assets, enable and place a real image under assets/.
    // auto texPtr = tm.load_texture("dummy", "assets/nayeon.png");
    // TEST(texPtr != nullptr);
    // TEST(tm.get_texture("dummy") != nullptr);
    // TEST(tm.load_texture("dummy", "assets/nayeon.png") == nullptr);

    // unload_texture() on missing should be safe and keep map unchanged
    tm.unload_texture("dummy");
    TEST(tm.get_texture("dummy") == nullptr);

    return 0;
}
