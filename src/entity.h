#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "config.h"

typedef enum EntityType {
    ZERO = 0,
    CONVEYOR,
    MACHINE
} EntityType;

typedef struct Entity{
    Vector2 position;
    EntityType type;
    void (*tick)(struct Entity* entity);
} Entity;

typedef struct EntityList{
    Entity entities[MAP_SIZE][MAP_SIZE];
} EntityList;

EntityList* InitEntities();
void DrawEntities(EntityList* entities, Camera2D* camera);
void AddEntity(EntityList* entities, EntityType type, Vector2 position);
void TickEntities(EntityList* entities);

#endif