// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameState.h"

class InputHandler;

class RunningState: public GameState {
public:
	RunningState(ecs::System* pacmanSys, ecs::System* renderSys, ecs::System* collisionSys, ecs::System* ghostSys, ecs::System* foodSys,
		ecs::System* immunitySys, ecs::System* gameCtrlSys);
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	
private:
	ecs::Manager* mngr_;
	ecs::System* pacmanSys_;
	ecs::System* gameCtrlSys_;
	ecs::System* ghostSys_;
	ecs::System* renderSys_;
	ecs::System* collisionSys_;
	ecs::System* foodSys_;
	ecs::System* immunitySys_;
	InputHandler &ihdlr;

};

