#ifndef STATE_H_
#define STATE_H_

#include <raylib.h>

struct PState {
public:
    bool mIsFullscreen;
    Vector2 mWindowSize;

    PState();
    ~PState() = default;

    bool write_to_file(const char *file_path);
    bool read_from_file(const char *file_path);
};

#endif // STATE_H_
