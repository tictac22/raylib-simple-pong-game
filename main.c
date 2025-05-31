

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
        { screenWidth / 2 ,screenHeight / 2},
        {4,4},
        10,
    };

    
    int paddle_width = 10;
    int paddle_height = 150;
    int paddle_x_position = 25;
    int paddle_y_position = screenHeight / 2  - (paddle_height / 2);
    Rectangle left_paddle = 
    {
        paddle_x_position,
        paddle_y_position,
        paddle_width,
        paddle_height,
    };

    
    Rectangle right_paddle = 
    {
        screenWidth - paddle_x_position - paddle_width,
        paddle_y_position,
        paddle_width,
        paddle_height
    };

    InitWindow(screenWidth, screenHeight, "raylib pong game");

    SetTargetFPS(60); 

    while (!WindowShouldClose())        
    {

        ClearBackground(BLACK);
        update_circle_coordinates(&circle);
        BeginDrawing();
        DrawCircleV(circle.position, circle.radius, PINK);

        DrawRectangleRec(left_paddle, WHITE);
        DrawRectangleRec(right_paddle, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}