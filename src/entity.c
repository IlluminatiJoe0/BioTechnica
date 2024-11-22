#include "raylib.h"
#include "entity.h"
#include "utils.h"
#include "funcList.h"

static EntityList entityList = {0};

EntityList* InitEntities(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            entityList.entities[i][j].type = ZERO;
        }
    }
    
    return &entityList;
}

void DrawEntities(EntityList* entities, Camera2D* camera){
    Vector4 renderBounds = GetScreenRenderBounds(camera);

    int startI = renderBounds.x;
    int startJ = renderBounds.y;
    int endI = renderBounds.z;
    int endJ = renderBounds.w;

    for (int i = startI; i < endI; i++) {
        for (int j = startJ; j < endJ; j++) {
            if (entities->entities[i][j].type != ZERO) {
                DrawRectangle(i * BLOCK_SIZE, j * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, RED);
            }
        }
    }
}

void TickEntities(EntityList* entities){
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (entities->entities[i][j].type != ZERO) {
                entities->entities[i][j].tick(&entities->entities[i][j]);
            }
        }
    }
}

void AddEntity(EntityList* entities, EntityType type, Vector2 position){
    if (entities->entities[(int)position.x][(int)position.y].type != ZERO) return;
    entities->entities[(int)position.x][(int)position.y].type = type;
    entities->entities[(int)position.x][(int)position.y].tick = ConveyorTick;
}