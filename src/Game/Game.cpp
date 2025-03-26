#include "Game.hpp"
#include "../Object/ObjButton.hpp"
#include "../Object/ObjText.hpp"
#include "../Window/Window.hpp"
#include "GameUtils.hpp"

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
    mSMan = ShadersManager();
    mWindow_ptr = nullptr;
    mStateOrTag = GameState::MENU;
    mScale = 0;
    mFont = Font();
    mCursorPos = Vector2();
    mWantExit = false;
}

Game::~Game() { UnloadFont(mFont); }

void Game::init(Window *w) {
    mWindow_ptr = w;
    mObjMan.mGame_ptr = this;
    int z_index = 1;

    mFont =
        LoadFontEx("./assets/Pixelify_Sans/PixelifySans-VariableFont_wght.ttf",
                   96, NULL, 95);

    // TODO: Move the shaders to assets or embed to the executeable.
    mSMan.add_shader("menu", nullptr, "./src/Shaders/menu_fragment.glsl");

    _sync_scale();

    // TODO: make it dynamic and generate the font size using the mScale value
    Texture2D *board_txt =
        mTexMan.load_texture("board_txt", "./assets/board-real.png");

    sptr_t<Object> board_obj = mObjMan.add_object(
        mk_sptr<Object>(Object({}, z_index, "board", board_txt)));
    _center_board(board_obj);
    board_obj->mTag = GameState::INGAME;

    z_index++;

    create_menu_object(this, &z_index);
    position_menu_object(this, w);
}

void Game::handle_logic(float dt) {
    (void)dt;

    for (auto &d : mObjMan.mData) {
        if (has_flag(d->mTag, mStateOrTag))
            d->logic(dt);
    }
}

void Game::handle_drawing(float dt) {
    (void)dt;

    Shader *s = mSMan.get_shader("menu");
    int sWidth = GetShaderLocation(*s, "sWidth");
    int sHeight = GetShaderLocation(*s, "sHeight");

    Vector2 *wsize = mWindow_ptr->get_window_size();
    SetShaderValue(*s, sWidth, &wsize->x, SHADER_UNIFORM_FLOAT);
    SetShaderValue(*s, sHeight, &wsize->y, SHADER_UNIFORM_FLOAT);

    BeginShaderMode(*s);

    DrawRectangle(0, 0, 1280, 720, WHITE);

    EndShaderMode();
    // if i move DrawRectangle here its working
    // DrawRectangle(0, 0, 1280, 720, WHITE);
    for (auto &d : mObjMan.mData) {
        if (has_flag(d->mTag, mStateOrTag))
            d->render();
    }
    _render_version();
}

void Game::handle_key(float dt) {
    (void)dt;
    if (IsKeyPressed(KEY_F)) {
        if (mScale == 4)
            mWindow_ptr->set_window_size(Vector2(854, 480));
        else
            mWindow_ptr->set_window_size(Vector2(1280, 720));
        _sync_scale();
        sptr_t<Object> b = mObjMan.get_object("board");
        _center_board(b);
    }
}

void Game::_sync_scale() {
    Vector2 *wsize = mWindow_ptr->get_window_size();
    if (wsize->y <= 640)
        mScale = 3;
    if (wsize->y == 720)
        mScale = 4;
    if (wsize->y >= 1080)
        mScale = 5;
}

inline void Game::_render_version() {
    static const int font_size = 16;
    static const char *version = "Ver 0.0.1-development";
    auto wsize = mWindow_ptr->get_window_size();
    DrawText(version, 0 + 10, wsize->y - font_size - (font_size * 0.5),
             font_size, WHITE);
}

void Game::_center_board(sptr_t<Object> object) {
    if (object->mText->width <= 0 && object->mText->height <= 0)
        return;

    Vector2 *wsize = mWindow_ptr->get_window_size();
    object->mRec = {(wsize->x - (object->mText->width * mScale)) / 2,
                    (wsize->y - (object->mText->height * mScale)) / 2,
                    (float)object->mText->width * mScale,
                    (float)object->mText->height * mScale};
}

void Game::exit_game() { mWantExit = true; }
