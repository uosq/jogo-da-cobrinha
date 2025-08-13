#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define GRID_BLOCK_SIZE 32
#define MAX_SNAKE_SIZE 256
#define MOVE_INTERVAL_SECS 0.15

typedef struct Snake {
    Vector2 pos;
    Vector2 vel;
    Color color;
} Snake;

typedef struct Food {
    Vector2 pos;
    Color color;
} Food;

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "croba");
    SetTargetFPS(60);

    int tailCounter = 10;
    Snake snake[MAX_SNAKE_SIZE] = {0};
    Color backgroundColor = (Color){46, 52, 64, 255};
    Color gridLines = (Color){236, 239, 244, 255};
    Color headBlack = (Color){216, 222, 233, 255};
    Color tailGreen = (Color){163, 190, 140, 255};
    Color foodColor = (Color){191, 97, 106, 255};

    // set snake pos & vel to 0
    for (int i = 0; i < MAX_SNAKE_SIZE; i++) {
        snake[i].pos = (Vector2){0.0, 0.0};
        snake[i].vel = (Vector2){0.0, 0.0};
        snake[i].color = i == 0 ? headBlack : tailGreen;
    }

    Food food = {0};
    food.pos = (Vector2){GetRandomValue(0, (WINDOW_WIDTH/GRID_BLOCK_SIZE) - 1)*GRID_BLOCK_SIZE, GetRandomValue(0, (WINDOW_HEIGHT/GRID_BLOCK_SIZE) - 1)*GRID_BLOCK_SIZE};
    food.color = foodColor;

    double nextMoveTime = 0;

    while (!WindowShouldClose()) {
        double currentTime = GetTime();

        if (IsKeyPressed(KEY_D) && snake[0].vel.x == 0)
            snake[0].vel = (Vector2){GRID_BLOCK_SIZE, 0.0};
        if (IsKeyPressed(KEY_A) && snake[0].vel.x == 0)
            snake[0].vel = (Vector2){-GRID_BLOCK_SIZE, 0.0};
        if (IsKeyPressed(KEY_S) && snake[0].vel.y == 0)
            snake[0].vel = (Vector2){0.0, GRID_BLOCK_SIZE};
        if (IsKeyPressed(KEY_W) && snake[0].vel.y == 0)
            snake[0].vel = (Vector2){0, -GRID_BLOCK_SIZE};

        if (currentTime >= nextMoveTime) {
            for (int i = 0; i < tailCounter; i++) {
                if (snake[i].pos.x == food.pos.x && snake[i].pos.y == food.pos.y) {
                    tailCounter++;
                    food.pos = (Vector2){GetRandomValue(0, (WINDOW_WIDTH/GRID_BLOCK_SIZE) - 1)*GRID_BLOCK_SIZE, GetRandomValue(0, (WINDOW_HEIGHT/GRID_BLOCK_SIZE) - 1)*GRID_BLOCK_SIZE};
                }
            }

            Vector2 prevPos = snake[0].pos;
            snake[0].pos.x += snake[0].vel.x;
            snake[0].pos.y += snake[0].vel.y;

            for (int i = 1; i < tailCounter; i++) {
                Vector2 temp = snake[i].pos;
                snake[i].pos = prevPos;
                prevPos = temp;
            }

            nextMoveTime = currentTime + MOVE_INTERVAL_SECS;
        }

        BeginDrawing();
        
        ClearBackground(backgroundColor);
        
        // draw food
        DrawRectangleV(food.pos, (Vector2){GRID_BLOCK_SIZE, GRID_BLOCK_SIZE}, foodColor);

        // draw snake
        for (int i = 0; i < tailCounter; i++) {
            DrawRectangle(snake[i].pos.x, snake[i].pos.y, GRID_BLOCK_SIZE, GRID_BLOCK_SIZE, snake[i].color);
        }

        // draw grid
        for (int y = 0; y < WINDOW_HEIGHT; y = y + GRID_BLOCK_SIZE) {
            DrawLine(0, y, WINDOW_WIDTH, y, gridLines);
        }

        for (int x = 0; x < WINDOW_WIDTH; x = x + GRID_BLOCK_SIZE) {
            DrawLine(x, 0, x, WINDOW_HEIGHT, gridLines);
        }

        //DrawText(TextFormat("%f", currentTime), 10, 10, 16, WHITE);
        DrawText(TextFormat("Frutas: %i", tailCounter), 10, 10, 24, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 1;
}