#include "raylib.h"
#include "config.h"
#include "player.h"
#include "raymath.h"
#include "utils.h"

// Returns a Vector2 representing the player's direction
Vector2 GetPlayerDirectionFromInput() {
    Vector2 direction = {0.0, 0.0};
    if (IsKeyDown(KEY_W)) {
        direction.y -= 1.0;
    }
    if (IsKeyDown(KEY_S)) {
        direction.y += 1.0;
    }
    if (IsKeyDown(KEY_A)) {
        direction.x -= 1.0;
    }
    if (IsKeyDown(KEY_D)) {
        direction.x += 1.0;
    }
    return direction;
}

void CameraZoom(float delta, Camera2D* camera) {
    if (GetMouseWheelMove() > 0) {
        ZoomInCamera(delta, camera);
    }
    if (GetMouseWheelMove() < 0) {
        ZoomOutCamera(delta, camera);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        ResetCamera(camera);
    }
    
}

Player InitPlayer(Vector2 position, Rectangle bounds, float speed) {
    Player player = {position, speed, {0, 0}, {0, 0}, bounds, 0.0f, 100};
    return player;
}

void DrawPlayer(Player* player) {
    DrawRectanglePro((Rectangle){player->position.x, player->position.y, BLOCK_SIZE, BLOCK_SIZE}, (Vector2){BLOCK_SIZE/2, BLOCK_SIZE/2}, player->rotation, WHITE);
}

void UpdatePlayer(Player* player, float delta) {
    player->direction = GetPlayerDirectionFromInput();
    player->direction = Vector2Normalize(player->direction);

    // TODO: check for collision

    player->velocity = (Vector2) {player->direction.x * player->speed * delta, player->direction.y * player->speed * delta};

    player->position = (Vector2){player->position.x + player->velocity.x, player->position.y + player->velocity.y};

    player->bounds = (Rectangle){player->position.x, player->position.y, BLOCK_SIZE, BLOCK_SIZE};
}

void RotateToMouse(Player* player, Camera2D camera) {
    Vector2 mousePosition = GetWorldMousePosition(GetMousePosition(), camera);
    player->rotation = RAD2DEG * atan2(mousePosition.y - player->position.y, mousePosition.x - player->position.x);
}

void ZoomInCamera(float delta, Camera2D* camera) {
    if (camera->zoom <= 2.0f)
    {
        camera->zoom += delta;
        if (camera->zoom >= 2.0f) camera->zoom = 2.0f;
    }
}

void ZoomOutCamera(float delta, Camera2D* camera) {
    if (camera->zoom >= 0.5f)
    {
        camera->zoom -= delta;
        if (camera->zoom <= 0.5f) camera->zoom = 0.5f;
    }
}

void ResetCamera(Camera2D* camera) {
    camera->zoom = 1.0f;
}
