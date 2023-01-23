#pragma once
#include "option.h"

namespace medusa::ui {
	class simple_option : public base_option<simple_option> {
	private:
		std::function<void()> m_function;
	public:
		explicit simple_option(const char* text) {
			set_left_text(text);
		}

		simple_option& add_right_text(const char* const text) {
			base_option::set_right_text(text);
			return *this;
		}

		simple_option& add_function(std::function<void()>&& function) {
			set_action(std::move(function));
			return *this;
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::simple_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}
