#pragma once
#include "pch.h"

namespace medusa
{
	class detour {
	public:
		void create_detour(std::string name, void* target, void* detour);
		void remove_detour();

		void enable_detour();
		void disable_detour();

		template <typename T>
		T get_original();
	public:
		std::string m_name;
		void* m_target;
		void* m_detour;
		void* m_original{};
	};

	template <typename T>
	inline T detour::get_original() {
		return static_cast<T>(m_original);
	}
}