

#include "include/raylib.h"

const int screenWidth = 1200;
const int screenHeight = 600;


typedef struct Circle
{
    Vector2 position;
    Vector2 delta;
    int radius;
} Circle;


void update_circle_coordinates(Circle *circle)
{

    circle->position.x += circle->delta.x;
    circle->position.y += circle->delta.y;

    if(circle->position.x + circle->radius >= screenWidth || circle->position.x - circle->radius <= 0) 
    {
        circle->delta.x *= -1;
    }

    if(circle->position.y + circle->radius >= screenHeight || circle->position.y - circle->radius <= 0)
    {
        circle->delta.y *= -1;
    }
}

int main(void)
{

    Circle circle = {
        {50,50},
        {4,4},
        10,
    };

    InitWindow(screenWidth, screenHeight, "raylib pong game");

    SetTargetFPS(60); 

    while (!WindowShouldClose())        
    {

        ClearBackground(BLACK);
        update_circle_coordinates(&circle);
        BeginDrawing();
        DrawCircleV(circle.position, circle.radius, PINK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}