// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../components/Points.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
GameCtrlSystem::GameCtrlSystem() :
		score_() {
	// TODO Auto-generated constructor stub

}

GameCtrlSystem::~GameCtrlSystem() {
	// TODO Auto-generated destructor stub
}

void GameCtrlSystem::initSystem() {
}

void GameCtrlSystem::update() {
	auto &ihldr = ih();
	
}

void GameCtrlSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_PACMAN_FOOD_COLLISION:
		incrScore(50);
		break;
	default:
		break;
	}
}
