#include "tests.hpp"
#include "../src/SoundManager/SoundManager.hpp"

// We avoid loading actual audio files to keep tests headless.
// Validate container and lookup behavior.
int test_sound_manager() {
    std::cout << "\n[Suite] SoundManager\n";

    SoundManager sm;
    TEST(sm.get_sound("missing") == nullptr);

    // When load_sound succeeds, it pushes a ManagedSound; but it calls raylib LoadSound.
    // For unit tests, skip actual loading. Just assert that querying missing returns nullptr.
    TEST(sm.get_sound("coin") == nullptr);

    return 0;
}
