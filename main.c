#include <stdlib.h>
#include <pthread.h>


#include "SDL.h"
#include "game.h"




const int TARGET_FPS = 60;
const int DELAY_TIME = 1000 / TARGET_FPS;


int main() {



    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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

    pthread_t thread;

     if (pthread_create(&thread, NULL, spawnApplesThread, (void*)game) != 0) {

        fprintf(stderr, "Error creating thread\n");
        return 1;
    }


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

    pthread_join(thread, NULL);

    cleanupGame(game);
    SDL_Quit();
}
