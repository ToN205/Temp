#ifndef STARTMENU_H_INCLUDED
#define STARTMENU_H_INCLUDED

#include"CommonFunc.h"
#include"BaseObject.h"
#include"TextObject.h"

#define MenuOption 3

class gameSDL
{
public:
    gameSDL(TTF_Font* fontA, TTF_Font* fontB, TTF_Font* fontC,
            Mix_Chunk* sfx1, Mix_Chunk* sfx2, Mix_Chunk* sfx3, Mix_Music* music);
    bool LoadMedia(SDL_Renderer* des);
    int titleScreen(SDL_Renderer* des);
    int Settings(SDL_Renderer* des);
    int End_Message(SDL_Renderer* des, const std::string& str, TTF_Font* font);
    void CleanUp();
private:
    int scrolling = 0;
    int selectedMenu = 0;
    Uint32 alpha = 0;

    TTF_Font* title_font, *menu_font, *setting_font;
    Mix_Chunk* select_menu_effect, *choose_effect, *tick_effect;
    Mix_Music* g_music;

    BaseObject gBackground, SettingPanel;
    TextObject SettingChoice[5];
    TextObject TitleGame, TitleChoice[MenuOption];

    BaseObject black_bg;
    TextObject Results;
    TextObject EndingChoice[2];

    bool selectedItem[2];
};

#endif // STARTMENU_H_INCLUDED