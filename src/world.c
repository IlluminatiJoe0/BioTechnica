#include "world.h"
#include "tile.h"
#include "raylib.h"
#include <stdio.h>
#include "utils.h"

#define FNL_IMPL
#include "FastNoiseLite.h"

static World world = {0};

void PopulateGrass(World* world) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            world->tiles[i][j] = GRASS;
        }
    }
}

void PopulateDirt(World* world, fnl_state noise) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (fnlGetNoise2D(&noise, i, j) > 0.5f)
            {
                world->tiles[i][j] = DIRT;
            }
        }
    }
}

void PopulateStone(World* world, fnl_state noise) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (fnlGetNoise2D(&noise, i, j) < -0.5f)
            {
                world->tiles[i][j] = STONE;
            }
        }
    }
}

void DrawTile(TileType type, Vector2 position, Texture2D grass) {
    switch (type) {
        case GRASS:
            //DrawRectangle(position.x, position.y, BLOCK_SIZE, BLOCK_SIZE, GREEN);
            //DrawTexture(grass, position.x, position.y, GREEN);
            break;
        case DIRT:
            DrawRectangle(position.x, position.y, BLOCK_SIZE, BLOCK_SIZE, BROWN);
            break;
        case STONE:
            DrawRectangle(position.x, position.y, BLOCK_SIZE, BLOCK_SIZE, GRAY);
            break;
    }
}

World* InitWorld() {
    // Create and configure noise state
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_PERLIN; 

    PopulateGrass(&world);
    PopulateDirt(&world, noise);
    PopulateStone(&world, noise);

    return &world;
}

void DrawWorld(World* world, Camera2D* camera, Texture2D grass) {
    Vector4 renderBounds = GetScreenRenderBounds(camera);

    int startI = renderBounds.x;
    int startJ = renderBounds.y;
    int endI = renderBounds.z;
    int endJ = renderBounds.w;

    for (int i = startI; i < endI; i++) {
        for (int j = startJ; j < endJ; j++) {
            DrawTile(world->tiles[i][j], (Vector2){i * BLOCK_SIZE, j * BLOCK_SIZE}, grass);
        }
    }
}