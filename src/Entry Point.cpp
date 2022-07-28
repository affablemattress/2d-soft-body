#include "Application.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

int main(int argc, char* argv[]) {
    Shabby::Application* app = new Shabby::Application(1200, 800, "2D Soft Body", 240);
    app->Run();
    delete app;
    return 0;
}