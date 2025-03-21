#include "Window.hpp"

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
        _handle_logic();
        _handle_drawing();
    }
    return true;
}

void Window::_handle_drawing() {
    BeginDrawing();

    ClearBackground(mDefaultBgColor);

    EndDrawing();
}

void Window::_handle_logic() {
    // do some logic here...
}

void Window::_handle_key() {
    // handle some key
}

Color Window::get_bg_color() { return mDefaultBgColor; }

void Window::set_bg_color(Color color) { mDefaultBgColor = color; }

void Window::set_fps_target(size_t fps) {
    mFPS = fps;
    SetTargetFPS(mFPS);
}
size_t Window::get_fps_target() { return mFPS; }

void Window::set_exit_key(int key) {
    mExitKey = key;
    SetExitKey(mExitKey);
}

size_t Window::get_exit_key() { return mExitKey; }

const char *Window::get_name() { return mName; }
