#include "Component.h"
#include "UniqueID.h"

namespace Shabby {
	Component::Type Component::GetType() const { return type_; }
	uint32_t Component::GetID() const {
		return kID_;
	}

	Component::Component(const Type& type) 
		: kID_(UniqueID::GenerateID()), type_(type) {}
	Component::~Component() {}
}