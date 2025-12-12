#include "tests.hpp"
#include <iostream>

int test_game_enums_and_flags();
int test_object_basic();
int test_object_manager();
int test_texture_manager();
int test_sound_manager();
int test_state_serialization();
int test_shaders_manager();

int main() {
    std::cout << "Running uwurg unit tests...\n";

    test_game_enums_and_flags();
    test_object_basic();
    test_object_manager();
    test_texture_manager();
    test_sound_manager();
    test_state_serialization();
    test_shaders_manager();

    TEST_SUMMARY();
}
