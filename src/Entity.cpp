#include "Entity.h"

uint32_t Entity::lastID_ = 0;

V2 Entity::GetPosition() { return position_; }
void Entity::SetPosition(const V2& position) {
	position_ = position;
}
uint32_t Entity::GetID() { return kID_; }

Entity::Entity() 
	: kID_(lastID_), position_(V2()) {
	lastID_++;
}
Entity::Entity(V2 position) 
	: kID_(lastID_), position_(position) {
	lastID_++;
}
Entity::~Entity() {};
