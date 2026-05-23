#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

void draw_pendulum(float length, Vector2 start, float phi){
    Vector2 end = (Vector2){start.x + length * sinf(phi), start.y + length * cosf(phi)};
    DrawLineV(start, end, WHITE);
}

int main(){
    InitWindow(WIDTH, HEIGHT, "Double Pendulum");

    Vector2 start = (Vector2){WIDTH/2, 0};

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        draw_pendulum(150, start, 0);
        EndDrawing();
    }
    return 0;
}

