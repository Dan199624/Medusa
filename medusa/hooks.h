#pragma once
#include "detour.h"
namespace medusa
{
	class hooks {
	public:
		static uint64_t hk_script_vm(void* stack, int64_t** globals, uint64_t* program, uint64_t* ctx);
		static uint64_t hk_taskjump_constructor(uint64_t a1, int a2);
	};

	class hooking {
	public:
		void init();
		void cleanup();
	public:
		detour og_script_vm;
		detour og_taskjump_constructor;
	}; inline hooking g_hooks;
}