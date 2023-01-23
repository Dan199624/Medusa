#pragma once

enum class eOptionFlag {
	indicator = (1 << 0),
	toggle_option = (1 << 1),
	scroll_option = (1 << 2),
	number_option = (1 << 3),
	simple_option = (1 << 4)
};