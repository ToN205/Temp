#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 640;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

#endif // INCLUDE_H_INCLUDED
