#pragma once
#include "vector.h"
#include "fonts.h"
#include "justify.h"

#pragma pack(push, 1)
struct Color
{
	std::uint8_t r{ 255 };
	std::uint8_t g{ 255 };
	std::uint8_t b{ 255 };
	std::uint8_t a{ 255 };
};
#pragma pack(pop)

namespace medusa::draw_helper {
	void draw_left_text(const char* text, float x, float y, float size, eFont font, Color color, bool outline, bool shadow);
	void draw_centered_text(const char* text, float x, float y, float size, eFont font, Color color, bool outline, bool shadow);
	void draw_right_text(const char* text, float x, float y, float size, eFont font, Color color, bool outline, bool shadow);
	float get_text_height(eFont font, float size);
	void draw_rect(rage::fvector2 pos, float width, float height, Color color);
	void draw_sprite(const char* dict, const char* texture, rage::fvector2 pos, float width, float height, Color color, float rotation);
	rage::fvector2 get_sprite_scale(float size);
	void draw_glare();
}