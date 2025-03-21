#ifndef WINDOW_H_
#define WINDOW_H_

#include <cstddef>
#include <raylib.h>
#include "../Game/Game.hpp"

struct Window {
  private:
    Vector2 mSize;
    const char *mName;

    int mExitKey;
    size_t mFPS;
    Color mDefaultBgColor;

    Game mGame;

    void _handle_drawing(float dt);
    void _handle_key(float dt);
    void _handle_logic(float dt);
    void _check_msg();

  public:
    Window(Vector2 size, const char *title);
    Window(Vector2 size, const char *title, size_t fps);
    Window(Vector2 size, const char *title, size_t fps, int exit_key);
    ~Window();

    bool start_window_loop();

    void set_window_size(Vector2 size);
    Vector2 get_window_size();

    void set_bg_color(Color color);
    Color get_bg_color();

    void set_fps_target(size_t fps);
    size_t get_fps_target();

    void set_exit_key(int key);
    size_t get_exit_key();

    const char *get_name();
};

#endif // WINDOW_H_
