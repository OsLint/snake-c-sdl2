#include <stdbool.h>
#include "SDL.h"

extern int PLAYER_POINTS;

#define MAX_SEGMENTS 100

enum Direction {
    North,
    West,
    East,
    South
};


typedef struct {
    SDL_Rect head;
    SDL_Point velocity;
    double speed;
    enum Direction direction;
    bool isMoving;
    SDL_Rect segments[MAX_SEGMENTS];
    int segmentCount;
}Player;

void playerInit(Player * player);
void renderPlayer(Player * player, SDL_Renderer *renderer);
void updatePlayer(Player * player);
void initSegment(SDL_Rect * segment,SDL_Rect * head);
