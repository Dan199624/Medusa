#pragma once
#include <cstdint>
#include <optional>
#include <string_view>
#include <vector>
#include "fwddec.h"
#include "ptr.h"

namespace memory
{
	class pattern
	{
		friend batch;
		friend range;
	public:
		pattern(std::string_view ida_sig);
		explicit pattern(const void* bytes, std::string_view mask);

		inline pattern(const char* ida_sig) :
			pattern(std::string_view(ida_sig))
		{}

		std::vector<std::optional<std::uint8_t>> m_bytes;
	};
}