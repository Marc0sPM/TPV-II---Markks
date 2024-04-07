// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/ecs.h"


class GameState {
public:

	GameState() {
	}

	virtual ~GameState() {
	}

	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;
private:
	ecs::Manager* mngr_;
	ecs::System* pacmanSys_;
	ecs::System* gameCtrlSys_;
	ecs::System* ghostSys_;
	ecs::System* renderSys_;
	ecs::System* collisionSys_;
	ecs::System* foodSys_;
	ecs::System* immunitySys_;
};
