#pragma once
#include "option.h"
#include "render.h"
#include "char_mem_stream.h"
namespace medusa::ui {
	template <typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
	class number_option : public base_option<number_option<Type>> {
	private:
		Type* m_number = nullptr;
		Type m_min = 0;
		Type m_max = 1;
		Type m_step = 1;
		std::size_t m_precision = 3;
		using base = base_option<number_option<Type>>;
		using display_type = std::conditional_t<sizeof(Type) == 1, std::uint32_t, Type>;
	public:
		explicit number_option(const char* text) {
			base::set_left_text(text);
		}

		number_option& add_number(Type* number) {
			m_number = number;
			return *this;
		}

		number_option& add_min(Type min) {
			m_min = min;
			return *this;
		}

		number_option& add_max(Type max) {
			m_max = max;
			return *this;
		}

		number_option& add_step(Type step) {
			m_step = step;
			return *this;
		}

		number_option& add_precision(Type precision) {
			m_precision = precision;
			return *this;
		}

		const char* get_right_text() {
			MemoryStringStream stream(base::m_right_text);
			stream
				<< std::setprecision(m_precision)
				<< std::fixed
				<< static_cast<display_type>(*m_number);
			return base::get_right_text();
		}

		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::left_click) {
				if (*m_number - m_step < m_min)
					*m_number = m_max;
				else
					*m_number -= m_step;
				if (base::m_action)
					std::invoke(base::m_action);
			}
			else if (action == eOptionAction::right_click) {
				if (*m_number + m_step > m_max)
					*m_number = m_min;
				else
					*m_number += m_step;
				if (base::m_action)
					std::invoke(base::m_action);
			}
			base::handle_action(action);
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::number_option) {
				return true;
			}
			return base::get_flag(flag);
		}
	};
	
}
