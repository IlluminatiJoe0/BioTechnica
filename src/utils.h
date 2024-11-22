#ifndef UTILS_H
#define UTILS_H

// Gets the mouse position from the screen to the world space
Vector2 GetWorldMousePosition(Vector2 position, Camera2D camera);
// Returns {startI, startJ, endI, endJ}
Vector4 GetScreenRenderBounds(Camera2D* camera);
// Gets the position in array from the position of the mouse in the world space
Vector2 GetArrayPositionFromMousePosition(Vector2 position, Camera2D camera);

#endif