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
                printf("North\n");
                game->player->isMoving = true;
                game->player->direction = North;
                break;
            case SDLK_s:
                printf("South\n");
                game->player->isMoving = true;
                game->player->direction = South;
                break;
            case SDLK_a:
                printf("West\n");
                game->player->isMoving = true;
                game->player->direction = West;
                break;
            case SDLK_d:
                printf("East\n");
                game->player->isMoving = true;
                game->player->direction = East;
                break;
        }
    }
}

void updateGame(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0xFF);
    updatePlayer(game->player);
    checkPlayerCollision(game);
}

void renderGame(Game *game) {

    SDL_RenderClear(game->renderer);
    renderPlayer(game->player, game->renderer);
    SDL_RenderPresent(game->renderer);
}

void checkPlayerCollision(Game *game) {
    if (game->player->player.x < 0 || game->player->player.x > SCREEN_WIDTH ||
        game->player->player.y < 0 || game->player->player.y > SCREEN_HEIGHT) {
        //game->isRunning = false;
        stopPlayer(game->player);
        printf("Player hit the wall\n");
    }
}