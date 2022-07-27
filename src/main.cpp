#include "Config.h"
#include "V2.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

#include <iostream> 
#include <raylib.h>
#include <raygui.h>


int main (int argc, char* argv[]) {
    GameObject* first = new GameObject(V2(0, 0), 0);
    Transform* firstTransform = new Transform({ 5, 5 }, 56);
    std::cout << first->GetTransform()->GetPosition().GetX() << std::endl;
    first->SetTransform(firstTransform);
    std::cout << first->GetTransform()->GetPosition().GetX() << std::endl;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Soft-Body");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
