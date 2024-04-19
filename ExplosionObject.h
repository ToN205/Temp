//
// Created by Administrator on 17/04/2024.
//
#include "CommonFunc.h"
#include "BaseObject.h"
#ifndef PROJECT_NAME_EXPLOSIONOBJECT_H
#define PROJECT_NAME_EXPLOSIONOBJECT_H
#define NUM_FRAME_EXP 1
class ExplosionObject : public BaseObject{
public:
    ExplosionObject();
    ~ExplosionObject();

    void set_clip();
    void set_frame(const int &fr){
        frame_ = fr;
    }
    virtual bool LoadImg(std::string path, SDL_Renderer *screen);
    void Show(SDL_Renderer *screen);
    int get_frame_width() const{
        return frame_width_;
    }
    int get_frame_height_() const{
        return frame_height_;
    }

private:
    int frame_width_;
    int frame_height_;
    int frame_;
    SDL_Rect frame_clip_[1];
};
#endif //PROJECT_NAME_EXPLOSIONOBJECT_H
