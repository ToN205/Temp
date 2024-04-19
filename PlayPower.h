//
// Created by Administrator on 18/04/2024.
//

#ifndef PROJECT_NAME_PLAYPOWER_H
#define PROJECT_NAME_PLAYPOWER_H
#include "CommonFunc.h"
#include "BaseObject.h"
class PlayPower : public BaseObject{
public:
    PlayPower();
    ~PlayPower();
    void SetNum(const int &num){
        number_ = num;
    }
    void AddPos(const int &xPos);
    void Show(SDL_Renderer *screen);
    void Init(SDL_Renderer *screen);

    void InitCrease();
    void Decrease();
private:
    int number_;
    std::vector<int> pos_list_;
};
class PlayerCoin : public BaseObject{
public:
    PlayerCoin();
    ~PlayerCoin();

    bool Init (SDL_Renderer *screen);
    void Show(SDL_Renderer *screen);
    void SetPos(const int &x, const int &y){
        x_pos_ = x;
        y_pos_ = y;
    }
private:
    int x_pos_;
    int y_pos_;
};
#endif //PROJECT_NAME_PLAYPOWER_H
