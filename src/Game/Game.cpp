#include "Game.hpp"
#include "../Object/ObjButton.hpp"
#include "../Object/ObjText.hpp"
#include "../Window/Window.hpp"

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

    mSMan.add_shader("menu", nullptr, "./src/Shaders/menu_fragment.glsl");

    _sync_scale();

    // TODO: make it dynamic and generate the font size using the mScale value
    Vector2 *wsize = w->get_window_size();
    Texture2D *board_txt =
        mTexMan.load_texture("board_txt", "./assets/board-real.png");

    sptr_t<Object> board_obj = mObjMan.add_object(
        mk_sptr<Object>(Object({}, z_index, "board", board_txt)));
    _center_board(board_obj);
    board_obj->mTag = GameState::INGAME;

    z_index++;

    static const char *title_name = "UwUrg";
    static const int title_font_size = 64;
    sptr_t<Object> title_obj = mObjMan.add_object(mk_sptr<ObjText>(
        Rectangle{}, z_index, "title", title_name, GetColor(0xfffb96FF), title_font_size));
    title_obj->mTag = GameState::MENU;

    // CAN BE REFACTORED TO A FUNCTION LATER.
    if (auto titleText = std::dynamic_pointer_cast<ObjText>(title_obj)) {
        titleText->mRec.x =
            (wsize->x - MeasureTextEx(mFont, title_name, titleText->mSize,
                                      titleText->mSpacing)
                            .x) /
            2;
        titleText->mRec.y = titleText->mSize * 2;
    }

    z_index++;

    static const int button_font_size = 40;
    static const char *play_button = "PLAY";

    sptr_t<Object> play_b_obj = mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "play_obj", play_button, GetColor(0x153CB4FF), WHITE,
        button_font_size, 10,
        [this]() { this->mStateOrTag = GameState::INGAME; }));
    play_b_obj->mTag = GameState::MENU;

    if (auto playButton = std::dynamic_pointer_cast<ObjButton>(play_b_obj)) {
        auto textSize = MeasureTextEx(mFont, play_button, playButton->mSize,
                                      playButton->mSpacing);
        playButton->mRec.x = (wsize->x - textSize.x) / 2;
        playButton->mRec.y = (wsize->y - playButton->mSize) / 2;
        playButton->mRec.width = textSize.x;
        playButton->mRec.height = playButton->mSize;
    }

    z_index++;

    static const char *settings_button = "Settings";
    sptr_t<Object> settings_b_obj = mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "settings_obj", settings_button, GetColor(0x153CB4FF), WHITE,
        button_font_size, 10,
        []() { TraceLog(LOG_INFO, "WIP Please be patien."); }));
    settings_b_obj->mTag = GameState::MENU;

    if (auto settButton =
            std::dynamic_pointer_cast<ObjButton>(settings_b_obj)) {
        auto textSize = MeasureTextEx(mFont, settings_button, settButton->mSize,
                                      settButton->mSpacing);
        settButton->mRec.x = (wsize->x - textSize.x) / 2;
        settButton->mRec.y =
            play_b_obj->mRec.y + play_b_obj->mRec.height + settButton->mSize;
        settButton->mRec.width = textSize.x;
        settButton->mRec.height = settButton->mSize;
    }

    z_index++;

    static const char *exit_button = "EXIT";

    sptr_t<Object> exit_b_obj = mObjMan.add_object(mk_sptr<ObjButton>(
        Rectangle{}, z_index, "exit_obj", exit_button, GetColor(0xE93479FF), WHITE,
        button_font_size, 10, [this]() { this->exit_game(); }));
    exit_b_obj->mTag = GameState::MENU;

    if (auto exitButton = std::dynamic_pointer_cast<ObjButton>(exit_b_obj)) {
        auto textSize = MeasureTextEx(mFont, exit_button, exitButton->mSize,
                                      exitButton->mSpacing);
        exitButton->mRec.x = (wsize->x - textSize.x) / 2;
        exitButton->mRec.y = settings_b_obj->mRec.y +
                             settings_b_obj->mRec.height + exitButton->mSize;
        exitButton->mRec.width = textSize.x;
        exitButton->mRec.height = exitButton->mSize;
    }

    z_index++;
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
    DrawText(version, 0 + 10, wsize->y - font_size - (font_size * 0.5), font_size,
             WHITE);
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
