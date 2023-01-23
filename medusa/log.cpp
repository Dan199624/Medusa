#include "pch.h"
#include "log.h"
#include "util.h"

namespace medusa {
	void logger::init() {
		AllocConsole();
		SetConsoleTitleA("Medusa | Made By Scarface");

		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);

		m_console.open("CONOUT$");

		m_path.append(util::get_path());
		m_path.append("medusa");
		if (!std::filesystem::exists(m_path)) {
			std::filesystem::create_directory(m_path);
		}
		m_path.append("log.txt");

		m_file.open(m_path, std::ios_base::out | std::ios_base::trunc);
		m_file.clear();
	}

	void logger::cleanup() {
		fclose(stdout);
		FreeConsole();
		m_console.clear();
		m_path.clear();
		m_console.close();
		m_file.close();
	}

	void set_color(int color) {
		SetConsoleTextAttribute(GetStdHandle(-11), color);
	}

	void logger::log(const char* type, const char* message, ...) {
		va_list args{};
		va_start(args, message);
		setup(type, message, args);
		va_end(args);
	}

	void logger::setup(const char* type, const char* message, va_list args) {
		
		set_color(FOREGROUND_INTENSITY);

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		char tag[64] = {};
		snprintf(tag, sizeof(tag) - 1, "[%02d:%02d:%02d] %s | ", tm->tm_hour, tm->tm_min, tm->tm_sec, type);

		std::size_t log_size = std::vsnprintf(nullptr, 0, message, args) + 1;
		auto buffer = std::make_unique<char[]>(log_size);

		std::uninitialized_fill_n(buffer.get(), log_size, '\0');
		std::vsnprintf(buffer.get(), log_size, message, args);

		m_file << tag << buffer.get() << std::endl;
		m_console << tag << buffer.get() << std::endl;
	}
}