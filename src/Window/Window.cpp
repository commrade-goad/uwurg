#include "Window.hpp"
#include <iostream>

void Window::_apply_option(const char *title) {
    mName = title;
    mDefaultBgColor = BLACK;
    mGame = Game();
    InitWindow(mSize.x, mSize.y, mName);
    SetTargetFPS(mFPS);
    SetExitKey(mExitKey);
}

Window::Window(Vector2 size, const char *title) {
    mSize = size;
    mFPS = 60;
    mExitKey = KEY_Q;
    _apply_option(title);
}

Window::Window(Vector2 size, const char *title, size_t fps) {
    mSize = size;
    mFPS = fps;
    mExitKey = KEY_Q;
    _apply_option(title);
}

Window::Window(Vector2 size, const char *title, size_t fps, int exit_key) {
    mSize = size;
    mFPS = fps;
    mExitKey = exit_key;
    _apply_option(title);
}

Window::~Window() { CloseWindow(); }

void Window::set_window_size(Vector2 size) {
    mSize = size;
    SetWindowSize(mSize.x, mSize.y);
}

Vector2 *Window::get_window_size() { return &mSize; }

bool Window::start_window_loop() {
    mGame.init(this);
    mGame.mWindow_ptr = this;
    while (!WindowShouldClose()) {
        if (mGame.mWantExit) break;
        float dt = GetFrameTime();
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

void Window::_handle_logic(float dt) {
    mGame.mCursorPos = GetMousePosition();
    mGame.handle_logic(dt);
}

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

void Window::toggle_fullscreen() {
    if (!IsWindowFullscreen()){
        Vector2 display_size = Vector2{(float)GetMonitorWidth(0), (float)GetMonitorHeight(0)};
        std::cout << display_size.x << ", " << display_size.y << std::endl;
        this->set_window_size(display_size);
    } else {
        this->set_window_size(Vector2(1280, 720));
    }
    ToggleFullscreen();
}
