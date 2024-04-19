#include"StartMenu.h"

gameSDL::gameSDL(TTF_Font* fontA, TTF_Font* fontB, TTF_Font* fontC,
                 Mix_Chunk* sfx1, Mix_Chunk* sfx2, Mix_Chunk* sfx3, Mix_Music* music)
{
    title_font = fontA;
    menu_font = fontB;
    setting_font = fontC;

    select_menu_effect = sfx1;
    choose_effect = sfx2;
    tick_effect = sfx3;
    g_music = music;

    for (int i=0; i<2; ++i)
        selectedItem[i] = false;
}

bool gameSDL::LoadMedia(SDL_Renderer* des)
{
    TitleGame.SetText("Mission Impossible");
    TitleChoice[0].SetText("     Start    ");
    TitleChoice[1].SetText("    Setting   ");
    TitleChoice[2].SetText("     Quit     ");
    TitleGame.SetColor(TextObject::ORANGE_TEXT);
    TitleGame.LoadFromRenderText(title_font,des);

    SettingChoice[0].SetText("Music");
    SettingChoice[1].SetText("Sound");
    SettingChoice[2].SetText("Back");

    gBackground.LoadImg("imageSDL/background.png",des);
    SettingPanel.LoadImg("imageSDL/settings.png",des);
    for (int i=3; i<5; ++i) {
        SettingChoice[i].LoadImg("imageSDL/boxX.png",des);
    }

    SettingPanel.SetRect(193,72);
    SettingChoice[0].SetRect(430,418);
    SettingChoice[1].SetRect(650,418);
    SettingChoice[2].SetRect(582,568);
    SettingChoice[3].SetRect(570,398);
    SettingChoice[4].SetRect(800,398);

    black_bg.LoadImg("imageSDL/black_bg.png",des);
    black_bg.setBlendMode(SDL_BLENDMODE_BLEND);
    black_bg.setAlpha(150);

    EndingChoice[0].SetText("Play Again");
    EndingChoice[1].SetText("Menu");
    EndingChoice[0].SetRect(400,418);
    EndingChoice[1].SetRect(700,418);
    for (int i=0; i<2; ++i)
        EndingChoice[i].SetColor(TextObject::WHITE_TEXT);
    Results.SetColor(TextObject::YELLOW_TEXT);

    return true;
}

int gameSDL::titleScreen(SDL_Renderer* des)
{
    if (Music_On && Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(g_music,-1);
    }

    --scrolling;
    if (scrolling < -gBackground.GetRect().w) scrolling = 0;

    gBackground.SetRect(scrolling,0);
    gBackground.Render(des);
    gBackground.SetRect(scrolling+gBackground.GetRect().w,0);
    gBackground.Render(des);

    while (SDL_PollEvent(&g_event) > 0)
    {
        if (g_event.type == SDL_QUIT) return 3;
        else if (g_event.type == SDL_KEYDOWN) {
            switch (g_event.key.keysym.sym)
            {
                case SDLK_UP:
                    if (Sound_On) {
                        Mix_PlayChannel(-1,select_menu_effect,0);
                    }
                    TitleChoice[selectedMenu].SetColor(TextObject::BLACK_TEXT);
                    selectedMenu--;
                    if (selectedMenu < 0) selectedMenu = MenuOption-1;
                    TitleChoice[selectedMenu].SetColor(TextObject::WHITE_TEXT);
                    break;
                case SDLK_DOWN:
                    if (Sound_On) {
                        Mix_PlayChannel(-1, select_menu_effect,0);
                    }
                    TitleChoice[selectedMenu].SetColor(TextObject::BLACK_TEXT);
                    selectedMenu++;
                    if (selectedMenu == MenuOption) selectedMenu = 0;
                    TitleChoice[selectedMenu].SetColor(TextObject::WHITE_TEXT);
                    break;
                case SDLK_RETURN:
                    if (Sound_On) {
                        Mix_PlayChannel(-1,choose_effect,0);
                    }
                    SDL_Delay(500);
                    switch (selectedMenu)
                    {
                        case 0: return 1; break;
                        case 1: return 2; break;
                        case 2: return 3; break;
                    }
                    break;
            }
        }
    }

    TitleGame.LoadFromRenderText(title_font,des);
    for (int i=0 ; i<MenuOption; ++i) {
        if (i == selectedMenu)
        {
            TitleChoice[i].LoadFromRenderTextShaded(menu_font,des);
        }
        else
        {
            TitleChoice[i].LoadFromRenderText(menu_font, des);
        }
    }
    TitleGame.RenderText(des,(SCREEEN_WIDTH-TitleGame.GetRect().w)/2,50);

    int height = 70 + TitleGame.GetRect().h;
    for (int i=0; i<MenuOption; ++i)
    {
        TitleChoice[i].RenderText(des,(SCREEEN_WIDTH-TitleChoice[i].GetRect().w)/2,height);
        height += TitleChoice[i].GetRect().h;
    }
    SDL_RenderPresent(des);


    return 0;
}

int gameSDL::Settings(SDL_Renderer* des)
{
    int xm = 0, ym = 0;

    while (SDL_PollEvent(&g_event) > 0) {
        switch (g_event.type)
        {
            case SDL_QUIT: return 3; break;
            case SDL_MOUSEMOTION:
                xm = g_event.motion.x; ym = g_event.motion.y;
                if (SettingChoice[2].CheckFocus(xm,ym)) {
                    SettingChoice[2].SetColor(TextObject::RED_TEXT);
                    if (Sound_On) {
                        Mix_PlayChannel(-1,select_menu_effect,0);
                    }
                } else SettingChoice[2].SetColor(TextObject::BLACK_TEXT);
                break;
            case SDL_MOUSEBUTTONDOWN:
                xm = g_event.button.x; ym = g_event.button.y;
                for (int i=2; i<=4; ++i)
                {
                    if (SettingChoice[i].CheckFocus(xm,ym)) {
                        switch (i)
                        {
                            case 2: return 0; break;
                            case 3:
                                if (Music_On) {
                                    Music_On = false;
                                    SettingChoice[3].LoadImg("imageSDL/box.png",des);
                                    Mix_PauseMusic();
                                }
                                else {
                                    Music_On = true;
                                    SettingChoice[3].LoadImg("imageSDL/boxX.png",des);
                                    Mix_ResumeMusic();
                                }
                                break;
                            case 4:
                                if (Sound_On) {
                                    Sound_On = false;
                                    SettingChoice[4].LoadImg("imageSDL/box.png",des);
                                }
                                else {
                                    Sound_On = true;
                                    SettingChoice[4].LoadImg("imageSDL/boxX.png",des);
                                }
                                break;
                        }
                        if (Sound_On) Mix_PlayChannel(-1, tick_effect, 0);
                    }
                }
        }
    }

    for (int i=0; i<3; ++i) {
        SettingChoice[i].LoadFromRenderText(setting_font,des);
    }

    SettingPanel.Render(des);
    for (int i=0; i<5; ++i)
    {
        SettingChoice[i].Render(des);
    }
    SDL_RenderPresent(des);
    return 2;
}

int gameSDL::End_Message(SDL_Renderer* des, const std::string& str, TTF_Font* font)
{
    Results.SetText(str);
    Results.LoadFromRenderText(font, des);
    alpha += 5;
    if (alpha > 255) alpha = 255;
    Results.setAlpha(alpha);

    black_bg.Render(des);
    Results.RenderText(des, (SCREEEN_WIDTH-Results.GetRect().w)/2,50);

    if (alpha < 255) {
        SDL_RenderPresent(des);
        return 4;
    }

    int xm = 0, ym = 0;
    while (SDL_PollEvent(&g_event) > 0)
    {
        switch (g_event.type)
        {
            case SDL_QUIT: return 4; break;
            case SDL_MOUSEMOTION:
                xm = g_event.motion.x; ym = g_event.motion.y;
                for (int i = 0; i < 2; ++i)
                {
                    if (EndingChoice[i].CheckFocus(xm,ym))
                    {
                        if (Sound_On && !selectedItem[i])
                            Mix_PlayChannel(-1,select_menu_effect,0);
                        selectedItem[i] = true;
                    }
                    else selectedItem[i] = false;
                }
                for (int i=0; i<2; ++i)
                {
                    if (selectedItem[i]) EndingChoice[i].SetColor(TextObject::RED_TEXT);
                    else EndingChoice[i].SetColor(TextObject::BLACK_TEXT);

                    EndingChoice[i].LoadFromRenderText(setting_font,des);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                xm = g_event.button.x; ym = g_event.button.y;
                if (Sound_On) Mix_PlayChannel(-1,choose_effect,0);
                for (int i=0; i<2; ++i)
                {
                    if (EndingChoice[i].CheckFocus(xm,ym))
                    {
                        for (int i=0; i<2; ++i) selectedItem[i] = false;
                        switch(i)
                        {
                            case 0: return 1; break;
                            case 1: return 0; break;
                        }
                    }
                }
        }
    }

    for (int i=0; i<2; ++i)
        EndingChoice[i].Render(des);
    SDL_RenderPresent(des);
    return 4;
}


void gameSDL::CleanUp()
{
    TitleGame.Free();
    gBackground.Free();
    SettingPanel.Free();
    black_bg.Free();
    Results.Free();
    for (int i=0; i<MenuOption; ++i) TitleChoice[i].Free();
    for (int i=0; i<5; ++i) SettingChoice[i].Free();
    for (int i=0; i<2; ++i) EndingChoice[i].Free();

}