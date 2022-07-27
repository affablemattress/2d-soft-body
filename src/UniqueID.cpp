#include "UniqueID.h"

uint32_t UniqueID::GenerateID() {
	lastID_++;
	return lastID_;
}