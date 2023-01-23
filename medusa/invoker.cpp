#include "pch.h"
#include "crossmap.h"
#include "invoker.h"
#include "log.h"
#include "patterns.h"

extern "C" void	_call_asm(void* context, void* function, void* ret);

namespace medusa
{
	native_call_context::native_call_context() {
		m_return_value = &m_return_stack[0];
		m_args = &m_arg_stack[0];
	}

	void native_invoker::cache_handlers() {
		if (m_handlers_cached)
			return;

		for (const rage::scrNativeMapping& mapping : g_crossmap) {
			rage::scrNativeHandler handler = g_patterns.m_get_native_handler(
				g_patterns.m_native_registration_table, mapping.second);
			m_handler_cache.emplace(mapping.first, handler);
		}

		m_handlers_cached = true;
	}

	void native_invoker::begin_call() {
		m_call_context.reset();
	}

	void native_invoker::end_call(rage::scrNativeHash hash) {
		if (auto it = m_handler_cache.find(hash); it != m_handler_cache.end()) {
			rage::scrNativeHandler handler = it->second;
			__try {	
				_call_asm(&m_call_context, handler, g_patterns.m_native_return);
				g_patterns.m_fix_vectors(&m_call_context);
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				[hash]() { g_logger.log("Warning", "Exception caught while trying to call %d native", hash); }();
			}
		}
		else {
			[hash]() {  g_logger.log("Warning", "Failed to find %d native handler", hash); }();
		}
	}
}