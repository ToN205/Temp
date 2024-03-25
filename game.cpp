#include"BaseObject.h"
#include"mainObject.h"
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

//Khoi tao ham
bool OnInit();
void close();

//Khai bao bien
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

int main(int argc, char* argv[])
{
    bool Running = true;
    if (OnInit())
    {
        GTexture gBackground(gRenderer);
        MainCharacter player(gRenderer);
        if (gBackground.loadImage("game_img/bg2.png") && player.loadImage("game_img/human64x91.png"))
        {
            gBackground.render(0,0);
            SDL_RenderPresent(gRenderer);
            SDL_Event event;
            while (Running)
            {
                player.displayImage();
                while (SDL_PollEvent(&event)>0) {
                    if (event.type == SDL_QUIT)
                        Running = false;
                    //player.handleInputAction(event);
                }
                //player.handleMove();
            }
        }
        gBackground.free();
        player.free();
    }
    close();
    return 0;
}

bool OnInit()
{
    bool flag = false;
    if (SDL_Init(SDL_INIT_EVERYTHING)<0) {
        printf("Could not initialize SDL! %s\n", SDL_GetError());
    } else {
        gWindow = SDL_CreateWindow("SDL Learning", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Failed to create Window! %s\n", SDL_GetError());
        } else{
            gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL){
                printf("Failed to create Renderer! %s\n", SDL_GetError());
            }
            else {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				else flag = true;
            }
        }
    }
    return flag;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}
