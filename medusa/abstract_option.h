#pragma once
#include "pch.h"
#include "option_action.h"
#include "option_flag.h"

namespace medusa::ui {
	class abstract_option {
	public:
		virtual const char* get_left_text() = 0;
		virtual const char* get_right_text() = 0;
		virtual void handle_action(eOptionAction action) = 0;
		virtual void set_value(double text) = 0;
		virtual void set_value(std::string text) = 0;
		virtual bool get_flag(eOptionFlag flag) = 0;
		virtual std::function<void()> get_action() = 0;
	};
}