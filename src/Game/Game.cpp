#include "Game.hpp"
#include "../Window/Window.hpp"
#include "../Object/ObjBead.hpp"
#include "GameUtils.hpp"
#include "../Shaders/menuShaders.hpp"

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

    mTurn = GameTurn::PLAYER1;
    mPaused = false;
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
    mSMan.add_shader_from_mem("menu", nullptr, menu_shaders);

    _sync_scale();

    _create_ingame_object(this, &z_index);
    _create_menu_object(this, &z_index);
    _create_settings_object(this, &z_index);

    _recalculate_all_pos(this);

    _ingame_getdice(this);
}

void Game::handle_logic(float dt) {
    GameState current_state = mStateOrTag;
    for (auto &d : mObjMan.mData) {
        if (current_state != mStateOrTag) {
            // TODO: Do something here...
            break;
        }
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

    DrawRectangle(0, 0, wsize->x, wsize->y, WHITE);

    EndShaderMode();
    for (auto &d : mObjMan.mData) {
        if (has_flag(d->mTag, mStateOrTag))
            d->render();
    }
    _render_version(this);
}

void Game::handle_key(float dt) {
    (void)dt;
    if (IsKeyReleased(KEY_N)) {
        sptr_t<Object> a = mObjMan.get_object("test_bead");
        if (auto b = std::dynamic_pointer_cast<ObjBead>(a)) {
            b->mPos++;
        }
    }
}

void Game::_sync_scale() {
    Vector2 *wsize = mWindow_ptr->get_window_size();
    if (wsize->y <= 640)
        mScale = 3;
    if (wsize->y == 720)
        mScale = 4;
    if (wsize->y >= 1080)
        mScale = 6;
}

void Game::exit_game() { mWantExit = true; }
