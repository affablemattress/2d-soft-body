#pragma once
#include "V2.hpp"
#include "Node.hpp"

#include "../include/raylib.h"
#include <vector>

class Spring {
public:
	Node* first;
	Node* second;
	double length;
	double springConstant;
	double dampingCoefficient;
	Spring(Node* First,  Node* Second, double Length, double SpringConstant, double DampingCoefficient);

	void ApplySpring();
	void ApplyDamper();
};