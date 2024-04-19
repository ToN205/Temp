//
// Created by Administrator on 01/03/2024.
//

#ifndef PROJECT_NAME_COMMONFUNC_H
#define PROJECT_NAME_COMMONFUNC_H
#include "windows.h"
#include "string"
#include "SDL.h"
#include "SDL_image.h"
#include "vector"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

const int PRAME_PER_SECOND = 25;
static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event g_event ;

static Mix_Chunk *g_sound_bullet[2];
static Mix_Chunk *g_sound_exp[2];
static Mix_Chunk *sound_battle;
static Mix_Chunk *sound_coin;
static bool Sound_On = true;
static bool Music_On = true;


const int SCREEEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;
#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define COIN 4
struct Input{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};
struct Map{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile [MAX_MAP_Y][MAX_MAP_X];
    char *file_name_;
};
namespace SDLCommonFunc{
    bool CheckCollision(const SDL_Rect &object1, const SDL_Rect &object2);
}
#endif //PROJECT_NAME_COMMONFUNC_H
