#include "window.hpp"
#include "../Object/object.hpp"

Window::Window(Vector2 size, const char *title) {
    mDefaultBgColor = BLACK;
    mFPS = 60;
    mExitKey = KEY_Q;
    InitWindow(size.x, size.y, title);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::Window(Vector2 size, const char *title, size_t fps) {
    mDefaultBgColor = BLACK;
    mFPS = fps;
    InitWindow(size.x, size.y, title);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::Window(Vector2 size, const char *title, size_t fps, int exit_key) {
    mDefaultBgColor = BLACK;
    mFPS = fps;
    mExitKey = exit_key;
    InitWindow(size.x, size.y, title);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::~Window() { CloseWindow(); }

void Window::set_window_size(Vector2 size) {
    mSize = size;
    SetWindowSize(mSize.x, mSize.y);
}

Vector2 Window::get_window_size() { return mSize; }

bool Window::start_window_loop() {
    while (!WindowShouldClose()) {
        p_start_logic();
        p_start_drawing();
    }
    return true;
}

void Window::p_start_drawing() {
    BeginDrawing();

    ClearBackground(mDefaultBgColor);

    EndDrawing();
}

void Window::p_start_logic() {
    // do some logic here...
}

Color Window::get_bg_color() { return mDefaultBgColor; }

void Window::set_bg_color(Color color) { mDefaultBgColor = color; }
