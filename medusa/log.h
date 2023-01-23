#pragma once
#include "pch.h"
namespace medusa {
	class logger {
	public:
		void init();
		void cleanup();

		void setup(const char* type, const char* message, va_list args);
		void log(const char* type, const char* message, ...);

		std::filesystem::path m_path{};
		std::ofstream m_file{};
		std::ofstream m_console{};

	}; inline logger g_logger;
}