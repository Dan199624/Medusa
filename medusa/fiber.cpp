#include "pch.h"
#include "fiber.h"
#include "log.h"
namespace medusa {
	void fibers::add(fiber* fiber, void(*function)()) {
		fiber->m_script_fiber = CreateFiber(0, reinterpret_cast<LPFIBER_START_ROUTINE>(function), this);
		fiber->m_func = function;
		fiber->m_wake_at = GetTickCount();
	}
	void fibers::remove(fiber* fiber) {	
	
	}
	void fibers::tick(fiber* fiber) {
		if (GetTickCount() < fiber->m_wake_at) {
			return;
		}
		if (fiber->m_main_fiber == nullptr) {
			fiber->m_main_fiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(NULL);
		}
		if (fiber->m_wake_at <= GetTickCount()) {
			if (fiber->m_script_fiber != nullptr) {
				SwitchToFiber(fiber->m_script_fiber);
			}
		}
	}
	void fibers::wait(fiber* fiber, uint32_t time) {
		fiber->m_wake_at = GetTickCount() + time;
		SwitchToFiber(fiber->m_main_fiber);
	}
	fiber* fibers::get_current_fiber() { return (fiber*)(GetFiberData()); }
}