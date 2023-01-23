#include "pch.h"
#include "patterns.h"
#include "all.h"

using namespace memory;

namespace medusa {
	void patterns::scan() {
		batch batch;

		batch.Add("SVM", ida_sig("E8 ? ? ? ? 48 85 FF 48 89 1D"), [this](Ptr ptr) {
			m_script_vm = ptr.call().as<script_vm>();
		});

		batch.Add("FC", ida_sig("8B 15 ? ? ? ? 41 FF CF"), [this](Ptr ptr) {
			m_frame_count = ptr.add(2).rip().as<uint32_t*>();
		});

		batch.Add("NH", ida_sig("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A"), [this](Ptr ptr) {
			m_native_registration_table = ptr.from_instruction().as<rage::scrNativeRegistrationTable*>();
			m_get_native_handler = ptr.add(12).rip().as<get_native_handler>();
		});

		batch.Add("FV", ida_sig("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA"), [this](Ptr ptr) {
			m_fix_vectors = ptr.as<fix_vectors>();
		});

		batch.Add("NRF", ida_sig("FF E3"), [this](Ptr ptr) {
			m_native_return = ptr.add(0).as<PVOID>();
		});

		batch.Add("TJC", ida_sig("48 89 5C 24 ? 89 54 24 10 57 48 83 EC 30 0F 29 74 24"), [this](Ptr ptr) {
			m_taskjump_constructor = ptr.as<PVOID>();
		});

		auto _module = memory::module("GTA5.exe");
		batch.run(_module);

		m_hwnd = FindWindowW(L"grcWindow", nullptr);

		if (!m_hwnd)
			throw std::runtime_error("Cant Find GTA5.exe");
	}
}