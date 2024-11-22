#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

// Player class
typedef struct Player {
    Vector2 position;
    float speed;
    Vector2 direction;
    Vector2 velocity;
    Rectangle bounds;
    float rotation;
    int health;
} Player;

// Initializes a player and returns it
Player InitPlayer(Vector2 position, Rectangle bounds, float speed);
// Draws the player
void DrawPlayer(Player* player);
// Updates the player
void UpdatePlayer(Player* player, float delta);
// Rotates the player to the mouse position
void RotateToMouse(Player* player, Camera2D camera);


// Camera Control
void CameraZoom(float delta, Camera2D* camera);
// Resets the camera
void ResetCamera(Camera2D* camera);
// Zooms in
void ZoomInCamera(float delta, Camera2D* camera);
// Zooms out
void ZoomOutCamera(float delta, Camera2D* camera);

#endif