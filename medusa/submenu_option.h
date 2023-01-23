#pragma once
#include "option.h"
#include "render.h"

namespace medusa::ui {
	class submenu_option : public base_option<submenu_option> {
	private:
		std::uint32_t m_sub_id{};
	public:
		explicit submenu_option(const char* text) {
			set_left_text(text);
		}	

		submenu_option& add_function(std::function<void()>&& function) {
			set_action(std::move(function));
			return *this;
		}

		submenu_option& add_target(const uint32_t id) {
			m_sub_id = id;
			return *this;
		}

		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::click) {
				g_render.switch_to_submenu(m_sub_id);
			}
			base_option::handle_action(action);
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::indicator) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}