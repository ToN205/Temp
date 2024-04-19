#include "CommonFunc.h"
#include "BaseObject.h"
#include "gamemap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayPower.h"
#include "Geometric.h"
#include "StartMenu.h"
BaseObject g_background, back_bg;
TTF_Font *font_time = nullptr;
// Khởi tạo dữ liệu của game
bool InitData(){
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
// Tạo cửa sổ game
    g_window = SDL_CreateWindow("Game cpp SDL",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(g_window == nullptr){
        success = false;
    }
    else{
        //tạo renderer
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == nullptr){
            success = false;
        }
        else{
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(IMG_Init(imgFlags) == 0){
                success = false;
            }
            if(TTF_Init() == -1){
                success = false;
            }
            font_time = TTF_OpenFont("dlxfont_.ttf", 15);
            if(font_time == nullptr){
                success = false;
            }
        }

// tạo âm thanh cho game
        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2 , 4096) == -1){
            return false;
        }
        g_sound_bullet[0] = Mix_LoadWAV("bullet1.wav");
        g_sound_bullet[1] = Mix_LoadWAV("bullet2.wav");
        g_sound_exp[0] = Mix_LoadWAV("exp.wav");
        sound_battle = Mix_LoadWAV("battle.wav");
        sound_coin = Mix_LoadWAV("coin.wav");
    }
    return success;
}
bool loadBackgound(){
    bool ret = g_background.LoadImg("background.png", g_screen);
    if(!ret){
        return false;
    }
    return true;
}
void close(){
    SDL_DestroyRenderer(g_screen);
        g_screen = nullptr;
        SDL_DestroyWindow(g_window);
        g_window = nullptr;
        IMG_Quit();
        SDL_Quit();
        TTF_Quit();
}
// tạo ra danh sách quái vật
std::vector<ThreatsObject*> MakeThreatList(){
    std::vector<ThreatsObject*> list_threats;
    auto* dynamic_threats = new ThreatsObject[20];
    for(int i = 0 ; i < 20; i++){
        ThreatsObject *p_threat = (dynamic_threats + i);
        if(p_threat != nullptr){
            p_threat->LoadImg("threat_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE);
            p_threat->set_x_pos(500 + i * 500);
            p_threat->set_y_pos(200);
            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            list_threats.push_back(p_threat);
        }
    }
    auto* threats_objs = new ThreatsObject[20];
    for(int i = 0; i < 20; i++){
        ThreatsObject* p_threat = (threats_objs + i);
        if(p_threat != nullptr){
            p_threat->LoadImg("threat_level.png",g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(700 + i * 1000);
            p_threat->set_y_pos(250);

            p_threat->set_input_left(0);
            auto* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}
// tạo menu game
int state = 0; //0: title screen, 1: in game, 2: Settings, 3: end;
bool win = false;
bool is_quit = false;

bool ret = InitData();
TTF_Font* font40 = TTF_OpenFont("imageSDL//font.ttf",40);
TTF_Font* titlefont = TTF_OpenFont("imageSDL//FzLongBeach.ttf",150);
TTF_Font* g_font_setting = TTF_OpenFont("imageSDL//SSWB.ttf",40);
Mix_Music* menu_music = Mix_LoadMUS("imageSDL//menu_mu"
                                    "sic.mp3");
Mix_Chunk* select_menu_effect = Mix_LoadWAV("imageSDL//selected_sound_effects.mp3");
Mix_Chunk* start_effect = Mix_LoadWAV("imageSDL//interface-124464.mp3");
Mix_Chunk* tick_effect = Mix_LoadWAV("imageSDL//medium.wav");
Mix_Chunk* game_over = Mix_LoadWAV("imageSDL/game-over-31-179699.mp3");
Mix_Music* victory_music = Mix_LoadMUS("imageSDL/sfx-victory1.mp3");

gameSDL Game(titlefont, font40, g_font_setting,
             select_menu_effect, start_effect, tick_effect, menu_music);
void MenuGame()
{

    while (!is_quit)
    {
        switch(state)
        {
            case 0: state = Game.titleScreen(g_screen); break;
            case 2: state = Game.Settings(g_screen); break;
            case 3: is_quit = true; break;
            case 4:
                back_bg.LoadImg("screenshot.png",g_screen);
                back_bg.Render(g_screen);
                if (win) {
                    state = Game.End_Message(g_screen,"Victory",titlefont);
                } else {
                    state = Game.End_Message(g_screen,"Game Over",titlefont);
                }
                break;
        }
        if (state == 1) break;
    }
}

int main(int argc, char* args []) {
    ImpTimer fps_timer;
    if(!loadBackgound()){
        return -1;
    }
    Game.LoadMedia(g_screen);
// tạo bản đồ
    GameMap game_map;
    game_map.LoadMap("map/map01.txt");
    game_map.LoadTiles(g_screen);

//tạo nhân vật game
    MainObject p_player;
    p_player.LoadImg("Run.png", g_screen);
    p_player.set_clip();


// tạo hình ảnh sinh mênh, đồng xu
    PlayPower player_power;
    player_power.Init(g_screen);

    PlayerCoin player_coin;
    player_coin.Init(g_screen);


// tạo danh sách các mối đe dọa
    std::vector<ThreatsObject*> threats_list = MakeThreatList();

// tạo đối tượng vụ nổ
    ExplosionObject exp_threat;
    ExplosionObject exp_main;
    bool tRet = exp_threat.LoadImg("exp.png", g_screen);
    if(!tRet) return -1;
    exp_threat.set_clip();

    bool ret = exp_main.LoadImg("exp.png", g_screen);
    exp_main.set_clip();
    if (!ret) return 0;

    int num_die = 0;


// hien thi text time
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

//hien thi text mark
    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    UINT mark_value = 0;

    TextObject coin;
    coin.SetColor(TextObject::WHITE_TEXT);

// vong lap chinh

       while(!is_quit){
           if(state == 1) {

               while (SDL_PollEvent(&g_event) != 0) {
                   if (g_event.type == SDL_QUIT) {
                       is_quit = true;
                   }
                   p_player.HandelIputAction(g_event, g_screen, g_sound_bullet + 1);
               }
               SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
                                      RENDER_DRAW_COLOR);
               SDL_RenderClear(g_screen);
               g_background.Render(g_screen, nullptr);


               Map map_data = game_map.getMap(); // lấy dữ liệu map
               p_player.HandleBullet(g_screen);
               p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
               p_player.DoPlayer(map_data, sound_coin);
               p_player.Show(g_screen);
               //p_player.CheckToMap(map_data, sound_coin);




               game_map.SetMap(map_data);
               game_map.DrawMap(g_screen);


// Ve hinh
               GeometricFormat rectangle_size(0, 0, SCREEEN_WIDTH, 40);
               ColorData color_data(0, 80, 150);
               Geometric::RenderRectangle(rectangle_size, color_data, g_screen);
               GeometricFormat outLineSize(1, 1, SCREEEN_WIDTH - 1, 38);
               ColorData color_data2(255, 255, 255);
               Geometric::RenderOutline(outLineSize, color_data2, g_screen);


               player_power.Show(g_screen);
               player_coin.Show(g_screen);
// xử lý các mối đe dọa
               for (auto p_threat: threats_list) {
                   if (p_threat != nullptr) {
                       p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                       p_threat->ImpMoveType(g_screen); // loại quái động hay tĩnh
                       p_threat->DoPlayer(map_data); // rơi xuống và đi lại
                       p_threat->MakeBullet(g_screen, SCREEEN_WIDTH, SCREEN_HEIGHT);
                       p_threat->Show(g_screen);


// xử lí va chạm của đạn quái và người chơi


                       SDL_Rect rect_player = p_player.GetRectFrame();
                       bool bCol1 = false;
                       std::vector<BulletObject *> tBullet_list = p_threat->get_bullet_list(); // lấy danh sách đạn quái
                       for (int jj = 0; jj < tBullet_list.size(); jj++) {
                           BulletObject *pt_bullet = tBullet_list.at(jj);
                           if (pt_bullet != nullptr) {
                               // đạn của quái và người chơi chạm vào nhau
                               bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                               if (bCol1) {
                                   p_threat->RemoveBullet(jj);
                                   break;
                               }
                           }
                       }
// check va chạm giữa quái và người chơi
                       SDL_Rect rect_threat = p_threat->GetRectFrame();
                       // va cham giữa quái và người chơi
                       bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                       if (bCol1 || bCol2) {
                           Mix_PlayChannel(-1, g_sound_exp[0], 0);
                           for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
                               int frame_exp_width = exp_main.get_frame_width();
                               int frame_exp_height = exp_main.get_frame_height_();
                               // vị trí của vụ nổ
                               int x_pos = p_player.GetRect().x - frame_exp_width * 0.5;
                               int y_pos = p_player.GetRect().y - frame_exp_height * 0.5;


                               exp_main.set_frame(ex);
                               exp_threat.SetRect(x_pos, y_pos);
                               exp_threat.Show(g_screen);
                           }
                           num_die++;
                           if (num_die <= 2) {
                               p_player.SetRect(0, 0);
                               p_player.set_come_back_time(60);
                               player_power.Decrease();
                               player_power.Render(g_screen);
                               //SDL_Delay(1000);
                               continue;
                           } else {
                               if (Sound_On) Mix_PlayChannel(-1,game_over,0);
                               win = false;
                               state = 4;
                           }
                       }
                   }
               }




// kiểm tra đạn của người chơi và quái vật


               std::vector<BulletObject *> bullet_arr = p_player.get_bullet_list();
               int frame_exp_width = exp_threat.get_frame_width();
               int frame_exp_height = exp_threat.get_frame_height_();


               for (int r = 0; r < bullet_arr.size(); r++) {
                   BulletObject *p_bullet = bullet_arr.at(r);
                   if (p_bullet != nullptr) {
                       for (int t = 0; t < threats_list.size(); t++) {
                           // lấy ra danh sách quái
                           ThreatsObject *obj_threat = threats_list.at(t);
                           if (obj_threat != nullptr) {
                               SDL_Rect tRect;
                               tRect.x = obj_threat->GetRect().x;
                               tRect.y = obj_threat->GetRect().y;
                               tRect.w = obj_threat->get_width_frame();
                               tRect.h = obj_threat->get_height_frame_();


                               SDL_Rect bRect = p_bullet->GetRect();
                               bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                               if (bCol) {
// hiển thị vụ no
                                   mark_value++;// cộng điểm
                                   // tạo hiệu ứng vụ nổ
                                   for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {


                                       int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                                       int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;


                                       exp_threat.set_frame(ex);
                                       exp_threat.SetRect(x_pos, y_pos);
                                       exp_threat.Show(g_screen);
                                   }
                                   Mix_PlayChannel(-1, g_sound_exp[0], 0);
                                   p_player.RemoveBullet(r);
                                   obj_threat->Free();
                                   threats_list.erase(threats_list.begin() + t);
                               }
                           }
                       }
                   }
               }
// hien thi thoi gian game
               std::string s_time = "Time: ";
               Uint32 time_val = SDL_GetTicks() / 1000;
               Uint32 val_time = 300 - time_val;
               if (val_time <= 0) {
                   if (MessageBox(nullptr, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK) {
                       return 0;
                   }
               } else {
                   std::string s_val = std::to_string(val_time);
                   s_time += s_val;
                   time_game.SetText(s_time);
                   time_game.LoadFromRenderText(font_time, g_screen);
                   time_game.RenderText(g_screen, SCREEEN_WIDTH - 200, 15);
               }


//hien thi diem so
               std::string a = "Point: ";
               std::string b = std::to_string(mark_value);
               a += b;
               mark_game.SetText(a);
               mark_game.LoadFromRenderText(font_time, g_screen);
               mark_game.RenderText(g_screen, SCREEEN_WIDTH * 0.5, 15);


               int coin_value = p_player.GetCountCoin();
               std::string str_coin = std::to_string(coin_value);
               std::string coin_ = "Coin: ";
               coin_ += str_coin;
               coin.SetText(coin_);
               coin.LoadFromRenderText(font_time, g_screen);
               coin.RenderText(g_screen, SCREEEN_WIDTH * 0.5 - 250, 15);




// hiển thị các đối tượng lên màn hình và điều chỉnh tốc độ khung hình
               SDL_RenderPresent(g_screen);


               int real_imp_time = fps_timer.get_ticks();
               int time_one_frame = 1000 / PRAME_PER_SECOND;


               if (real_imp_time < time_one_frame) {
                   int delay_time = time_one_frame - real_imp_time;
                   if (delay_time >= 0) {
                       SDL_Delay(delay_time);
                   }
               }
               if (p_player.GetCountCoin() >= 50 && mark_value >= 40) {
                   Mix_HaltMusic();
                   if (Music_On && Mix_PlayingMusic() == 0) Mix_PlayMusic(victory_music,0);
                   win = true;
                   state = 4;
                   SDL_Surface* sshot = SDL_CreateRGBSurface(0, SCREEEN_WIDTH, SCREEN_HEIGHT,32,0,0,0,0);
                   SDL_RenderReadPixels(g_screen,NULL,sshot->format->format,sshot->pixels,sshot->pitch);
                   IMG_SavePNG(sshot,"screenshot.png");
                   SDL_FreeSurface(sshot);
                   back_bg.LoadImg("screenshot.png",g_screen);
               }
           }
           else{
               MenuGame();
           }

}

    Game.CleanUp();
    for(auto p_threat : threats_list){
        if(p_threat){
            p_threat->Free();

        }
    }
    threats_list.clear();
    close();
    return 0;
}


