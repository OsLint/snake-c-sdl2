#include "player.h"


void playerInit(Player *player) {
    player->isMoving = false;

    player->velocity.x = 0;
    player->velocity.y = 0;

    player->player.x = 100;
    player->player.y = 100;

    player->player.w = 20;
    player->player.h = 20;

    player->speed = 2;
}


void renderPlayer(Player *player, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0xFF);
    SDL_RenderFillRect(renderer, &player->player);
}

void updatePlayer(Player *player) {
    if(player->isMoving){
        player->player.y += player->velocity.y * player->speed;
        player->player.x += player->velocity.x * player->speed;
        enum Direction dir = player->direction;

        switch (dir) {
            case North:
                player->velocity.x = 0;
                player->velocity.y = -1;
                break;
            case West:
                player->velocity.x = -1;
                player->velocity.y = 0;
                break;
            case East:
                player->velocity.x = 1;
                player->velocity.y = 0;
                break;
            case South:
                player->velocity.x = 0;
                player->velocity.y = 1;
                break;
        }

    }
}

void stopPlayer(Player * player){
    player->isMoving = false;
}
