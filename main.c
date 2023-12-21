#include <stdlib.h>

#include "SDL.h"
#include "game.h"




const int TARGET_FPS = 60;
const int DELAY_TIME = 1000 / TARGET_FPS;


int main() {



    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not be initialized!\n");
        printf("SDL_Error: %s\n", SDL_GetError());
        return 1;
    }



    Game * game = malloc(sizeof (Game));
    int gameInit = initializeGame(game);
    if(gameInit != 0){
        printf("Game could not be initialized!");
        return 1;
    }



    SDL_TimerID spawnApples = SDL_AddTimer(1000,  spawnApplesTimer, game);

    SDL_Event e;

    while (game->isRunning){
        Uint32 frameStart = SDL_GetTicks();

        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                game->isRunning = false;
            }
            handleGameEvents(game,e);
        }
        updateGame(game);
        renderGame(game);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < DELAY_TIME){
            SDL_Delay(DELAY_TIME - frameTime);
        }

    }

    //pthread_join(thread, NULL);
    SDL_RemoveTimer(spawnApples);
    cleanupGame(game);
    SDL_Quit();
}
