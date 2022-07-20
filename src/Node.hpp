#pragma once
#include "V2.hpp"

#include "../include/raylib.h"
#include <vector>

struct Node {
	static uint64_t lastID;
	uint64_t ID;
	V2 position;

	Color color;
	float radius;

	bool collidable;
	float mass;
	V2 velocity;
	V2 force;

	Node(Color ColorC, float Radius, float Mass, V2 Position, V2 Velocity);
};