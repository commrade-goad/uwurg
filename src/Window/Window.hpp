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
    Color mDefaultBgColor;

    void Phandle_drawing();
    void Phandle_key();
    void Phandle_logic();

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
};

#endif // WINDOW_H_
