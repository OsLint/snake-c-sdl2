#include <stdbool.h>
#include "SDL.h"

enum Direction {
    North,
    West,
    East,
    South
};

typedef struct {
    SDL_Rect player;
    SDL_Point velocity;
    int speed;
    enum Direction direction;
    bool isMoving;

}Player;

void playerInit(Player * player);
void renderPlayer(Player * player, SDL_Renderer *renderer);
void updatePlayer(Player * player);
void stopPlayer(Player * player);