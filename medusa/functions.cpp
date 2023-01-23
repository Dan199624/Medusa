#include "pch.h"
#include "functions.h"
#include "fiber.h"
#include "player.h"
namespace medusa {
	//add functions you want to loop here
	void loop() {
		while (true) {
			g_player.loop();
			g_fibers.wait(&g_function_fiber);
		}
	}
	void functions::init() {
		g_fibers.add(&g_function_fiber, &loop);
	}
	void functions::cleanup() {
		g_fibers.remove(&g_function_fiber);
	}
}