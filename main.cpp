#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_test_font.h>
#include <string.h>

const int WIDTH = 1280, HEIGHT = 720;

int main( int argc, char *argv[] )
{

    SDL_Window      *window=NULL;
    SDL_Renderer    *renderer=NULL;
    int             res = SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );

    if (res<0){ SDL_Log("sdl_init error!");}

    window = SDL_CreateWindow( "SDL PROGRAM.", WIDTH, HEIGHT, 0 );
    renderer = SDL_CreateRenderer(window, NULL);

    SDL_FRect       rect;
    rect.h=50;
    rect.w=50;
    rect.x=0;
    rect.y=0;

    SDL_Event       event;
    int             quit = 0;

    while (!quit){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_EVENT_QUIT :
                    SDL_Log("SDL 3 QUIT");
                    quit = 1;
                    break;
            }
        }

        // SET BACKGROUND

        SDL_SetRenderDrawColor(renderer, 45, 40, 50, 0xff);
        SDL_RenderClear(renderer);

        // RENDER OTHER OBJECTS

        SDL_SetRenderDrawColor(renderer, 0, 50, 255, 50);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_Log("SDL3 shutdown");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    
    return EXIT_SUCCESS;
}