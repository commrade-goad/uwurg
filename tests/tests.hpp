#pragma once
#include <iostream>

inline int& get_test_fail_count() {
    static int count = 0;
    return count;
}

#define TEST(expr) \
    do { \
        if (!(expr)) { \
        std::cerr << "[FAIL] " \
                  <<  #expr << " is false" << "\n" << __FILE__ << ":" << __LINE__ << "\n"; \
            get_test_fail_count()++; \
        } else { \
            std::cout << "[ OK ] " #expr << "\n"; \
        } \
    } while (0)

#define TEST_SUMMARY() \
    do { \
        if (get_test_fail_count() == 0) \
            std::cout << "\nAll tests passed!\n"; \
        else \
            std::cerr << "\nTotal failures :  " << get_test_fail_count() << "\n"; \
        return get_test_fail_count(); \
    } while (0)
