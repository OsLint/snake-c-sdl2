#include <stdbool.h>

#include "SDL.h"
#include "player.h"


extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;



typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int playerScore;
    bool isRunning;
    Player * player;
    int gameBoard [];

} Game;

int initializeGame(Game *game);
void cleanupGame(Game *game);
void handleGameEvents(Game *game, SDL_Event e);
void updateGame(Game * game);
void renderGame(Game * game);