#pragma once
#include "option.h"
#include "render.h"

namespace medusa::ui {
	class toggle_option : public base_option<toggle_option> {
	private:
		bool* m_Bool = nullptr;
		bool m_DisplayInverted = false;
		std::function<void()> m_function;
	public:
		explicit toggle_option(const char* text) {
			base_option::set_left_text(text);
		}

		toggle_option& add_function(std::function<void()>&& function) {
			m_function = std::move(function);
			return *this;
		}

		toggle_option& add_toggle(bool* const b00l) {
			m_Bool = b00l;
			return *this;
		}

		toggle_option& add_display_inverted(const bool displayInverted) {
			m_DisplayInverted = displayInverted;
			return *this;
		}

		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::click) {
				*m_Bool = !*m_Bool;
			}
			base_option::handle_action(action);
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::toggle_option) {
				g_render.m_toggled_on = *m_Bool;
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}