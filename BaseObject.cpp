#include"BaseObject.h"

GTexture::GTexture(SDL_Renderer* Renderer)
{
    mTexture = NULL;
    mRender = Renderer;
    mWidth = mHeight = 0;
}

void GTexture::free()
{
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = mHeight = 0;
    }
}

bool GTexture::loadImage(string path)
{
    bool success = false;

    free();
    SDL_Surface* loadedSurface = NULL;
    loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
        cout << "Failed to upload Image! " << IMG_GetError() << "\n";
    else {
        SDL_SetColorKey(loadedSurface,SDL_TRUE, SDL_MapRGB(loadedSurface->format,0, 0xFF, 0xFF));
        mTexture = SDL_CreateTextureFromSurface(mRender,loadedSurface);
        if (mTexture == NULL)
            printf( "\nUnable to create texture from %s! SDL Error: %s", path.c_str(), SDL_GetError() );
        else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
            SDL_FreeSurface(loadedSurface);
            success = true;
        }
    }
    return success;
}

void GTexture::render(int x, int y, double angle, SDL_Point* Center, SDL_RendererFlip flip)
{
    SDL_Rect rect = {x, y, mWidth, mHeight};
    SDL_RenderCopyEx(mRender, mTexture, NULL, &rect, angle, Center, flip);
}
