//
// Created by Administrator on 26/03/2024.
//

#ifndef PROJECT_NAME_IMPTIMER_H
#define PROJECT_NAME_IMPTIMER_H
class ImpTimer{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();

    bool is_started();
    bool is_paused();
private:
    int start_tick_;
    int paused_tick_;

    bool is_paused_;
    bool is_started_;

};
#endif //PROJECT_NAME_IMPTIMER_H
