#include "Node.hpp"

uint64_t Node::lastID = 0;

Node::Node(Color ColorC, double Radius, double Mass, V2 Position, V2 Velocity) {
	lastID++;
	ID = lastID;
	position = Position;

	color = ColorC;
	radius = Radius;

	isFixed = false;
	isCollidable= false;
	mass = Mass;
	velocity = Velocity;
}

Node::Node(Color ColorC, double Radius, V2 Position) {
	lastID++;
	ID = lastID;
	position = Position;

	color = ColorC;
	radius = Radius;

	isFixed = true;
	isCollidable = false;
	mass = 1;
	velocity = { 0, 0 };
}