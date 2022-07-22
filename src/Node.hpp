#pragma once
#include "V2.hpp"

#include "../include/raylib.h"
#include <vector>

struct Node {
	//Entity
	static uint64_t lastID;
	uint64_t ID;
	V2 position;

	//Renderer
	Color color;
	
	//Collider
	double radius;

	//Rigidbody
	bool isFixed;
	bool isCollidable;
	double mass;
	V2 velocity;
	V2 force;

	Node(Color ColorC, double Radius, double Mass, V2 Position, V2 Velocity);
	Node(Color ColorC, double Radius, V2 Position);
};