//TO DO: Add Drag

#define LOG_LEVEL_DEBUG
#include "LOG.hpp"
#include "V2.hpp"
#include "Node.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../include/raylib.h"
#include "../include/raygui.h"
#include <string>
#include <vector>

#define WIDTH 1200
#define HEIGHT 800
#define TITLE "Mass-Spring-Damper Pendulum"
#define FPS 960
#define PIXELS_PER_UNIT 10

#define UNIT_HEIGHT HEIGHT/PIXELS_PER_UNIT
#define UNIT_WIDTH WIDTH/PIXELS_PER_UNIT
#define DELTA_T 1/FPS

V2 gravity = { 0, -9.81 };
const double kBorderThickness = 3;

std::vector<Node*> allNodes;
std::vector<Node*> collidables;
bool isPaused = false;
double GUIe = 1;

std::string GUIeText = "";

void MakeCollidable(Node* node) {
    if (node->isCollidable == false) {
        node->isCollidable = true;
        collidables.push_back(node);
        return;
    }
    else return;
}

void MakeUnCollidable(Node* node) {
    if (node->isCollidable == true) {
        node->isCollidable = false;
        for (int i = 0; i < collidables.size(); i++) {
            if (node->ID == collidables.at(i)->ID) {
                collidables.erase(collidables.begin() + i);
                return;
            }
        }
        return;
    }
    else return;
}

//-----Collisions-----//

void CheckForBoundaryCollision(Node* node) {
    if (!node->isFixed) {
        if (node->position.x < -(UNIT_WIDTH / 2) + (kBorderThickness / PIXELS_PER_UNIT) + node->radius) {
            node->position.x = -(UNIT_WIDTH / 2) + (kBorderThickness / PIXELS_PER_UNIT) + node->radius;
            node->velocity.x = -node->velocity.x * GUIe;
        }
        else if (node->position.x > (UNIT_WIDTH / 2) - (kBorderThickness / PIXELS_PER_UNIT) - node->radius) {
            node->position.x = (UNIT_WIDTH / 2) - (kBorderThickness / PIXELS_PER_UNIT) - node->radius;
            node->velocity.x = -node->velocity.x * GUIe;
        }
        if (node->position.y < -(UNIT_HEIGHT / 2) + (kBorderThickness / PIXELS_PER_UNIT) + node->radius) {
            node->position.y = -(UNIT_HEIGHT / 2) + (kBorderThickness / PIXELS_PER_UNIT) + node->radius;
            node->velocity.y = -node->velocity.y * GUIe;
        }
        else if (node->position.y > (UNIT_HEIGHT / 2) - (kBorderThickness / PIXELS_PER_UNIT) - node->radius) {
            node->position.y = (UNIT_HEIGHT / 2) - (kBorderThickness / PIXELS_PER_UNIT) - node->radius;
            node->velocity.y = -node->velocity.y * GUIe;
        }
    }
}

bool CheckForCollision(Node* first, Node* second) {
    return (pow(second->position.x - first->position.x, 2) + pow(second->position.y - first->position.y, 2) < pow(first->radius + second->radius, 2));
}

void CollisionResponse(Node* first, Node* second) {
    if (!first->isFixed && !second->isFixed) {
        //Dynamic Response
        V2 normal = V2::Normalized((second->position - first->position));
        float impulse = abs(V2::Dot((first->velocity - second->velocity), normal) * (GUIe + 1) * (first->mass * second->mass) / (first->mass + second->mass));
        first->velocity = first->velocity - (normal * impulse) / first->mass;
        second->velocity = second->velocity + (normal * impulse) / second->mass;
        //Displace/Static Response
        float deltaX = first->radius + second->radius - V2::Distance(first->position, second->position);
        first->position = first->position - normal * (deltaX / 2.f);
        second->position = second->position + normal * (deltaX / 2.f);
    }
    else if (first->isFixed && !second->isFixed) {
        V2 normal = V2::Normalized((second->position - first->position));
        float impulse = abs(V2::Dot((second->velocity), normal) * (GUIe + 1) * second->mass);
        second->velocity = second->velocity + (normal * impulse) / second->mass;
        float deltaX = first->radius + second->radius - V2::Distance(first->position, second->position);
        second->position = second->position + normal * deltaX;
    }
    else if (!first->isFixed && second->isFixed) {
        V2 normal = V2::Normalized((second->position - first->position));
        float impulse = abs(V2::Dot((first->velocity), normal) * (GUIe + 1) * first->mass);
        first->velocity = first->velocity - (normal * impulse) / first->mass;
        float deltaX = first->radius + second->radius - V2::Distance(first->position, second->position);
        first->position = first->position - normal * deltaX;
    }
}

void CheckForCollisionsInVector(std::vector<Node*>& vector) {
    for (int i = 0; i < vector.size(); i++) {
        for (int j = i + 1; j < vector.size(); j++) {
            if (CheckForCollision(vector.at(i), vector.at(j))) {
                CollisionResponse(vector.at(i), vector.at(j));
            }
        }
    }
}

//-----Kinematics----//

void ApplyGravity(Node* node) {
    if (!node->isFixed) {
        node->force = node->force + (gravity * node->mass);
    }
}

//TO DO: Kinetic enegrgy increases with each bounce (and over time?)
void ApplyKinematics(Node* node) {
    if (!node->isFixed) {
        node->position = node->position + (node->velocity * DELTA_T) + (node->force / node->mass) * pow(DELTA_T, 2) * 0.5f;
        node->velocity = node->velocity + (node->force / node->mass) * DELTA_T;
        node->force = { 0, 0 };
    }
}

//------Drawing------//
void DrawBorders() {
    DrawRectangle(0, 0, kBorderThickness, HEIGHT, GRAY);
    DrawRectangle(WIDTH - kBorderThickness, 0, kBorderThickness, HEIGHT, GRAY);
    DrawRectangle(0, 0, WIDTH, kBorderThickness, GRAY);
    DrawRectangle(0, HEIGHT - kBorderThickness, WIDTH, kBorderThickness, GRAY);
}

void DrawNode(Node* node) {
    DrawCircle(WIDTH / 2 + node->position.x * PIXELS_PER_UNIT, HEIGHT / 2 - node->position.y * PIXELS_PER_UNIT, node->radius * PIXELS_PER_UNIT, node->color);
    DrawCircle(WIDTH / 2 + node->position.x * PIXELS_PER_UNIT, HEIGHT / 2 - node->position.y * PIXELS_PER_UNIT, node->radius * PIXELS_PER_UNIT - PIXELS_PER_UNIT / 5, GRAY);
    DrawCircle(WIDTH / 2 + node->position.x * PIXELS_PER_UNIT, HEIGHT / 2 - node->position.y * PIXELS_PER_UNIT, PIXELS_PER_UNIT / 5, BLACK);
}

void DrawGUIBackground() {
    if (isPaused) {
        DrawText("PAUSED", WIDTH / 2 - 410, HEIGHT / 2 - 90, 200, LIGHTGRAY);
    }
}

void DrawGUIForeground() {
    GUIe = GuiSlider(Rectangle{ 164 , HEIGHT - 30, 95, 15 }, "Coefficient of Restitution  ", GUIeText.c_str(), GUIe, 0, 1);
    GUIeText = std::to_string(GUIe).substr(0, 3);

    DrawText("Press [SPACE] to pause.", WIDTH / 2 - MeasureText("Press [SPACE] to pause.", 10) / 2, 15, 10, GRAY);
    if (IsKeyPressed(KEY_SPACE)) {
        isPaused ^= 1;
    }
}

int main()
{
    Node* first = new Node(RED, 1, 1, { 12, 12 }, { 5, -3 });
    MakeCollidable(first);
    allNodes.push_back(first);

    Node* second = new Node(GREEN, 5, { -22, -12 });
    MakeCollidable(second);
    allNodes.push_back(second);

    Node* third = new Node(GREEN, 3, { -15, 17 });
    MakeCollidable(third);
    allNodes.push_back(third);

    Node* fourth = new Node(GREEN, 8, { 0, -25 });
    MakeCollidable(fourth);
    allNodes.push_back(fourth);

    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        if (!isPaused) {
            CheckForCollisionsInVector(collidables);
            for (Node* node : collidables) {
                CheckForBoundaryCollision(node);
            }
            for (Node* node : allNodes) {
                ApplyGravity(node);
                ApplyKinematics(node);
            }
            LOG_DEBUG((pow(first->velocity.Length(), 2) * 0.5) + first->position.y * 9.81);
        }

        BeginDrawing();
        DrawGUIBackground();
        for (Node* node : allNodes) {
            DrawNode(node);
        }
        DrawBorders();
        DrawGUIForeground();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
