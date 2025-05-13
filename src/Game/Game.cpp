#include "Game.hpp"
#include "../Object/ObjText.hpp"
#include "../Shaders/ingameShaders.hpp"
#include "../Shaders/menuShaders.hpp"
#include "../Window/Window.hpp"
#include "GameBot.hpp"
#include "GameUtils.hpp"

#define DEBUG_MODE

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
    mPosMove = {};
    mVSBot = false;
    mScore = {0, 0};
    mBot = new GameBot();
}

Game::~Game() { UnloadFont(mFont); }

void Game::init(Window *w) {
    mWindow_ptr = w;
    mObjMan.mGame_ptr = this;
    mBot->mGame_ptr = this;
    int z_index = 1;

    mFont =
        LoadFontEx("./assets/Pixelify_Sans/PixelifySans-VariableFont_wght.ttf",
                   96, NULL, 95);
    if (mFont.texture.id == 0)
        TraceLog(LOG_FATAL,
                 TextFormat("%s\n",
                            "Try to launch the game from the correct path."
                            " The game expect the `assets` folder in cwd."));

    mSMan.add_shader_from_mem("menu", nullptr, menu_shaders);
    mSMan.add_shader_from_mem("ingame", nullptr, ingame_shaders);

    _sync_scale();

    _create_ingame_object(this, z_index);
    _create_menu_object(this, z_index);
    _create_settings_object(this, z_index);
    _create_play_menu_object(this, z_index);
    _create_finish_menu_object(this, z_index);

    _recalculate_all_pos(this);

    _ingame_getdice(this);
    mPosMove = get_possible_move(this);
}

void Game::handle_logic(float dt) {
    GameState current_state = mStateOrTag;
    for (auto &d : mObjMan.mData) {
        if (current_state != mStateOrTag) {
            // TODO: Do something here...
            break;
        }
        std::optional<GameTurn> winnning = game_check_win(this);
        if (winnning.has_value()) {
            sptr_t<Object> label = mObjMan.get_object("win_label");
            if (label != nullptr) {
                if (auto labelCasted =
                        std::dynamic_pointer_cast<ObjText>(label)) {
                    const char *winner = winnning.value() == GameTurn::PLAYER1
                                             ? "Player 1"
                                             : "Player 2";
                    labelCasted->mText = TextFormat("%s Win.", winner);
                    _position_finish_menu_object(this);
                }
            }
        }

        if (mVSBot && mTurn == GameTurn::PLAYER2)
            continue;

        if (has_flag(d->mTag, mStateOrTag))
            d->logic(dt);
    }
}

void Game::handle_drawing(float dt) {
    (void)dt;

    const char *shaders_str =
        (mStateOrTag == GameState::INGAME || mStateOrTag == GameState::FINISHED)
            ? "ingame"
            : "menu";
    Shader *s = mSMan.get_shader(shaders_str);
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

    switch (mStateOrTag) {
    case GameState::ALL: {
        break;
    }
    case GameState::INGAME: {

        if (IsKeyReleased(KEY_ESCAPE)) {
            mStateOrTag = GameState::MENU;
            _ingame_reset_state(this);
            _ingame_getdice(this);
        }

        // IDK MAN This thing always block without any good reason...
        // if (mVSBot && mTurn == GameTurn::PLAYER2)
        //     break;

        if (IsKeyReleased(KEY_N)) {
            // TODO: Handle error
            game_new_bead_helper(this);
        }

#ifdef DEBUG_MODE
        if (IsKeyReleased(KEY_G)) {
            mScore[(int)mTurn] = 6;
        }
#endif

        // TODO: Handle error
        static const int start_at = 49;
        for (int i = KEY_ONE; i <= KEY_SEVEN; i++) {
            if (IsKeyReleased(i)) {
                game_move_bead_helper(this, i - start_at);
            }
        }

        if (IsKeyReleased(KEY_SPACE)) {
            if (mDice <= 0 || mPosMove.empty()) {
                _ingame_getdice(this);
                game_change_turn(this);
            }
        }
        break;
    }

    case GameState::PLAYMENU: {
        if (IsKeyReleased(KEY_E)) {
            _start_game(this, true);
        }
        if (IsKeyReleased(KEY_Q)) {
            _start_game(this, false);
        }
        if (IsKeyReleased(KEY_ESCAPE)) {
            mStateOrTag = GameState::MENU;
        }
        break;
    }
    case GameState::MENU: {
        if (IsKeyReleased(KEY_P)) {
            mStateOrTag = GameState::PLAYMENU;
        }
        if (IsKeyReleased(KEY_S)) {
            mStateOrTag = GameState::SETTINGS;
        }
        if (IsKeyReleased(KEY_ESCAPE)) {
            exit_game();
        }
        break;
    }
    case GameState::SETTINGS: {
        if (IsKeyReleased(KEY_E)) {
            _window_flag_helper(this);
        }
        if (IsKeyReleased(KEY_Q)) {
            _window_res_helper(this);
        }
        if (IsKeyReleased(KEY_ESCAPE)) {
            mStateOrTag = GameState::MENU;
        }
        break;
    }
    case GameState::FINISHED: {
        break;
    }
    default:
        break;
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
