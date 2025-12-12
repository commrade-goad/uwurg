#pragma once
#include <iostream>

// Use this header file to do the whitebox testing

static int __test_fail_count = 0;

#define TEST(expr)                                                  \
    do {                                                            \
        if (!(expr)) {                                              \
            std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__   \
                      << " -> " #expr << " is false\n";             \
            __test_fail_count++;                                    \
        } else {                                                    \
            std::cout << "[ OK ] " #expr << "\n";                   \
        }                                                           \
    } while (0)

#define TEST_SUMMARY()                                                  \
    do {                                                                \
        if (__test_fail_count == 0)                                     \
            std::cout << "\nAll tests passed!\n";                       \
        else                                                            \
            std::cerr << "\nTotal failures : " << __test_fail_count << "\n"; \
        return __test_fail_count;                                       \
    } while (0)
