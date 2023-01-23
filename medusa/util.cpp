#include "pch.h"
#include "util.h"
#include "patterns.h"

namespace medusa {
	std::string util::get_path() {
		wchar_t folder[1024];
		HRESULT result = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, folder);
		if (SUCCEEDED(result)) {
			char string[1024];
			wcstombs(string, folder, 1023);
			return string;
		}
		else return "";
	}

	bool util::is_key_pressed(std::uint16_t key) {
		if (GetForegroundWindow() == g_patterns.m_hwnd) {
			if (GetAsyncKeyState(key) & 0x8000) {
				return true;
			}
		}
		return false;
	}

	float util::conv_360(float base, float min, float max) {
		float fVar0;
		if (min == max) return min;
		fVar0 = max - min;
		base -= std::round(base - min / fVar0) * fVar0;
		if (base < min) base += fVar0;
		return base;
	}
}