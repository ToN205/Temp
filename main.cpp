#include"include.h"
#include"TextObject.h"
#include"BaseObject.h"
#include"StartMenu.h"

bool OnInit();
void close();
void TimeCounter();

bool ret = OnInit();

TTF_Font* font40 = TTF_OpenFont("imageSDL/font.ttf",40);
TTF_Font* titlefont = TTF_OpenFont("imageSDL/FzLongBeach.ttf",150);
TTF_Font* g_font_setting = TTF_OpenFont("imageSDL/SSWB.ttf",40);
TTF_Font* g_over_font = TTF_OpenFont("imageSDL/game_over.ttf",200);
TTF_Font* victory_font = TTF_OpenFont("imageSDL/FzLongBeach.ttf",150);

Mix_Music* menu_music = Mix_LoadMUS("imageSDL/menu_music.mp3");
Mix_Music* victory_music = Mix_LoadMUS("imageSDL/sfx-victory1.mp3");
Mix_Chunk* select_menu_effect = Mix_LoadWAV("imageSDL/selected_sound_effects.mp3");
Mix_Chunk* start_effect = Mix_LoadWAV("imageSDL/interface-124464.mp3");
Mix_Chunk* tick_effect = Mix_LoadWAV("imageSDL/medium.wav");
Mix_Chunk* game_over = Mix_LoadWAV("imageSDL/game-over-31-179699.mp3");

gameSDL Game(titlefont, font40, g_font_setting,
             select_menu_effect, start_effect, tick_effect, menu_music);
bool rett = Game.LoadMedia(g_screen);
int state = 0; //0: title screen, 1: in game, 2: Settings, 3: result, 3: end;
BaseObject back_bg;
bool win;

int main(int argc, char* argv[])
{
    while (IsRunning)
    {
        switch (state)
        {
        case 0: state = Game.titleScreen(g_screen); break;
        case 1:
            while (SDL_PollEvent(&g_event) > 0)
            {
                switch(g_event.type)
                {
                    case SDL_QUIT: IsRunning = false;
                    case SDL_KEYDOWN:
                        SDL_Surface* sshot = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT,32,0,0,0,0);
                        SDL_RenderReadPixels(g_screen,NULL,sshot->format->format,sshot->pixels,sshot->pitch);
                        IMG_SavePNG(sshot,"screenshot.png");
                        SDL_FreeSurface(sshot);
                        back_bg.LoadImg("screenshot.png",g_screen);
                        state = 4;
                        if (g_event.key.keysym.sym == SDLK_SPACE) {
                            if (Music_On && Mix_PlayingMusic() == 0) Mix_PlayMusic(victory_music,0);
                            win = true;
                        }
                        if (g_event.key.keysym.sym == SDLK_RETURN) {
                            if (Sound_On) Mix_PlayChannel(-1,game_over,0);
                            win = false;
                        }

                }
            }
            break;
        case 2: state = Game.Settings(g_screen); break;
        case 4:
            back_bg.Render(g_screen);
            if (win) {
                state = Game.End_Message(g_screen,"Victory",victory_font);
            } else {
                state = Game.End_Message(g_screen,"Game Over",g_over_font);
            }
            break;
        case 3 : IsRunning = false; break;
        }

    }
    Game.CleanUp();
    close();
    return 0;
}

bool OnInit()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING)<0) {
        printf("Could not initialize SDL! %s\n", SDL_GetError());
        success = false;
    } else {
        g_window = SDL_CreateWindow("SDL Learning", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (g_window == NULL) {
            printf("Failed to create Window! %s\n", SDL_GetError());
            success = false;
        } else{
            g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if (g_screen == NULL){
                printf("Failed to create Renderer! %s\n", SDL_GetError());
            }

            SDL_SetRenderDrawColor( g_screen, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear(g_screen);

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
    return success;
}

/*void TimeCounter()
{
    string str_time = "Time: ";
    Uint32 time_val = SDL_GetTicks()/1000;
    string str_val = to_string(time_val);
    str_time += str_val;
    time_game_.SetText(str_time);
    time_game_.LoadFromRenderText(font40,g_screen);
} */

void close()
{
	Mix_FreeChunk(select_menu_effect);
	Mix_FreeMusic(menu_music);
	Mix_FreeChunk(start_effect);
	Mix_FreeChunk(tick_effect);
	Mix_FreeMusic(victory_music);
	Mix_FreeChunk(game_over);

	TTF_CloseFont(font40);
	TTF_CloseFont(titlefont);
	TTF_CloseFont(g_font_setting);
	TTF_CloseFont(g_over_font);
	TTF_CloseFont(victory_font);

	back_bg.free();

	SDL_DestroyRenderer( g_screen );
	SDL_DestroyWindow( g_window );
	g_window = NULL;
	g_screen = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
