#include "pch.h"
#include "player.h"
#include "natives.h"

namespace medusa {
	//this is an example on how to add features
	void player::loop() {
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), m_godmode);	
	}
}