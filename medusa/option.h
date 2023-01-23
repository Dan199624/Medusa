#pragma once
#include "pch.h"
#include "abstract_option.h"

namespace medusa::ui {
	template <typename T>
	class base_option : public abstract_option {
	public:
		const char* get_left_text() override {
			return &m_left_text[0];
		}
		const char* get_right_text() override {
			return &m_right_text[0];
		}
		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::click) {
				if (m_action) {
					std::invoke(m_action);
				}
			}
		}
		bool get_flag(eOptionFlag) override {
			return false;
		}
		std::function<void()> get_action() override {
			return m_action;
		}

		void set_value(double text) override {}
		void set_value(std::string text) {}

		T& set_left_text(const char* text) {
			std::strncpy(&m_left_text[0], text, sizeof(m_left_text) - 1);
			return static_cast<T&>(*this);
		}
		T& set_right_text(const char* text) {
			std::strncpy(&m_right_text[0], text, sizeof(m_right_text) - 1);
			return static_cast<T&>(*this);
		}
		T& set_action(std::function<void()> action) {
			m_action = std::move(action);
			return static_cast<T&>(*this);
		}

	protected:
		std::function<void()> m_action;
		char m_left_text[64] = {};
		char m_right_text[64] = {};
	};
}
