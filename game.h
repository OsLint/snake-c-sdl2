#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "SDL.h"
#include "player.h"


extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int APPLE_COUNTER;
extern int PLAYER_POINTS;

typedef struct {
    SDL_Rect apple;
} Apple;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int playerScore;
    bool isRunning;
    Player *player;
    Apple apples[100];
} Game;

//Apple Generation
bool rectOverlap(SDL_Rect * rect, SDL_Rect * rect2);

void spawnApple(Apple *apple);

void *spawnApplesThread(void *arg);

//Render
void renderApple(Apple *apple, SDL_Renderer *renderer);

void renderApples(Game *game);

void renderGame(Game *game);

//Game Util
int initializeGame(Game *game);

void cleanupGame(Game *game);

void handleGameEvents(Game *game, SDL_Event e);

void updateGame(Game *game);

void checkPlayerCollision(Game *game);