#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED
#include"include.h"

class BaseObject{
public:
    BaseObject();
    void free();
    void SetRect(const int& x, const int &y){
        rect_.x = x, rect_.y =y;
    }
    SDL_Rect GetRect() const {return rect_;}
    SDL_Texture *GetObject() const {return  p_objcet_;}
    virtual bool LoadImg(std::string path, SDL_Renderer *screen);
    void Render(SDL_Renderer *des, const SDL_Rect *clip = nullptr);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha( Uint8 alpha );
protected:
    SDL_Texture* p_objcet_;
    SDL_Rect rect_;
};
#endif // BASEOBJECT_H_INCLUDED
