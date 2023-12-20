
#include "game.h"

#ifdef _WIN32
#include <Windows.h>
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 640;
int APPLE_COUNTER = 0;


bool rectOverlap(SDL_Rect *rect, SDL_Rect *rect2) {
    bool overlap = false;

    if (rect->x < rect2->x + rect2->w &&
        rect->x + rect->w > rect2->x &&
        rect->y < rect2->y + rect2->h &&
        rect->y + rect->h > rect2->y) {
        overlap = true;
    }


    return overlap;
}

void spawnApple(Apple *apple) {
    srand((unsigned int) time(NULL));
    int x, y;


    x = rand() % (SCREEN_WIDTH / 20);
    y = rand() % (SCREEN_HEIGHT / 20);

    x = x > 800 ? 800 : x;
    y = y > 640 ? 640 : y;

    apple->apple.x = x * 20;
    apple->apple.y = y * 20;

    apple->apple.w = 20;
    apple->apple.h = 20;

}

void *spawnApplesThread(void *arg) {
    Game *game = (Game *) arg;

    while (game->isRunning) {
        if (APPLE_COUNTER < 10) {
            spawnApple(&game->apples[APPLE_COUNTER]);

            for (int i = 0; i < APPLE_COUNTER; ++i) {
                if (rectOverlap(&game->apples[APPLE_COUNTER].apple, &game->apples[i].apple)) {
                    APPLE_COUNTER--;
                    break;
                }
            }


            APPLE_COUNTER++;
            usleep(2000000); // 2seconds
        }
    }
    return NULL;
}

//Render
void renderApple(Apple *apple, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
    SDL_RenderFillRect(renderer, &apple->apple);
}

void renderApples(Game *game) {
    for (int i = 0; i < APPLE_COUNTER; ++i) {
        renderApple((Apple *) &game->apples[i], game->renderer);
    }
}

void renderGame(Game *game) {
    SDL_RenderClear(game->renderer);
    renderApples(game);
    renderPlayer(game->player, game->renderer);

    SDL_RenderPresent(game->renderer);
}

//Game Util
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
            case SDLK_ESCAPE :
                CLEAR_SCREEN;
                printf("Leaving the game you gathered %d points!\n", PLAYER_POINTS);
                game->isRunning = false;
                break;
            case SDLK_w:
                game->player->isMoving = true;
                 if (game->player->direction != South) {
                     game->player->direction = North;
                 }
                break;
            case SDLK_s:
                 game->player->isMoving = true;
                 if (game->player->direction != North) {
                     game->player->direction = South;
                 }
                break;
            case SDLK_a:
                game->player->isMoving = true;
                 if (game->player->direction != East) {
                     game->player->direction = West;
                 }
                break;
            case SDLK_d:
                game->player->isMoving = true;
                 if (game->player->direction != West) {
                     game->player->direction = East;
                 }
                break;
        }
    }
}

void updateGame(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0xFF);
    updatePlayer(game->player);
    checkPlayerCollision(game);

}

void checkPlayerCollision(Game *game) {
    if (game->player->head.x < 0 || game->player->head.x > SCREEN_WIDTH ||
        game->player->head.y < 0 || game->player->head.y > SCREEN_HEIGHT) {
        game->isRunning = false;
        printf("Player hit the wall\n");
    }

    for (int i = 0; i < APPLE_COUNTER; ++i) {
        if (rectOverlap(&game->player->head, &game->apples[i].apple)) {
            PLAYER_POINTS++;
            CLEAR_SCREEN;
            printf("Points: %d\n", PLAYER_POINTS);


            if (game->player->segmentCount < MAX_SEGMENTS) {
                SDL_Rect *newSegment = malloc(sizeof(SDL_Rect));
                initSegment(newSegment, &game->player->head);


                game->player->segments[game->player->segmentCount] = *newSegment;
                game->player->segmentCount++;
                game->player->speed += 0.3;
                free(newSegment);
            }


            for (int j = i; j < APPLE_COUNTER - 1; ++j) {
                game->apples[j] = game->apples[j + 1];
            }
            APPLE_COUNTER--;
        }
    }
}








