#include <iostream>
#include <SDL3/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main( int argc, char *argv[] )
{
    int res = SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );

    if (res<0){
        SDL_Log("sdl_init error!");
    }

    SDL_Window *window = SDL_CreateWindow( "Hello SDL World", WIDTH, HEIGHT, 0 );
    if (window==NULL){
        SDL_Log("error with window %s", SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    SDL_Event event;
    int quit = 0;
    while (!quit){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_EVENT_QUIT :
                    SDL_Log("SDL 3 QUIT");
                    quit =1;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_Log("SDL3 shutdown");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    
    return EXIT_SUCCESS;
}