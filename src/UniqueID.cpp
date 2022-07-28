#include "UniqueID.h"

namespace Patchwork {
	uint32_t UniqueID::GenerateID() {
		lastID_++;
		return lastID_;
	}
}