#include "raylib.h"
#include "sat.h"
#include <stdio.h>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

float numOfnumsOnScreen;
Vector2 off;

int main(void)
{
    SCREEN_WIDTH = 1200;
    SCREEN_HEIGHT = 800;

    SAT_Polygon polygon1;
    Vector2 points[4] = {(Vector2){100, 100}, (Vector2){100, 200}, (Vector2){200, 200}, (Vector2){200, 100}};
    SAT_CreatePolygon(&polygon1, 4, points);

    SAT_Polygon polygon2;
    Vector2 points2[4] = {(Vector2){200, 150}, (Vector2){200, 200}, (Vector2){250, 200}, (Vector2){250, 150}};
    SAT_CreatePolygon(&polygon2, 4, points2);

    SAT_Polygon polygon3;
    Vector2 points3[4] = {(Vector2){500, 50}, (Vector2){500, 600}, (Vector2){700, 600}, (Vector2){700, 50}};
    SAT_CreatePolygon(&polygon3, 4, points3);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SAT");

    Vector2 normalToMove;

    Vector2 speed = (Vector2){0, 0};
    float maxSpeed = 5;

    float movingStrength;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        speed.x = 0;
        speed.y = 0;
        if (IsKeyDown(KEY_W)) speed.y -= maxSpeed;
        if (IsKeyDown(KEY_S)) speed.y += maxSpeed;
        if (IsKeyDown(KEY_A)) speed.x -= maxSpeed;
        if (IsKeyDown(KEY_D)) speed.x += maxSpeed;

        SAT_MovePolygon(&polygon1, speed);
        SAT_MovePolygon(&polygon2, (Vector2){1.24832984, 0});

        movingStrength = SAT_FindSeparationValue(&polygon1, &polygon2, &normalToMove);
        if (movingStrength < 0) {
            SAT_MovePolygon(&polygon1, (Vector2){movingStrength*normalToMove.x, movingStrength*normalToMove.y});
        }

        movingStrength = SAT_FindSeparationValue(&polygon1, &polygon3, &normalToMove);
        if (movingStrength < 0) {
            SAT_MovePolygon(&polygon1, (Vector2){movingStrength*normalToMove.x, movingStrength*normalToMove.y});
        }

        BeginDrawing();

        ClearBackground(BLACK);
        SAT_DrawPolygon(&polygon1);
        SAT_DrawPolygon(&polygon2);
        SAT_DrawPolygon(&polygon3);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}