#pragma once
#include "pch.h"
#include "native_handler.h"

namespace medusa {
	class patterns {
	public:
		void scan();
	public:
		rage::scrNativeRegistrationTable* m_native_registration_table{};
	public:
		HWND m_hwnd{};
		uint32_t* m_frame_count{};
		PVOID m_native_return;
		PVOID m_taskjump_constructor;
	public:
		using script_vm = int(*)(uint64_t* stack, int64_t** globals, uint64_t* program, uint64_t* ctx);
		script_vm m_script_vm;

		using get_native_handler = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable* registration_table, rage::scrNativeHash hash);
		get_native_handler m_get_native_handler;

		using fix_vectors = void(*)(rage::scrNativeCallContext* call_ctx);
		fix_vectors m_fix_vectors;

	}; inline patterns g_patterns;
}