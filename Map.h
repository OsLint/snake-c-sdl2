typedef struct {
    int size;
    int **keys;
    int *values;

} Map;

void initMap(Map *map,int size);

int getIndexInMap(Map *map,int value);

void insertToMap(Map *map, int value);

void getByKeyFromMap(const Map *map, const char key[]);

void printMap(const Map *map);

void destroyMap(Map *map);
