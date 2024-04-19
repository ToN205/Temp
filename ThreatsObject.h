//
// Created by Administrator on 13/04/2024.
//

#ifndef PROJECT_NAME_THREATSOBJECT_H
#define PROJECT_NAME_THREATSOBJECT_H
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_MAX_FALL_SPEED 10
#define THREAT_GRAVITY_SPEED 1
#define THREAT_FRAME_NUM 8
#define THREAT_SPEED 3
class ThreatsObject : public BaseObject{
public:
    ThreatsObject();
    ~ThreatsObject();

    enum TypeMove{
        STATIC_THREAT = 0,
        MOVE_IN_SPACE = 1,
    };
    void set_x_val(const int &xVal){
        x_val_ = xVal;
    }
    void set_y_val(const int &yVal){
        y_val_ = yVal;
    }
    void set_x_pos(const int &xPos){
        x_pos_ = xPos;
    }
    void set_y_pos(const int &yPos){
        y_pos_ = yPos;
    }
    int get_y_pos(){
        return y_pos_;
    };
    int get_x_pos() const{
        return x_pos_;
    }
    void SetMapXY(const int &mp_x, const int &mp_y){
        map_x_ = mp_x;
        map_y_ = mp_y;
    }
    void set_clips();
    void set_clipss();
    bool LoadImg(std::string path, SDL_Renderer *screen);
    bool LoadImgs(std::string path, SDL_Renderer *screen);
    void Show(SDL_Renderer *des);
    void Shows(SDL_Renderer *des);
    int get_width_frame() const{
        return width_frame_;
    }
    int get_height_frame_() const{
        return height_frame_;
    }
    void DoPlayer(Map &gMap);
    void CheckToMap(Map &gMap);
    void set_type_move(const int &typeMove){
        type_move_ = typeMove;
    }
    void SetAnimationPos(const int &pos_a, const int &pos_b){
        animation_a_ = pos_a;
        animation_b_ = pos_b;
    }
    void set_input_left(const int &ipleft){
        input_type.left_ = ipleft;
    }
    void ImpMoveType(SDL_Renderer *screen);
    void InitThreat();

    std::vector<BulletObject*> get_bullet_list(){
        return bullet_list_;
    }
    void set_bullet_list(const std::vector<BulletObject*> bl){
        bullet_list_ = bl;
    }
    void InitBullet(BulletObject *p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer *screen, const int &x_limit, const int &y_limit);
    void RemoveBullet(const int &idx);
    SDL_Rect GetRectFrame();
private:
    int map_x_;
    int map_y_;
    int x_val_;
    int y_val_;
    int x_pos_;
    int y_pos_;
    bool on_ground_;
    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    int frame_;
    int come_back_time_;

    int type_move_;
    int animation_a_;
    int animation_b_;
    Input input_type;

    std::vector<BulletObject*> bullet_list_;
};

#endif //PROJECT_NAME_THREATSOBJECT_H
