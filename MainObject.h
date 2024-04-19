//
// Created by Administrator on 09/03/2024.
//

#ifndef PROJECT_NAME_MAINOBJECT_H
#define PROJECT_NAME_MAINOBJECT_H
#include "CommonFunc.h"
#include "BaseObject.h"
#include "vector"
#include "BulletObject.h"

#define GRAVITY_SPEED 5
#define MAX_FALL_SPEED 20
#define PLAYER_SPEED 10
#define PLAYER_JUMP_VAL 50
class MainObject : public BaseObject{
public:
    MainObject();
    ~MainObject();

    enum WalkType{
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };
    bool LoadImg( std::string path, SDL_Renderer* screen);

    void Show(SDL_Renderer *des);
    void HandelIputAction(SDL_Event events, SDL_Renderer *screen, Mix_Chunk *bullet_sound[2]);
    void set_clip();

    void DoPlayer(Map &map_data, Mix_Chunk *k);
    void CheckToMap (Map &map_data, Mix_Chunk  *b);

    void UpdateImagePlayer(SDL_Renderer  *des);

    void SetMapXY(const int map_x, const int map_y){
        map_x_ = map_x;
        map_y_ = map_y;
    }
    void CenterEntityOnMap (Map& map_data) const;
    void Increas_Coin();

    void set_bullet_list(std::vector<BulletObject*> bullet_list){
        p_bullet_list_ = bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list(){
        return p_bullet_list_;
    };
    void HandleBullet(SDL_Renderer *des);
    void RemoveBullet(const int &idx);
    SDL_Rect GetRectFrame();
    void set_come_back_time(const int &cbt){
        come_back_time = cbt;
    }
    int GetCountCoin(){
        return count_coin;
    }
private:
    std::vector<BulletObject*> p_bullet_list_;
    int count_coin ;
    int x_val_;
    int y_val_;

    int x_pos_;
    int y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8]{};
    Input input_type_{};
    int frame_;
    int status_;
    bool on_ground_;

    int map_x_;
    int map_y_;

    int come_back_time;


};

#endif //PROJECT_NAME_MAINOBJECT_H
