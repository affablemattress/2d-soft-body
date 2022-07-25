#include "Spring.hpp"

void Spring::ApplySpring() {
	V2 deltaX = (second->position - first->position);
	V2 springDisplacement = deltaX - V2::Normalized(deltaX) * length;
	first->force = first->force + springDisplacement * springConstant;
	second->force = second->force - springDisplacement * springConstant;
}

void Spring::ApplyDamper() {
	V2 deltaX = (second->position - first->position);
	V2 deltaVAlongDeltaX = V2::Normalized(deltaX) * V2::Dot(second->velocity - first->velocity, deltaX);
	first->force = first->force + deltaVAlongDeltaX * dampingCoefficient;
	second->force = second->force - deltaVAlongDeltaX * dampingCoefficient;
}

Spring::Spring(Node* First, Node* Second, double Length, double SpringConstant, double DampingCoefficient) {
	first = First;
	second = Second;
	length = Length;
	springConstant = SpringConstant;
	dampingCoefficient = DampingCoefficient;
}