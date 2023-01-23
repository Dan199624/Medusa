#include "pch.h"
#include "hooks.h"
#include "patterns.h"
#include "log.h"
#include "fiber.h"
#include "invoker.h"
#include "minhook.h"
#pragma comment (lib, "minhook.lib")

#include "player.h"

namespace medusa {
	void hooking::init() {
		MH_Initialize();

		og_script_vm.create_detour("SVM", g_patterns.m_script_vm, &hooks::hk_script_vm);
		og_taskjump_constructor.create_detour("TJC", g_patterns.m_taskjump_constructor, &hooks::hk_taskjump_constructor);

		MH_EnableHook(MH_ALL_HOOKS);
	}
	void hooking::cleanup() {
		og_taskjump_constructor.remove_detour();
		og_script_vm.remove_detour();

		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
	
	uint64_t hooks::hk_script_vm(void* stack, int64_t** globals, uint64_t* program, uint64_t* ctx) {
		static uint32_t hook_frame_count;
		medusa::g_native_invoker.cache_handlers();
		if (hook_frame_count != *g_patterns.m_frame_count) {
			hook_frame_count = *g_patterns.m_frame_count;
			g_fibers.tick(&g_main_fiber);
			g_fibers.tick(&g_function_fiber);
		}
		return g_hooks.og_script_vm.get_original<decltype(&hooks::hk_script_vm)>()(stack, globals, program, ctx);
	}

	uint64_t hooks::hk_taskjump_constructor(std::uint64_t a1, int a2) {
		if (g_player.m_super_jump)
			a2 |= 1 << 15;
		return g_hooks.og_taskjump_constructor.get_original<decltype(&hooks::hk_taskjump_constructor)>()(a1, a2);
	}
}