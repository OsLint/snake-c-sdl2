#include "player.h"


void playerInit(Player *player) {
    player->direction = North;

    player->velocity.x = 0;
    player->velocity.y = 0;

    player->player.x = 100;
    player->player.y = 100;

    player->player.w = 20;
    player->player.h = 20;

}

void move(Player *player,enum Direction direction) {
   player->isMoving = true;

}

void renderPlayer(Player *player, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0xFF);
    SDL_RenderFillRect(renderer, &player->player);
}

void updatePlayer(Player *player) {
   /* if(player->isMoving){
        player->player.y += player->velocity.y;
        player->player.x += player->velocity.x;

        if (player->player.y < 0) {
            player->player.y = 0;
        } else {
           // if (player->player.y + player->player.h > SCREEN_HEIGHT) {
          //      player->player.y = SCREEN_HEIGHT - player->player.h;
          //  }
        }
    } */
}
