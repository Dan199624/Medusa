#pragma once
#include <cstdint>
#include <windows.h> 

namespace medusa {
	class fiber {
	public:
		void* m_main_fiber;
		void* m_script_fiber;
		void (*m_func)();
		uint32_t m_wake_at;
	};
	class fibers {
	public:
		void add(fiber* fiber, void(*function)());
		void remove(fiber* fiber);
		void tick(fiber* fiber);
		void wait(fiber* fiber, uint32_t time = 0);
		fiber* get_current_fiber();
	};
	inline fibers g_fibers;
	inline fiber g_main_fiber;
	inline fiber g_function_fiber;

}