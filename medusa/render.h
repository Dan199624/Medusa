#pragma once
#include "pch.h"
#include "abstract_submenu.h"
#include "fonts.h"
#include "vector.h"
#include "draw_helper.h"

namespace medusa::ui {
	class render {
	public:
		template <typename sub_type, typename ...TArgs>
		void new_sub(TArgs&&... args) {
			auto sub = std::make_unique<sub_type>(std::forward<TArgs>(args)...);
			if (m_submenu_stack.empty()) {
				m_submenu_stack.push(sub.get());
			}
			m_all_subs.push_back(std::move(sub));
		}

		void switch_to_submenu(std::uint32_t id) {
			for (auto&& sub : m_all_subs) {
				if (sub->get_id() == id) {
					m_submenu_stack.push(sub.get());
					return;
				}
			}
		}
		void init();
	public:
		bool m_opened{};
		bool m_toggled_on{};

		rage::fvector2 m_position = { 0.31f, 0.08f };
		float m_draw_base_y{};
		float m_width = 0.2f;

		std::size_t m_max_vis_options = 12;

		int m_delay = 150;
		int m_previous_tick = 0;
		std::int32_t m_open_delay = 200, m_back_delay = 300, m_enter_delay = 300, m_vertical_delay = 120, m_horizontal_delay = 120;
		bool m_open_key; bool m_back_key; bool m_enter_key; bool m_up_key; bool m_down_key;bool m_left_key; bool m_right_key;
		void reset_keys();
		void check_keys();
		void handle_keys();	

		float m_header_height = 0.08f, m_header_text_size = 0.8f;
		eFont m_header_font = eFont::Pricedown;

		float m_submenu_height = 0.032f, m_submenu_text_size = 0.282f, m_submenu_padding = 2.1f;
		eFont m_submenu_font = eFont::ChaletLondon;

		float m_option_height = 0.0315f, m_option_text_size = 0.3f, m_option_padding = 2.1f;
		eFont m_option_font = eFont::ChaletLondon;

		float m_footer_height = 0.03f, m_footer_sprite_size = 0.03f, m_footer_sprite_size_x = 0.028f;
		
		Color m_header_color = Color{ 86, 59, 236, 255 };
		Color m_header_text_color = Color{ 255, 255, 255, 255 };
		Color m_submenu_background_color = Color{ 0, 0, 0, 255 };
		Color m_submenu_text_color = Color{ 255, 255, 255, 255 };
		Color m_selected_text_color = Color{ 10, 10, 10, 255 };
		Color m_unselected_text_color = Color{ 255, 255, 255, 255 };
		Color m_selected_option_color = Color{ 255, 255, 255, 255 };
		Color m_unselected_option_color = Color{ 0, 0, 0, 160 };
		Color m_footer_color = Color{ 0, 0, 0, 255 };
		Color m_footer_sprite_color = Color{ 255, 255, 255, 255 };
		Color m_toggle_red = Color{ 180, 66, 76, 255 };
		Color m_toggle_green = Color{ 117, 168, 137, 255 };

		void draw_header();
		void draw_submenu(abstract_submenu* sub);
		void draw_option(abstract_option* option, bool selected);
		void draw_footer();
	private:
		std::vector<std::unique_ptr<abstract_submenu>> m_all_subs;
		std::stack<abstract_submenu*, std::vector<abstract_submenu*>> m_submenu_stack;
	}; inline render g_render;
}