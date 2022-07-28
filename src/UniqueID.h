#pragma once
#include <stdint.h>

namespace Patchwork {
	namespace UniqueID {
		namespace {
			uint32_t lastID_ = 0;
		}
		uint32_t GenerateID();
	}
}

