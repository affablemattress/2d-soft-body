#pragma once
#include <stdint.h>

namespace Shabby {
	namespace UniqueID {
		namespace {
			uint32_t lastID_ = 0;
		}
		uint32_t GenerateID();
	}
}

