#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "config.h"

typedef struct World {
    int tiles[MAP_SIZE][MAP_SIZE];
} World;

World* InitWorld();
void DrawWorld(World* world, Camera2D* camera, Texture2D grass);

#endif