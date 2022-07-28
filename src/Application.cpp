#include "Application.h"
#include "WindowManager.h"

#include <raylib.h>
#include <raygui.h>

namespace Shabby {
    void Application::Run() {
        WindowManager::InitializeWindow(screenWidth_, screenHeight_, title_, targetFPS_);
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            EndDrawing();
        }
        WindowManager::CloseWindow();
    }

    Application::Application(uint16_t screenWidth, uint16_t screenHeight, const char* title, uint16_t targetFPS) 
        : screenWidth_(screenWidth)
        , screenHeight_(screenHeight)
        , title_(title)
        , targetFPS_(targetFPS) {}
    Application::~Application() {}
}