#include "raylib.h"
#include "utils.h"
#include "config.h"

Vector2 GetWorldMousePosition(Vector2 position, Camera2D camera) {
    return GetScreenToWorld2D(position, camera);
}

Vector4 GetScreenRenderBounds(Camera2D* camera) {
    int startI = (int)((camera->target.x - WINDOW_WIDTH/2 / camera->zoom) / BLOCK_SIZE) - 1;
    int startJ = (int)((camera->target.y - WINDOW_HEIGHT/2 / camera->zoom) / BLOCK_SIZE) - 1;
    int endI = (int)((camera->target.x + WINDOW_WIDTH/2 / camera->zoom) / BLOCK_SIZE) + 1;
    int endJ = (int)((camera->target.y + WINDOW_HEIGHT/2 / camera->zoom) / BLOCK_SIZE) + 1;

    if (startI < 0) startI = 0;
    if (startJ < 0) startJ = 0;
    if (endI > MAP_SIZE) endI = MAP_SIZE;
    if (endJ > MAP_SIZE) endJ = MAP_SIZE;

    return (Vector4){startI, startJ, endI, endJ};
}

Vector2 GetArrayPositionFromMousePosition(Vector2 position, Camera2D camera) {
    Vector2 worldPos = GetWorldMousePosition(position, camera);
    return (Vector2){worldPos.x / BLOCK_SIZE, worldPos.y / BLOCK_SIZE};
}