#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

class GTexture
{
public:
    GTexture(SDL_Renderer* Renderer = NULL);
    bool loadImage (string path);
    void render (int x, int y, double angle = 0.0, SDL_Point* Center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void free();
protected:
    SDL_Texture* mTexture;
    SDL_Renderer* mRender;
    int mWidth;
    int mHeight;
};
#endif // BASEOBJECT_H_INCLUDED
