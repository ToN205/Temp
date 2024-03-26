//
// Created by Administrator on 01/03/2024.
//

#ifndef PROJECT_NAME_COMMONFUNC_H
#define PROJECT_NAME_COMMONFUNC_H
#include "windows.h"
#include "string"
#include "SDL.h"
#include "SDL_image.h"

const int PRAME_PER_SECOND = 25;
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event ;

const int SCREEEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 93;
const int COLOR_KEY_G = 109;
const int COLOR_KEY_B = 98;

const int RENDER_DRAW_COLOR = 255;
#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
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
#endif //PROJECT_NAME_COMMONFUNC_H
