#include "pch.h"
#include "menu.h"
#include "fiber.h"
#include "natives.h"
#include "log.h"

#include "joaat.h"

#include "render.h"
#include "sub.h"
#include "submenu_option.h"
#include "simple_option.h"
#include "toggle_option.h"
#include "number_option.h"
#include "scroll_option.h"

#include "player.h"

namespace medusa {
	void main_menu() {
		using namespace ui;
		
		g_render.new_sub<sub>("Home", "home"_j, [](sub* core) {

			core->add_option(submenu_option("Example Submenu")
				.add_target("example_submenu"_j));

			core->add_option(submenu_option("Settings")
				.add_target("settings"_j));

			core->add_option(simple_option("Unload")
				.add_function([] { g_running = false; }));
		});
		g_render.new_sub<sub>("Settings", "settings"_j, [](sub* core) {

			core->add_option(number_option<float>("X")
				.add_number(&g_render.m_position.x).add_min(0.f).add_max(10.f)
				.add_step(0.01).add_precision(2));

			core->add_option(number_option<float>("Y")
				.add_number(&g_render.m_position.y).add_min(0.f).add_max(10.f)
				.add_step(0.01).add_precision(2));
		});

		g_render.new_sub<sub>("Example Submenu", "example_submenu"_j, [](sub* core) {
			static int test_int{ 1 };
			static float test_float{ 1.f };

			core->add_option(toggle_option("Godmode")
				.add_toggle(&g_player.m_godmode));

			core->add_option(toggle_option("Super Jump")
				.add_toggle(&g_player.m_super_jump));

			core->add_option(number_option<int>("Number Option Int")
				.add_number(&test_int).add_min(0).add_max(10));

			core->add_option(number_option<float>("Number Option Float")
				.add_number(&test_float).add_min(0.f).add_max(10.f).add_precision(1));

			core->add_option(scroll_option<const char*, std::size_t>("Scroll Option"));

			core->add_option(simple_option("Log Hello")
				.add_function([] { g_logger.log("Log", "Hello"); }));
		});
	}

	void menu_script() {
		while (true) {
			main_menu();
			ui::g_render.init();
			g_fibers.wait(&g_main_fiber);
		}
	}

	void menu::init() {
		g_fibers.add(&g_main_fiber, &menu_script);
	}

	void menu::cleanup() {
		g_fibers.remove(&g_main_fiber);
	}
}