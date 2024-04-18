#include"include.h"
#include"TextObject.h"
#include"BaseObject.h"
#include"Dot.h"

bool OnInit();
void close();
bool LoadMedia();
void TimeCounter();
void titleScreen();
void Settings();

bool ret = OnInit();

TTF_Font* font40 = TTF_OpenFont("imageSDL/font.ttf",40);
TTF_Font* titlefont = TTF_OpenFont("imageSDL/FzLongBeach.ttf",150);
TTF_Font* g_font_setting = TTF_OpenFont("imageSDL/SSWB.ttf",40);
Mix_Music* menu_music = Mix_LoadMUS("imageSDL/menu_music.mp3");
Mix_Chunk* select_menu_effect = Mix_LoadWAV("imageSDL/selected_sound_effects.mp3");
Mix_Chunk* start_effect = Mix_LoadWAV("imageSDL/interface-124464.mp3");
Mix_Chunk* tick_effect = Mix_LoadWAV("imageSDL/medium.wav");

#define MenuOption 3

BaseObject gBackground, SettingPanel;
TextObject SettingChoice[5];
TextObject TitleGame, TitleChoice[MenuOption];

bool IsRunning = true;
bool Music_On = true;
bool Sound_On = true;
SDL_Event e;
int scrolling = 0;
int state = 0; //0: title screen, 1: in game, 2: Settings, 3: end;
int selectedMenu = 0;

int main(int argc, char* argv[])
{
    if (LoadMedia())
    {
        while (IsRunning)
        {
            switch (state)
            {
            case 0: titleScreen(); break;
            case 1:
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                gBackground.SetRect(0,0);
                gBackground.Render(gRenderer);
                while (SDL_PollEvent(&e) > 0) {
                    if (e.type == SDL_QUIT)
                        IsRunning = false;
                }
                SDL_RenderPresent(gRenderer);
                break;
            case 2: Settings(); break;
            case 3: IsRunning = false; break;
            }
        }
    }
    close();
    return 0;
}

bool LoadMedia()
{
    TitleGame.SetText("Contra");
    TitleChoice[0].SetText("     Start    ");
    TitleChoice[1].SetText("    Setting   ");
    TitleChoice[2].SetText("     Quit     ");
    TitleGame.SetColor(TextObject::ORANGE_TEXT);
    TitleGame.LoadFromRenderText(titlefont,gRenderer);

    SettingChoice[0].SetText("Music");
    SettingChoice[1].SetText("Sound");
    SettingChoice[2].SetText("Back");

    gBackground.LoadImg("imageSDL/background.png",gRenderer);
    SettingPanel.LoadImg("imageSDL/settings.png",gRenderer);
    for (int i=3; i<5; ++i) {
        SettingChoice[i].LoadImg("imageSDL/boxX.png",gRenderer);
    }

    SettingPanel.SetRect(193,72);
    SettingChoice[0].SetRect(430,418);
    SettingChoice[1].SetRect(650,418);
    SettingChoice[2].SetRect(582,568);
    SettingChoice[3].SetRect(570,398);
    SettingChoice[4].SetRect(800,398);

    return true;
}

bool OnInit()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING)<0) {
        printf("Could not initialize SDL! %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Learning", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Failed to create Window! %s\n", SDL_GetError());
            success = false;
        } else{
            gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL){
                printf("Failed to create Renderer! %s\n", SDL_GetError());
            }
            else {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear(gRenderer);

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
                }
				if (TTF_Init() == -1) {
                    success = false;
                    printf("Failed to initialize SDL TTF!\n");
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1048) < 0)
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

/*void TimeCounter()
{
    string str_time = "Time: ";
    Uint32 time_val = SDL_GetTicks()/1000;
    string str_val = to_string(time_val);
    str_time += str_val;
    time_game_.SetText(str_time);
    time_game_.LoadFromRenderText(font40,gRenderer);
} */

void titleScreen()
{
    if (Music_On && Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(menu_music,-1);
    }

    --scrolling;
    if (scrolling < -gBackground.GetRect().w) scrolling = 0;

    gBackground.SetRect(scrolling,0);
    gBackground.Render(gRenderer);
    gBackground.SetRect(scrolling+gBackground.GetRect().w,0);
    gBackground.Render(gRenderer);


    TitleGame.LoadFromRenderText(titlefont,gRenderer);
    for (int i=0 ; i<MenuOption; ++i) {
        if (i == selectedMenu)
        {
            TitleChoice[i].LoadFromRenderTextShaded(font40,gRenderer);
        }
        else
        {
            TitleChoice[i].LoadFromRenderText(font40, gRenderer);
        }
    }
    TitleGame.RenderText(gRenderer,(SCREEN_WIDTH-TitleGame.GetRect().w)/2,50);

    int height = 70 + TitleGame.GetRect().h;
    for (int i=0; i<MenuOption; ++i)
    {
        TitleChoice[i].RenderText(gRenderer,(SCREEN_WIDTH-TitleChoice[i].GetRect().w)/2,height);
        height += TitleChoice[i].GetRect().h;
    }
    SDL_RenderPresent(gRenderer);

    while (SDL_PollEvent(&e) > 0)
    {
        if (e.type == SDL_QUIT) IsRunning = false;
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
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
                    Mix_PlayChannel(-1,start_effect,0);
                }
                SDL_Delay(500);
                switch (selectedMenu)
                {
                case 0: state = 1; break;
                case 1: state = 2; break;
                case 2: state = 3; break;
                }
                break;
            }
        }
    }
}

void titleScreen2()
{
    int xm = 0, ym = 0;
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(menu_music,0);
    }
    while (SDL_PollEvent(&e) > 0)
    {
        switch (e.type)
        {
            case SDL_QUIT: IsRunning = false; break;
            case SDL_MOUSEMOTION:
                xm = e.motion.x;
                ym = e.motion.y;
                for (int i=0; i<MenuOption; ++i)
                {
                    if (TitleChoice[i].CheckFocus(xm,ym))
                    {
                        if (selectedMenu != i) {
                            selectedMenu = i;
                            Mix_PlayChannel(-1,select_menu_effect,0);
                        }
                        TitleChoice[i].LoadFromRenderTextShaded(font40,gRenderer);
                    }
                    else {
                        TitleChoice[i].LoadFromRenderText(font40,gRenderer);
                    }
                }
                break;
        }
    }
}

void Settings()
{
    int xm = 0, ym = 0;

    while (SDL_PollEvent(&e) > 0) {
        switch (e.type)
        {
            case SDL_QUIT: IsRunning = false; break;
            case SDL_MOUSEMOTION:
                xm = e.motion.x; ym = e.motion.y;
                if (SettingChoice[2].CheckFocus(xm,ym)) {
                    SettingChoice[2].SetColor(TextObject::RED_TEXT);
                    if (Sound_On) {
                        Mix_PlayChannel(-1,select_menu_effect,0);
                    }
                } else SettingChoice[2].SetColor(TextObject::BLACK_TEXT);
                break;
            case SDL_MOUSEBUTTONDOWN:
                xm = e.button.x; ym = e.button.y;
                for (int i=2; i<=4; ++i)
                {
                    if (SettingChoice[i].CheckFocus(xm,ym)) {
                        switch (i)
                        {
                            case 2: state = 0; break;
                            case 3:
                                if (Music_On) {
                                    Music_On = false;
                                    SettingChoice[3].LoadImg("imageSDL/box.png",gRenderer);
                                    Mix_PauseMusic();
                                }
                                else {
                                    Music_On = true;
                                    SettingChoice[3].LoadImg("imageSDL/boxX.png",gRenderer);
                                    Mix_ResumeMusic();
                                }
                                break;
                            case 4:
                                if (Sound_On) {
                                    Sound_On = false;
                                    SettingChoice[4].LoadImg("imageSDL/box.png",gRenderer);
                                }
                                else {
                                    Sound_On = true;
                                    SettingChoice[4].LoadImg("imageSDL/boxX.png",gRenderer);
                                }
                                break;
                        }
                        if (Sound_On) Mix_PlayChannel(-1, tick_effect, 0);
                    }
                }
        }
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    for (int i=0; i<3; ++i) {
        SettingChoice[i].LoadFromRenderText(g_font_setting,gRenderer);
    }

    gBackground.SetRect(0,0);
    gBackground.Render(gRenderer);
    SettingPanel.Render(gRenderer);
    for (int i=0; i<5; ++i)
    {
        SettingChoice[i].Render(gRenderer);
    }
    SDL_RenderPresent(gRenderer);
}

void close()
{
	Mix_FreeChunk(select_menu_effect);
	Mix_FreeMusic(menu_music);
	Mix_FreeChunk(start_effect);
	Mix_FreeChunk(tick_effect);

	TTF_CloseFont(font40);
	TTF_CloseFont(titlefont);
	TTF_CloseFont(g_font_setting);

    TitleGame.free();
    for (int i=0; i<MenuOption; ++i) TitleChoice[i].free();
    gBackground.free();
    SettingPanel.free();
    for (int i=0; i<5; ++i) SettingChoice[i].free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
