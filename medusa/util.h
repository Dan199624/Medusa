#pragma once
#include "pch.h"

namespace medusa::util {
	std::string get_path();
	bool is_key_pressed(std::uint16_t key);
	float conv_360(float base, float min, float max);
}