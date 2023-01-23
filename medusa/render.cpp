#include "pch.h"
#include "render.h"
#include "natives.h"
#include "draw_helper.h"
#include "util.h"
#include "vector.h"
#include "timer.h"

namespace medusa {
	void ui::render::init() {
		check_keys();
		handle_keys();
		if (m_opened) {
			PAD::DISABLE_CONTROL_ACTION(0, 27, true);
			m_draw_base_y = m_position.y;
			if (!m_submenu_stack.empty()) {
				auto sub = m_submenu_stack.top();
				sub->reset();
				sub->execute();
				draw_header();
				draw_submenu(sub);	
				if (sub->get_options_size() != 0) {
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->get_options_size() > m_max_vis_options ? m_max_vis_options : sub->get_options_size();
					if (sub->get_options_size() >m_max_vis_options && sub->get_selected_option() >= m_max_vis_options) {
						startPoint = sub->get_selected_option() - m_max_vis_options + 1;
						endPoint = sub->get_selected_option() + 1;
					}
					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j) {
						draw_option(sub->get_option(i), i == sub->get_selected_option());
					}
				}
			}
			draw_footer();
		}
	}
	void ui::render::reset_keys() {
		m_open_key = false, m_back_key = false, m_enter_key = false, m_up_key = false; m_down_key = false,
			m_left_key = false, m_right_key = false;
	}
	void ui::render::check_keys() {
		reset_keys();
		m_open_key = util::is_key_pressed(VK_F4), m_back_key = util::is_key_pressed(VK_BACK), m_enter_key = util::is_key_pressed(VK_RETURN),
			m_up_key = util::is_key_pressed(VK_UP), m_down_key = util::is_key_pressed(VK_DOWN), m_left_key = util::is_key_pressed(VK_LEFT),
			m_right_key = util::is_key_pressed(VK_RIGHT);
	}
	void ui::render::handle_keys() {
		static auto open_timer = GetTickCount();
		if (g_render.m_open_key && GetTickCount() - open_timer >= static_cast<std::uint32_t>(m_open_delay)) {
			open_timer = GetTickCount();
			g_render.m_opened ^= true;
		}
		static Timer backTimer(0ms);
		backTimer.SetDelay(std::chrono::milliseconds(m_back_delay));
		if (g_render.m_opened && g_render.m_back_key && backTimer.Update()) {
			if (m_submenu_stack.size() <= 1) {
				g_render.m_opened = false;
			}
			else {
				m_submenu_stack.pop();
			}
		}
		if (g_render.m_opened && !m_submenu_stack.empty()) {
			auto sub = m_submenu_stack.top();
			static Timer enterTimer(0ms);
			enterTimer.SetDelay(std::chrono::milliseconds(m_enter_delay));
			if (g_render.m_enter_key && sub->get_options_size() != 0 && enterTimer.Update()) {
				if (auto opt = sub->get_option(sub->get_selected_option())) {
					opt->handle_action(eOptionAction::click);
				}
			}
			static Timer upTimer(0ms);
			upTimer.SetDelay(std::chrono::milliseconds(m_vertical_delay));
			if (g_render.m_up_key && sub->get_options_size() != 0 && upTimer.Update()) {
				sub->scroll_backward();
			}
			static Timer downTimer(0ms);
			downTimer.SetDelay(std::chrono::milliseconds(m_vertical_delay));
			if (g_render.m_down_key && sub->get_options_size() != 0 && downTimer.Update()) {
				sub->scroll_forward();
			}
			static Timer leftTimer(0ms);
			leftTimer.SetDelay(std::chrono::milliseconds(m_horizontal_delay));
			if (g_render.m_left_key && sub->get_options_size() != 0 && leftTimer.Update()) {
				if (auto opt = sub->get_option(sub->get_selected_option())) {
					opt->handle_action(eOptionAction::left_click);
				}
			}
			static Timer rightTimer(0ms);
			rightTimer.SetDelay(std::chrono::milliseconds(m_horizontal_delay));
			if (g_render.m_right_key && sub->get_options_size() != 0 && rightTimer.Update()) {			
				if (auto opt = sub->get_option(sub->get_selected_option())) {
					opt->handle_action(eOptionAction::right_click);
				}
			}
		}
	}
	void ui::render::draw_header() {
		draw_helper::draw_rect({ m_position.x, m_draw_base_y + (m_header_height / 2.f)}, m_width, m_header_height, m_header_color);
		draw_helper::draw_centered_text("medusa", m_position.x, m_draw_base_y + (m_header_height / 2.f)
			- (draw_helper::get_text_height(m_header_font, m_header_text_size) / 2.f),
			m_header_text_size, m_header_font, m_header_text_color, true, true);
		draw_helper::draw_glare();
		m_draw_base_y += m_header_height;
	}
	void ui::render::draw_submenu(abstract_submenu* sub) {
		draw_helper::draw_rect({ m_position.x, m_draw_base_y + (m_submenu_height / 2.f) },
			m_width, m_submenu_height, m_submenu_background_color);

		char left_text[64] = {};
		std::strncpy(&left_text[0], sub->get_name(), sizeof(left_text) - 1);
		std::transform(std::begin(left_text), std::end(left_text), std::begin(left_text), [](char c) { return static_cast<char>(c); });
		draw_helper::draw_left_text(&left_text[0], m_position.x - (m_width / m_submenu_padding),
			m_draw_base_y + (m_submenu_height / 2.f) - (draw_helper::get_text_height(m_submenu_font, m_submenu_text_size) / 1.5f),
			m_submenu_text_size, m_submenu_font, m_submenu_text_color, false, true);

		char right_text[32] = {};
		std::snprintf(right_text, sizeof(right_text) - 1, "%zu / %zu", sub->get_selected_option() + 1, sub->get_options_size());
		draw_helper::draw_right_text(&right_text[0], m_position.x + (m_width / m_submenu_padding),
			m_draw_base_y + (m_submenu_height / 2.f) - (draw_helper::get_text_height(m_submenu_font, m_submenu_text_size) / 1.5f),
			m_submenu_text_size, m_submenu_font, m_submenu_text_color, false, true);
		m_draw_base_y += m_submenu_height;
	}
	void ui::render::draw_option(abstract_option* option, bool selected) {
		draw_helper::draw_left_text(option->get_left_text(), m_position.x - (m_width / m_option_padding),
			m_draw_base_y + (m_option_height / 2.f)
			- (draw_helper::get_text_height(m_option_font, m_option_text_size) / 1.5f),
			m_option_text_size, m_option_font, selected ? m_selected_text_color
			: m_unselected_text_color, false, false);

		draw_helper::draw_rect({ m_position.x, m_draw_base_y + (m_option_height / 2.f) }, m_width, m_option_height,
			selected ? m_selected_option_color : m_unselected_option_color);

		if (option->get_flag(eOptionFlag::indicator)) {
			draw_helper::draw_right_text(">", m_position.x + (m_width / m_option_padding), m_draw_base_y + (m_option_height / 2.f)
				- (draw_helper::get_text_height(eFont::Monospace, 0.35) / 1.725f), 0.35, eFont::Monospace,
				selected ? m_selected_text_color : m_unselected_text_color, false, false);
		}
		else if (option->get_flag(eOptionFlag::toggle_option)) {
			auto size = draw_helper::get_sprite_scale(0.032);
			if (m_toggled_on) {
				draw_helper::draw_sprite("commonmenu", "common_medal", { m_position.x + (m_width / m_option_padding - 0.0045f),
					m_draw_base_y + (m_option_height / 2.f), }, size.x, size.y, m_toggle_green, 0.0f);
			}
			else {
				draw_helper::draw_sprite("commonmenu", "common_medal", { m_position.x + (m_width / m_option_padding - 0.0045f),
					m_draw_base_y + (m_option_height / 2.f), }, size.x, size.y, m_toggle_red, 0.0f);
			}
		}
		else if (option->get_flag(eOptionFlag::number_option)) {
			draw_helper::draw_right_text(option->get_right_text(), m_position.x + (m_width / m_option_padding),
				m_draw_base_y + (m_option_height / 2.f) - (draw_helper::get_text_height(m_option_font, m_option_text_size) / 1.5f) - 0.00007,
				m_option_text_size, m_option_font, selected ? m_selected_text_color : m_unselected_text_color, false, false);
		}
		else if (option->get_flag(eOptionFlag::scroll_option)) {
			draw_helper::draw_right_text(option->get_right_text(), m_position.x + (m_width / m_option_padding),
				m_draw_base_y + (m_option_height / 2.f) - (draw_helper::get_text_height(m_option_font, m_option_text_size) / 2) - 0.003,
				m_option_text_size, m_option_font, selected ? m_selected_text_color : m_unselected_text_color, false, false);
		}
		m_draw_base_y += m_option_height;
	}
	void ui::render::draw_footer() {
		draw_helper::draw_rect({ m_position.x, m_draw_base_y + (m_footer_height / 2.f) }, m_width, m_footer_height, m_footer_color);
		float size = m_footer_sprite_size;
		auto _size = draw_helper::get_sprite_scale(size);
		draw_helper::draw_sprite("commonmenu", "shop_arrows_upanddown", { m_position.x, m_draw_base_y + (m_footer_height / 2.f) }, _size.x, _size.y, m_footer_sprite_color, 0);
		m_draw_base_y += m_footer_height;
	}
}