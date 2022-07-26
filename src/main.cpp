#include "Config.h"

#include <raylib.h>
#include <raygui.h>

#include "V2.h"
#include "Entity.h"
#include "Circle.h"

int main (int argc, char* argv[]) {
    Renderer::InitializeWindow();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    Renderer::CloseWindow();
    return 0;
}