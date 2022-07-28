#include "Component.h"
#include "UniqueID.h"

namespace Patchwork {
	uint32_t Component::GetID() const {
		return kID_;
	}

	Component::Component() 
		: kID_(UniqueID::GenerateID()) {}
	Component::~Component() {}
}