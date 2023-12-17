#include "game.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 640;

int initializeGame(Game *game) {
    game->window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!game->window) {
        printf("Window could not be created!\n");
        printf("SDL_ERROR: %s\n", SDL_GetError());
        return 1;
    } else {
        game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
        if (!game->renderer) {
            printf("Renderer could not be created!\n");
            printf("SDL_Error: %s\n", SDL_GetError());
            return 1;
        } else {
            game->isRunning = true;
            game->player = malloc(sizeof(Player));
            playerInit(game->player);
        }
    }
    return 0;
}

void cleanupGame(Game *game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    free(game->player);
    free(game);
}

void handleGameEvents(Game *game, SDL_Event e) {
    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                game->player->direction = North;
                break;
            case SDLK_s:
                game->player->direction = South;
                break;
            case SDLK_a:
                game->player->direction = West;
                break;
            case SDLK_d:
                game->player->direction = East;
                break;
        }
    }
}

void updateGame(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0xFF);

    updatePlayer(game->player);
}

void renderGame(Game *game) {

    SDL_RenderClear(game->renderer);
    renderPlayer(game->player, game->renderer);
    SDL_RenderPresent(game->renderer);
}