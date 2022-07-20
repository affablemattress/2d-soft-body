#include "Node.hpp"

uint64_t Node::lastID = 0;

Node::Node(Color ColorC, float Radius, float Mass, V2 Velocity, V2 Position) {
	lastID++;
	ID = lastID;
	position = Position;

	color = ColorC;
	radius = Radius;

	collidable= false;
	mass = Mass;
	velocity = Velocity;
}