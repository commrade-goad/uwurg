
#include "GameUtils.hpp"

inline void Game::_sync_scale() {
    Vector2 *wsize = mWindow_ptr->get_window_size();
    if (wsize->y <= 640)
        mScale = 3;
    if (wsize->y == 720)
        mScale = 4;
    if (wsize->y >= 1080)
        mScale = 5;
}

inline void Game::_center_n_resize_2_texture_object(const char *obj_name) {
    Vector2 *wsize = mWindow_ptr->get_window_size();
    auto board = mObjMan.get_object(obj_name);
    board->mRec = {(wsize->x - (board->mText->width * mScale)) / 2,
                   (wsize->y - (board->mText->height * mScale)) / 2,
                   (float)board->mText->width * mScale,
                   (float)board->mText->height * mScale};
}

inline void Game::_center_n_resize_2_texture_object(sptr_t<Object> object) {
    Vector2 *wsize = mWindow_ptr->get_window_size();
    object->mRec = {(wsize->x - (object->mText->width * mScale)) / 2,
                    (wsize->y - (object->mText->height * mScale)) / 2,
                    (float)object->mText->width * mScale,
                    (float)object->mText->height * mScale};
}
