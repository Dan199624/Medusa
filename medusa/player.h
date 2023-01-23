#pragma once

namespace medusa {
	class player {
	public:
		void loop();
		bool m_godmode;
		bool m_super_jump;
	}; inline player g_player;
}