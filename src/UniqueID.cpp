#include "UniqueID.h"

namespace Shabby {
	uint32_t UniqueID::GenerateID() {
		lastID_++;
		return lastID_;
	}
}