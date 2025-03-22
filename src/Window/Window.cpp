#include "Window.hpp"

Window::Window(Vector2 size, const char *title) {
    mDefaultBgColor = BLACK;
    mFPS = 60;
    mExitKey = KEY_Q;
    mGame = Game();
    InitWindow(size.x, size.y, title);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::Window(Vector2 size, const char *title, size_t fps) {
    mDefaultBgColor = BLACK;
    mFPS = fps;
    mExitKey = KEY_Q;
    mGame = Game();
    InitWindow(size.x, size.y, title);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::Window(Vector2 size, const char *title, size_t fps, int exit_key) {
    mDefaultBgColor = BLACK;
    mFPS = fps;
    mExitKey = exit_key;
    mGame = Game();
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
    mGame.init();
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        _check_msg();
        _handle_key(dt);
        _handle_logic(dt);
        _handle_drawing(dt);
    }
    return true;
}

void Window::_handle_drawing(float dt) {
    BeginDrawing();

    ClearBackground(mDefaultBgColor);

    mGame.handle_drawing(dt);

    EndDrawing();
}

void Window::_handle_logic(float dt) { mGame.handle_logic(dt); }

void Window::_handle_key(float dt) { mGame.handle_key(dt); }

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

void Window::_check_msg() {
    // TODO: add case as used.
    switch (mGame.mMsg.mMsgT) {
    default:
        break;
    }
}
