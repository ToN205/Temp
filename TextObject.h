#ifndef TEXTOBJECT_H_INCLUDED
#define TEXTOBJECT_H_INCLUDED

#include"include.h"
#include "BaseObject.h"

class TextObject : public BaseObject
{
public:
    TextObject();
    enum{
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
        YELLOW_TEXT = 3,
        ORANGE_TEXT = 4,
        BLUE_TEXT = 5,
    };

    bool LoadFromRenderText( TTF_Font* font, SDL_Renderer* screen);
    bool LoadFromRenderTextShaded( TTF_Font* font, SDL_Renderer* screen);
    bool CheckFocus(int xp, int yp);

    void SetColor( Uint8 red, Uint8 green, Uint8 blue);
    void SetColor( int Type);

    void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle = 0.0,
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    string getText(){return str_val_;};
    void SetText(const string& text) { str_val_ = text;};
private:
    string str_val_;
    SDL_Color text_color_;
    SDL_Color bg_color_;
};

#endif // TEXTOBJECT_H_INCLUDED
