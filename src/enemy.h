#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef struct Enemy
{
    Vector2 position;
    float speed;
} Enemy;

// Initializes a player and returns it
Enemy InitEnemy(Vector2 position, float speed);

// Draws enemy
void DrawEnemy(Enemy* enemy);

// Updates the enemy
void UpdateEnemy(Enemy* enemy, Player* player);


#endif