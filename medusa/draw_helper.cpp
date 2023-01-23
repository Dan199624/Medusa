#include "pch.h"
#include "draw_helper.h"
#include "natives.h"
#include "util.h"
#include "render.h"
namespace medusa {
	void draw_helper::draw_left_text(const char* text, float x, float y, float size, eFont font, Color color, bool outline, bool shadow) {
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
	}
	void draw_helper::draw_centered_text(const char* text, float x, float y, float size, eFont font, Color color, bool outline, bool shadow) {
		HUD::SET_TEXT_CENTRE(true);
		draw_left_text(text, x, y, size, font, color, outline, shadow);
	}
	void draw_helper::draw_right_text(const char* text, float x, float y, float size, eFont font, Color color, bool outline, bool shadow) {
		HUD::SET_TEXT_WRAP(0.f, x);
		HUD::SET_TEXT_RIGHT_JUSTIFY(true);
		draw_left_text(text, x, y, size, font, color, outline, shadow);
	}
	float draw_helper::get_text_height(eFont font, float size) {
		return HUD::GET_RENDERED_CHARACTER_HEIGHT(size, static_cast<int>(font));
	}
	void draw_helper::draw_rect(rage::fvector2 pos, float width, float height, Color color) {
		GRAPHICS::DRAW_RECT(pos.x, pos.y, width, height, color.r, color.g, color.b, color.a, 0);
	}
	void draw_helper::draw_sprite(const char* dict, const char* texture, rage::fvector2 pos, float width, float height, Color color, float rotation) {
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict)) {
			GRAPHICS::DRAW_SPRITE(dict, texture, pos.x, pos.y, width, height, rotation, color.r, color.g, color.b, color.a, 0, 0);
		}
		else {
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
		}
	}
	rage::fvector2 draw_helper::get_sprite_scale(float size) {
		int x, y;
		GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&x, &y);
		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}
	void draw_helper::draw_glare() {
		int handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		float dir = util::conv_360(rot.z, 0, 360);
		static float _dir;
		if ((_dir == 0 || _dir - dir > 0.5) || _dir - dir < -0.5) {
			_dir = dir;
			GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(handle, "SET_DATA_SLOT");
			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(_dir);
			GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		}
		GRAPHICS::DRAW_SCALEFORM_MOVIE(handle, ui::g_render.m_position.x + 0.2865f, ui::g_render.m_draw_base_y + (ui::g_render.m_header_height / 2.f + 0.38f), 
			ui::g_render.m_width + 0.62700f, ui::g_render.m_header_height + 0.852f, 255, 255, 255, 255, 0);
	}
}