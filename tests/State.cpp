#include "tests.hpp"
#include "../src/State/State.hpp"
#include <cstdio>
#include <cstdlib>

// This suite uses a temporary file to validate serialization.
int test_state_serialization() {
    std::cout << "\n[Suite] PState\n";

    PState st;
    st.mWindowSize = {800, 600};
    st.mIsFullscreen = true;

    const char* tmp = "./tmp_state_test.bin";
    // Write
    TEST(st.write_to_file(tmp));

    // Read to a fresh instance
    PState rd;
    TEST(rd.read_from_file(tmp));
    TEST(rd.mWindowSize.x == 800);
    TEST(rd.mWindowSize.y == 600);
    TEST(rd.mIsFullscreen == true);

    // Cleanup
    std::remove(tmp);

    return 0;
}
