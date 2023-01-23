#pragma once
#include "pch.h"
#include "abstract_option.h"

namespace medusa::ui {
	class abstract_submenu {
	public:
		virtual const char* get_name() = 0;
		virtual std::uint32_t get_id() = 0;
		virtual void execute() = 0;
		virtual void reset() = 0;

		virtual abstract_option* get_option(std::size_t i) = 0;
		virtual std::size_t get_options_size() = 0;
		virtual std::size_t get_selected_option() = 0;
		virtual void set_selected_option(std::size_t) = 0;

		void scroll_forward() {
			if (get_selected_option() < get_options_size() - 1)
				set_selected_option(get_selected_option() + 1);
			else
				set_selected_option(0);
		}
		void scroll_backward() {
			if (get_selected_option() > 0)
				set_selected_option(get_selected_option() - 1);
			else
				set_selected_option(get_options_size() - 1);
		}
	};
}
