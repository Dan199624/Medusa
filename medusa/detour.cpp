#include "pch.h"
#include "detour.h"
#include "log.h"
#include "minhook.h"
#pragma comment (lib, "minhook.lib")

namespace medusa {
	void detour::create_detour(std::string name, void* target, void* detour) {
		m_name = name, m_target = target, m_detour = detour;

		if (auto _hook = MH_CreateHook(target, detour, &m_original); _hook == MH_OK) {
			g_logger.log("Hook", "Hooked %s", name);
		}
	}

	void detour::remove_detour() {
		if (auto _hook = MH_RemoveHook(m_target); _hook == MH_OK) {
			g_logger.log("Hook", "Removed Hook %s", m_name);
		}
	}

	void detour::enable_detour() {
		if (auto _hook = MH_EnableHook(m_target); _hook == MH_OK) {
			g_logger.log("Hook", "Enabled Hook %s", m_name);
		}
	}

	void detour::disable_detour() {
		if (auto _hook = MH_DisableHook(m_target); _hook == MH_OK) {
			g_logger.log("Hook", "Disabled Hook %s", m_name);
		}
	}
}