#include "tests.hpp"
#include "../src/Game/GameState.hpp"
#include "../src/Game/GameTurn.hpp"

int test_game_enums_and_flags() {
    std::cout << "\n[Suite] GameState & GameTurn\n";

    // Bit flags composition
    {
        GameState a = GameState::MENU;
        GameState b = GameState::SETTINGS;
        GameState c = a | b;
        TEST(has_flag(c, GameState::MENU));
        TEST(has_flag(c, GameState::SETTINGS));
        TEST(!has_flag(c, GameState::INGAME));

        GameState all = GameState::ALL;
        TEST(has_flag(all, GameState::MENU));
        TEST(has_flag(all, GameState::SETTINGS));
        TEST(has_flag(all, GameState::INGAME));
        TEST(has_flag(all, GameState::PLAYMENU));
        TEST(has_flag(all, GameState::FINISHED));
        TEST(has_flag(all, GameState::TUTORIAL));
    }

    // GameTurn enum values
    {
        TEST(static_cast<int>(GameTurn::PLAYER1) == 0);
        TEST(static_cast<int>(GameTurn::PLAYER2) == 1);
        TEST(GameTurn::PLAYER1 != GameTurn::PLAYER2);
    }

    return 0;
}
