#include "raylib.h"
#include "funcList.h"
#include "entity.h"

void ConveyorTick(Entity* entity) {
    // simulate a short function without changing entity
    for (int i = 0; i < 10; i++) {
        double x = entity->position.x + i * 0.01;
        double y = entity->position.y + i * 0.01;
        double z = x * x + y * y;
    }
}