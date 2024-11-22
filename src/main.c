#include "raylib.h"
#include "raymath.h"
#include "config.h"
#include "utils.h"
#include "world.h"
#include "player.h"
#include "entity.h"

#include "resource_dir.h"

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	SearchAndSetResourceDir("resources");

	// Textures
	Texture2D grass = LoadTexture("grass.png");

	// Variables
	Vector2 screenCenter = (Vector2){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
	Vector2 worldCenter = (Vector2){MAP_SIZE * BLOCK_SIZE / 2, MAP_SIZE * BLOCK_SIZE / 2};

	// Player obj
	Player player = InitPlayer(worldCenter, (Rectangle){screenCenter.x, screenCenter.y, BLOCK_SIZE, BLOCK_SIZE}, PLAYER_SPEED);

	// Camera obj
	Camera2D camera = {0};
	camera.target = player.position;
	camera.offset = screenCenter;
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	// World
	World* world = InitWorld();
	// Entities
	EntityList* entityList = InitEntities();

	// Ticker
	float tickAccumulator = 0.0f;
	float lastTime = GetTime();

	// FPS
	//SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose())
	{
		// Update ticker
		float currentTime = GetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		tickAccumulator += deltaTime;

		// Update player
		UpdatePlayer(&player, deltaTime);
		// Update cam
		CameraZoom(0.05f, &camera);
		// Rotate player
		RotateToMouse(&player, camera);
		// Camera follow
		camera.target = player.position;

		// Input
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			AddEntity(entityList, CONVEYOR, GetArrayPositionFromMousePosition(GetMousePosition(), camera));
		}

		// Update Entities
		while (tickAccumulator >= TICK_DURATION) {
			TickEntities(entityList);
			tickAccumulator -= TICK_DURATION;
		}

		// drawing
		BeginDrawing();

			// Setup the backbuffer for drawing (clear color and depth buffers)
			ClearBackground(GREEN);

			BeginMode2D(camera);

				// Draw world
				DrawWorld(world, &camera, grass);
				DrawEntities(entityList, &camera);

				// Draw player
				DrawPlayer(&player);

			EndMode2D();

			// Debug texts
			DrawText(TextFormat("Player position: (%.2f, %.2f)", player.position.x, player.position.y), 10, 10, 10, WHITE);
			DrawText(TextFormat("Player direction: (%.2f, %.2f)", player.direction.x, player.direction.y), 10, 30, 10, WHITE);
			DrawText(TextFormat("Player velocity: (%.2f, %.2f)", player.velocity.x, player.velocity.y), 10, 50, 10, WHITE);
			DrawText(TextFormat("Player rotation: %.2f", player.rotation), 10, 70, 10, WHITE);
			DrawText(TextFormat("World Mouse Position: (%.2f, %.2f)", GetWorldMousePosition(GetMousePosition(), camera).x, GetWorldMousePosition(GetMousePosition(), camera).y), 10, 90, 10, WHITE);
			DrawText(TextFormat("FPS: %d", GetFPS()), 10, 110, 10, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	UnloadTexture(grass);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}