//
// Created by Administrator on 18/04/2024.
//
#include "PlayPower.h"
PlayPower::PlayPower() {
    number_ = 0;

}
PlayPower::~PlayPower() = default;
void PlayPower::AddPos(const int &xPos) {
    pos_list_.push_back(xPos);
}
void PlayPower::Init(SDL_Renderer *screen) {
    LoadImg("player.png", screen);
    number_ = 2;
    if(pos_list_.size() > 0){
        pos_list_.clear();
    }
    AddPos(20);
    AddPos(50);

}
void PlayPower::Show(SDL_Renderer *screen) {
    for(int i = 0; i < pos_list_.size(); i++){
        rect_.x = pos_list_.at(i);
        rect_.y = 0;
        Render(screen);
    }
}
void PlayPower::Decrease() {
    number_ --;
    pos_list_.pop_back();
}
void PlayPower::InitCrease() {
    number_ ++;
    int last_pos = pos_list_.back();
    last_pos += 40;
    pos_list_.push_back(last_pos);
}
PlayerCoin::PlayerCoin() {
    x_pos_ = SCREEEN_WIDTH*0.5 - 300;
    y_pos_ = 8;
}
PlayerCoin::~PlayerCoin() = default;
bool PlayerCoin::Init (SDL_Renderer *screen){
    bool ret = LoadImg("coin.png", screen);
    return ret;

}
void PlayerCoin::Show(SDL_Renderer *screen) {
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);

}