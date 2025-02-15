#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_test_font.h>
#include <vector>
#include <math.h>

const Uint16   WIDTH = 500 ,HEIGHT = 500;
const Uint16   WORM_LENGTH=100;
const bool  BORDERS=false;
uint32_t    timer = 0;

using namespace std;

int main( int argc, char *argv[] )
{

    SDL_Window      *window=NULL, *window2=NULL, *window3;
    SDL_Renderer    *renderer=NULL;
    int             res = SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );

    if (res<0){ SDL_Log("sdl_init error!");}

    window = SDL_CreateWindow( "SDL PROGRAM.", WIDTH, HEIGHT, 0 );
    //window2 =SDL_CreateWindow( "SDL 2 ", WIDTH, HEIGHT, 0);
    //window3 =SDL_CreateWindow( "SDL 3 ", WIDTH, HEIGHT, 0);


    renderer = SDL_CreateRenderer(window, NULL);

    Uint8               nor_speed=2;
    Uint8               max_speed=5;
    Uint8               speed=nor_speed;

    SDL_FRect           rect;
    rect.h=20;
    rect.w=20;
    rect.x=0;
    rect.y=0;

    SDL_FRect           sqar;
    sqar.h=100;
    sqar.w=100;

    vector<SDL_FRect>   trail(WORM_LENGTH);

    SDL_Event           event;
    Uint8                 quit = 0;

    vector<vector<float>> crds_arr(WORM_LENGTH, vector<float>(2, 0.0f));

    for (int i=0;i<WORM_LENGTH;i++) {trail[i]=rect; trail[i].h=rect.h/2; trail[i].w=rect.w/2;}

    while (!quit){
        while (SDL_PollEvent(&event)){
            switch (event.type){

                case SDL_EVENT_KEY_DOWN :
                    if (event.key.key== SDLK_LSHIFT) speed=max_speed; break;
                
                case SDL_EVENT_KEY_UP :
                    if (event.key.key== SDLK_LSHIFT) speed=nor_speed; break;

                case SDL_EVENT_QUIT :
                    SDL_Log("SDL 3 QUIT");
                    quit = 1;
                    break;
            }
        }

        // MOVE OBJECT

        const bool* state = SDL_GetKeyboardState(NULL);

        sqar.x=WIDTH/2 - sqar.w/2;
        sqar.y=HEIGHT/2- sqar.h/2;
        

        for (int i=WORM_LENGTH-1;i>0;i--){
            crds_arr[i]=crds_arr[i-1];
        }
        crds_arr[0]={rect.x, rect.y};

        if (state[79]) rect.x+=speed; // 79 is for the RIGHT arrow
        if (state[80]) rect.x-=speed; // 80 is for the LEFT arrow
        if (state[81]) rect.y+=speed; // 81 is for the DOWN arrow
        if (state[82]) rect.y-=speed; // 82 is for the UP  arrow

        // BOUNDS

        if (!BORDERS){
            if (rect.x+rect.w > WIDTH)          rect.x=0;
            if (rect.x<0)                       rect.x=WIDTH-rect.w;
            if (rect.y+rect.h > HEIGHT)         rect.y=0;
            if (rect.y<0)                       rect.y=HEIGHT-rect.h;
        } else {
            if (rect.x+rect.w > WIDTH)          rect.x=WIDTH-rect.w;
            if (rect.x<0)                       rect.x=0;
            if (rect.y+rect.h > HEIGHT)         rect.y=HEIGHT-rect.h;
            if (rect.y<0)                       rect.y=0;
        }

        // SET BACKGROUND

        SDL_SetRenderDrawColor(renderer, 45, 40, 50, 0xff);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(renderer, &sqar);

        // RENDER OTHER OBJECTS

        for (int i=0;i<WORM_LENGTH;i++) {
            trail[i].x=crds_arr[i][0]+rect.w/4;
            trail[i].y=crds_arr[i][1]+rect.h/4;

            SDL_SetRenderDrawColor(renderer, 50, 50, 255 - float(i)*(255/float(WORM_LENGTH)), 255);
            SDL_RenderFillRect(renderer, &trail[i]);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(1);

        timer++;
    }

    SDL_Log("SDL3 shutdown");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    
    return EXIT_SUCCESS;
}