#include "player.h"

int PLAYER_POINTS = 0;

void playerInit(Player *player) {
    player->isMoving = false;

    player->velocity.x = 0;
    player->velocity.y = 0;

    player->head.x = 100;
    player->head.y = 100;

    player->head.w = 20;
    player->head.h = 20;

    player->speed = 2;

    //Add head to segments array
    player->segments[0] = player->head;
    player->segmentCount = 1;

}


void renderPlayer(Player *player, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0xFF);
    SDL_RenderFillRect(renderer, &player->head);

    for (int i = 1; i < player->segmentCount; ++i) {
        SDL_RenderFillRect(renderer, &player->segments[i]);
    }
}

void updatePlayer(Player *player) {
    if (player->isMoving) {


        //Move the segments
        for (int i = player->segmentCount - 1; i > 0; --i) {
            player->segments[i] = player->segments[i - 1];
        }

        //Move the head
        player->head.y += player->velocity.y * player->speed;
        player->head.x += player->velocity.x * player->speed;

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
        player->segments[0] = player->head;
    }
}

void stopPlayer(Player *player) {
    player->isMoving = false;
    player->velocity.x = 0;
    player->velocity.y = 0;
}

void initSegment(SDL_Rect * segment,SDL_Rect * head){
    segment->x = head->x;
    segment->y = head->y;
    segment->w = head->w;
    segment->h = head->h;

}

