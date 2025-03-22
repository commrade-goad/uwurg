#include "Window/Window.hpp"

// TODO: decide to use public or private on Object, ObjectManager, TextureManager

int main(void) {
    Window w(Vector2(1280, 720), "UwUrg", 60, KEY_Q);
    w.start_window_loop();
    return 0;
}
