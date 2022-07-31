#define LOG_LEVEL_DEBUG
#include "LOG.hpp"
#include "V2.hpp"
#include "Node.hpp"
#include "Spring.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../include/raylib.h"
#include "../include/raygui.h"
#include <string>
#include <vector>

#define WIDTH 1200
#define HEIGHT 800
#define TITLE "Mass-Spring-Damper Pendulum"
#define FPS 1920
#define PIXELS_PER_UNIT 5

#define UNIT_HEIGHT HEIGHT/PIXELS_PER_UNIT 
#define UNIT_WIDTH WIDTH/PIXELS_PER_UNIT
#define DELTA_T 1 / 960

V2 gravity = { 0, -9.81 };
const double kBorderThickness = 3;

std::vector<Node*> allNodes;
std::vector<Node*> collidables;
std::vector<Spring*> springs;
bool isPaused = false;
double GUIe = 1;
double GUIDragCoefficient = 0.1;

std::string GUIeText = "";
std::string GUIDragCoefficientText = "";

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

void ApplyDrag(Node* node) {
    node->force = node->force + (-node->velocity * pow(node->radius, 2) * GUIDragCoefficient);
}

void ApplyGravity(Node* node) {
    node->force = node->force + (gravity * node->mass);
}

void ApplyKinematics(Node* node) {
    node->position = node->position + (node->velocity * DELTA_T) + (node->force / node->mass) * pow(DELTA_T, 2) * 0.5f;
    node->velocity = node->velocity + (node->force / node->mass) * DELTA_T;
    node->force = { 0, 0 };
}

//------Drawing------//
void DrawBorders() {
    DrawRectangle(0, 0, kBorderThickness, HEIGHT, GRAY);
    DrawRectangle(WIDTH - kBorderThickness, 0, kBorderThickness, HEIGHT, GRAY);
    DrawRectangle(0, 0, WIDTH, kBorderThickness, GRAY);
    DrawRectangle(0, HEIGHT - kBorderThickness, WIDTH, kBorderThickness, GRAY);
}

void DrawSpring(Spring* spring) {
    DrawLine(WIDTH / 2 + spring->first->position.x * PIXELS_PER_UNIT, 
             HEIGHT / 2 - spring->first->position.y * PIXELS_PER_UNIT, 
             WIDTH / 2 + spring->second->position.x * PIXELS_PER_UNIT, 
             HEIGHT / 2 - spring->second->position.y * PIXELS_PER_UNIT,
             BLACK);
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

    GUIDragCoefficient = GuiSlider(Rectangle{ 164 , HEIGHT - 60, 95, 15 }, "Drag Coefficient  ", GUIDragCoefficientText.c_str(), GUIDragCoefficient, 0, 0.5);
    GUIDragCoefficientText = std::to_string(GUIDragCoefficient).substr(0, 5);

    DrawText("Press [SPACE] to pause.", WIDTH / 2 - MeasureText("Press [SPACE] to pause.", 10) / 2, 15, 10, GRAY);
    if (IsKeyPressed(KEY_SPACE)) {
        isPaused ^= 1;
    }
}

int main()
{
    double gridLength = 10;
    Node* first = new Node(RED, 1, 1, { 1 * gridLength, 2 * gridLength * 0.866 }, { 0, 0 });
    MakeCollidable(first);
    allNodes.push_back(first);
    Node* second = new Node(GREEN, 1, 1, { 0.5 * gridLength, 1 * gridLength * 0.866 }, { 0, 0 });
    MakeCollidable(second);
    allNodes.push_back(second);
    Node* third = new Node(BLUE, 1, 1, { 1.5 * gridLength, 1 * gridLength * 0.866 }, { 0, 0 });
    MakeCollidable(third);
    allNodes.push_back(third);
    Node* fourth = new Node(RED, 1, 1, { 0, 0 }, { 0, 0 });
    MakeCollidable(fourth);
    allNodes.push_back(fourth);
    Node* fifth = new Node(GREEN, 1, 1, { 1 * gridLength, 0 }, { 0, 0 });
    MakeCollidable(fifth);
    allNodes.push_back(fifth);
    Node* sixth = new Node(BLUE, 1, 1, { 2 * gridLength, 0 }, { 0, 0 });
    MakeCollidable(sixth);
    allNodes.push_back(sixth);


    double springLength = gridLength;
    double springConstant = 400;
    double dampingCoefficient = 0.1;
    springs.push_back(new Spring(first, second, springLength, springConstant, dampingCoefficient));
    springs.push_back(new Spring(first, third, springLength, springConstant, dampingCoefficient));
    springs.push_back(new Spring(second, third, springLength, springConstant, dampingCoefficient));

    springs.push_back(new Spring(second, fourth, springLength, springConstant, dampingCoefficient));
    springs.push_back(new Spring(second, fifth, springLength, springConstant, dampingCoefficient));
    springs.push_back(new Spring(fourth, fifth, springLength, springConstant, dampingCoefficient));

    springs.push_back(new Spring(third, fifth, springLength, springConstant, dampingCoefficient));
    springs.push_back(new Spring(third, sixth, springLength, springConstant, dampingCoefficient));
    springs.push_back(new Spring(fifth, sixth, springLength, springConstant, dampingCoefficient));

    Node* obstacle = new Node(RED, 7, 1, { 3, -10 }, { 0, 0 });
    MakeCollidable(obstacle);
    obstacle->isFixed = true;
    allNodes.push_back(obstacle);

    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);

    bool switchie = true;
    double lastPos = 0;
    double pos = 0;
    int step = 0;
    while (!WindowShouldClose()) {
        if (!isPaused) {
            CheckForCollisionsInVector(collidables);
            for (Spring* spring : springs) {
                spring->ApplySpring();
                spring->ApplyDamper();
            }
            for (Node* node : collidables) {
                CheckForBoundaryCollision(node);
            }
            for (Node* node : allNodes) {
                if (!node->isFixed) {
                    ApplyDrag(node);
                    ApplyGravity(node);
                    ApplyKinematics(node);
                }
            }
        }

        BeginDrawing();
        DrawGUIBackground();

        for (Spring* spring : springs) {
            DrawSpring(spring);
        }
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
