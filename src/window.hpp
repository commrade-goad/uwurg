#ifndef WINDOW_H_
#define WINDOW_H_

#include <cstddef>
#include <raylib.h>

struct Window {
private:
    Vector2 mSize;
    const char *mName;

    int mExitKey;
    size_t mFPS;

public:
    Window(Vector2 size, const char *title);
    Window(Vector2 size, const char *title, size_t fps);
    Window(Vector2 size, const char *title, size_t fps, int exit_key);
    ~Window();

    void set_window_size(Vector2 size);
    Vector2 get_window_size();
    bool start_window_loop();
};

#endif // WINDOW_H_
