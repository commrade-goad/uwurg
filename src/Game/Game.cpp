#include "Game.hpp"
#include "../Object/ObjText.hpp"
#include "../Shaders/beadShaders.hpp"
#include "../Shaders/ingameShaders.hpp"
#include "../Shaders/menuShaders.hpp"
#include "../Window/Window.hpp"
#include "GameBot.hpp"
#include "GameUtils.hpp"

/* #define DEBUG_MODE */

auto winSound = std::pair<bool, ManagedSound *>(true, nullptr);

Game::Game() {
    mTexMan = TextureManager();
    mObjMan = ObjectManager();
    mSMan = ShadersManager();
    mSouMan = SoundManager();
    mWindow_ptr = nullptr;
    mStateOrTag = GameState::MENU;
    mOldStateOrTag = mStateOrTag;
    mScale = 0;
    mFont = Font();
    mCursorPos = Vector2();
    mWantExit = false;

    mTurn = GameTurn::PLAYER1;
    mPosMove = {};
    mScore = {0, 0};
    mVSBot = false;
    mBot = new GameBot(1.5);
    mBotCanMove = true;
    winSound.first = true;
}

Game::~Game() {
    UnloadFont(mFont);
    UnloadMusicStream(mMusic);
}

void Game::init(Window *w) {
    mWindow_ptr = w;
    mObjMan.mGame_ptr = this;
    mBot->mGame_ptr = this;
    int z_index = 1;

    mWindow_ptr->set_app_icon("./assets/nayeon.png");
    mSouMan.load_sound("./assets/bead-placed.wav", "bead_placed");
    mSouMan.load_sound("./assets/victory-96688.mp3", "victory");
    winSound.second = mSouMan.get_sound("victory");
    if (winSound.second)
        SetSoundVolume(winSound.second->mData, 0.2);
    // TODO: Refactor to be its own class
    mMusic = LoadMusicStream("./assets/background-music.mp3");

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
    mSMan.add_shader_from_mem("bead", nullptr, bead_shaders);

    _sync_scale();

    _create_ingame_object(this, z_index);
    _create_menu_object(this, z_index);
    _create_settings_object(this, z_index);
    _create_play_menu_object(this, z_index);
    _create_finish_menu_object(this, z_index);
    _create_help_object(this, z_index);

    _recalculate_all_pos(this);

    _ingame_getdice(this);
    mPosMove = get_possible_move(this);

    // Play the music.
    PlayMusicStream(mMusic);
    SetMusicVolume(mMusic, VOL_NORMAL);
}

void Game::handle_logic(float dt) {
    // To keep the stream alive it seems.
    UpdateMusicStream(mMusic);
    GameState current_state = mStateOrTag;

    // If the current state not menu then decrase the volume more.
    if (current_state == GameState::INGAME ||
        current_state == GameState::FINISHED)
        SetMusicVolume(mMusic, VOL_LOW);

    for (auto &d : mObjMan.mData) {
        if (current_state != mStateOrTag) {
            // TODO: Do something here...
            break;
        }
        std::optional<GameTurn> winnning = game_check_win(this);
        if (winnning.has_value()) {
            if (winSound.first) {
                TraceLog(LOG_INFO, "Playing the winning sound");
                winSound.second->play_sound();
                winSound.first = false;
            }
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

        if (mVSBot && mTurn == GameTurn::PLAYER2) {
            if (!mBotCanMove && mBot->check_timer()) {
                mBotCanMove = true;
                move_bot_wrapper(this);
            }
            // continue;
        }

        if (has_flag(d->mTag, mStateOrTag))
            d->logic(dt);
    }
}

void Game::handle_drawing(float dt) {
    (void)dt;

    // TODO use better way.
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
            change_state(GameState::MENU);
            _ingame_reset_state(this);
            _ingame_getdice(this);
            SetMusicVolume(mMusic, VOL_NORMAL);
        }

        if (mVSBot && mTurn == GameTurn::PLAYER2)
            break;

        if (IsKeyReleased(KEY_N)) {
            // TODO: Handle error
            game_new_bead_helper(this);
        }

#ifdef DEBUG_MODE
        if (IsKeyReleased(KEY_G)) {
            mScore[(int)mTurn] = 7;
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
            change_state(GameState::MENU);
        }
        break;
    }
    case GameState::MENU: {
        if (IsKeyReleased(KEY_P)) {
            change_state(GameState::PLAYMENU);
        }
        if (IsKeyReleased(KEY_S)) {
            change_state(GameState::SETTINGS);
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
            change_state(GameState::MENU);
        }
        break;
    }
    case GameState::FINISHED: {
        if (IsKeyReleased(KEY_E)) {
            _finish_restart_game(this);
        }
        if (IsKeyReleased(KEY_Q)) {
            _finish_exit_main(this);
        }
        break;
    }
    case GameState::TUTORIAL: {
        if (IsKeyReleased(KEY_ESCAPE)) {
            revert_state();
        }
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

void Game::change_state(GameState new_state) {
    mOldStateOrTag = mStateOrTag;
    mStateOrTag = new_state;
}

void Game::revert_state() {
    mStateOrTag = mOldStateOrTag;
}

void Game::exit_game() { mWantExit = true; }

void set_winsound_playable(bool p) { winSound.first = p; }
