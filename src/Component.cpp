#include "Component.h"
#include "UniqueID.h"

Component::Type Component::GetType() const { return type_; }
uint32_t Component::GetID() const {
	return kID_;
}

Component::Component(Type type) 
	: kID_(UniqueID::GenerateID()), type_(type) {}
Component::~Component() {}