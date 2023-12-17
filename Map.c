
#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initMap(Map *map,int size){
    map->size = size;
    map->keys = (int **)malloc(size * sizeof (int *));
    map->values = (int *) malloc(size * sizeof (int));

    for (int i = 0; i < size; ++i) {
        map->keys[i] = NULL;
        map->values[i] = 0;
    }
}

int getIndexInMap(Map *map,int value)
{
    for (int i = 0; i < map->size; i++) {
        //if (strcmp(map->keys[i], key) == 0) {
          //  return i;
       // }
    }
    return -1; // Key not found
}

void insertToMap(Map *map,  int value){
    int index = getIndexInMap(map,value);
}

void getByKeyFromMap(const Map *map, const char key[]){

}

void printMap(const Map *map){
    for(int i = 0; i < map->size; i++){
        printf("%p: %d\n",map->keys[i],map->values[i]);
    }
}

void destroyMap(Map *map){
    for (int i = 0; i < map->size; ++i) {
        free(map->keys[i]);
    }
    free(map->keys);
    free(map->values);
}
