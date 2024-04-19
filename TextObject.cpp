#include"TextObject.h"

TextObject::TextObject()
{
    BaseObject();
    text_color_.r = 0;
    text_color_.g = 0;
    text_color_.b = 0;
    bg_color_.r = 0;
    bg_color_.g = 255;
    bg_color_.b = 255;
}
TextObject::~TextObject() = default;
bool TextObject::LoadFromRenderText( TTF_Font* font, SDL_Renderer* screen)
{

    SDL_Surface* textSurface = TTF_RenderText_Solid( font, str_val_.c_str(), text_color_);
    if( textSurface != nullptr )
    {
        p_objcet_ = SDL_CreateTextureFromSurface( screen, textSurface );
        if( p_objcet_ == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            rect_.w = textSurface->w;
            rect_.h = textSurface->h;
        }
    }
    SDL_FreeSurface( textSurface );
    return p_objcet_ != nullptr;
}

bool TextObject::LoadFromRenderTextShaded( TTF_Font* font, SDL_Renderer* screen)
{

    SDL_Surface* textSurface = TTF_RenderText_Shaded( font, str_val_.c_str(), text_color_, bg_color_);
    if( textSurface != NULL )
    {
        p_objcet_ = SDL_CreateTextureFromSurface( screen, textSurface );
        if( p_objcet_ == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            rect_.w = textSurface->w;
            rect_.h = textSurface->h;
        }
    }
    SDL_FreeSurface( textSurface );
    return p_objcet_!=NULL;
}

bool TextObject::CheckFocus(int xp, int yp)
{
    if (xp >= rect_.x && xp <= rect_.x+rect_.w &&
        yp >= rect_.y && yp <= rect_.y+rect_.h)
    {
        return true;
    }
    return false;
}

void TextObject::SetColor( Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}

void TextObject::SetColor(int Type)
{
    switch(Type)
    {
        case RED_TEXT:
            SetColor( 255, 0 , 0);
            break;
        case WHITE_TEXT:
            SetColor( 255, 255, 255);
            break;
        case BLACK_TEXT:
            SetColor( 0, 0, 0);
            break;
        case YELLOW_TEXT:
            SetColor( 255, 215, 0);
            break;
        case ORANGE_TEXT:
            SetColor(255,140,0);
            break;
        case BLUE_TEXT:
            SetColor(0,255,255);
            break;
    }
}

void TextObject::RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip, double angle,
                            SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {xp, yp, rect_.w, rect_.h};
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(screen, p_objcet_, clip, &renderQuad, angle, center, flip);
}
