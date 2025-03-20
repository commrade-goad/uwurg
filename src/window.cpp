#include "window.hpp"

Window::Window(Vector2 size, const char *title) {
    mFPS = 60;
    mExitKey = KEY_Q;
    InitWindow(size.x, size.y, title);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::Window(Vector2 size, const char *title, size_t fps) {
    mFPS = fps;
    InitWindow(size.x, size.y, title);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::Window(Vector2 size, const char *title, size_t fps, int exit_key) {
    mFPS = fps;
    mExitKey = exit_key;
    InitWindow(size.x, size.y, title);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::~Window() {
    CloseWindow();
}

void Window::set_window_size(Vector2 size) {
    mSize = size;
    SetWindowSize(mSize.x, mSize.y);
}

Vector2 Window::get_window_size() {
    return mSize;
}

bool Window::start_window_loop() {
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }
    return true;
}
