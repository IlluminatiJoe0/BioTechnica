#include "config.h"
#include "raylib.h"
#include "player.h"
#include "raymath.h"
#include "enemy.h"

Enemy InitEnemy(Vector2 position, float speed) {
    Enemy enemy = {position, speed};
    return enemy;
}

void DrawEnemy(Enemy* enemy) {
    DrawRectanglePro((Rectangle){enemy->position.x, enemy->position.y, BLOCK_SIZE, BLOCK_SIZE}, (Vector2){8, 8}, 0, RED);
}

void UpdateEnemy(Enemy* enemy, Player* player) {
    Vector2 direction = (Vector2){player->position.x - enemy->position.x, player->position.y - enemy->position.y};
    direction = Vector2Normalize(direction);
    enemy->position = (Vector2){enemy->position.x + direction.x * enemy->speed, enemy->position.y + direction.y * enemy->speed};
}

