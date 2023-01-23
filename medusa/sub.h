#pragma once
#include "submenu.h"

namespace medusa::ui {
	class sub : public base_submenu<sub> {
	public:
		explicit sub() = default;
		~sub() noexcept = default;
		explicit sub(const char* name, uint32_t id, std::function<void(sub*)> action) {
			set_name(name);
			set_id(id);
			set_action(std::move(action));
		}
		sub(sub const&) = default;
		sub& operator=(sub const&) = default;
		sub(sub&&) = default;
		sub& operator=(sub&&) = default;
	};
}
