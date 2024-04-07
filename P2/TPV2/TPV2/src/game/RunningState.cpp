// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

#include "Game.h"

RunningState::RunningState() :
	ihdlr(ih()), //
	mngr_(), //
	pacmanSys_(), //
	gameCtrlSys_(), //
	ghostSys_(), //
	renderSys_(), //
	collisionSys_(), //
	immunitySys_(), // 
	foodSys_() {
}

RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {
	pacmanSys_->update();
	ghostSys_->update();
	renderSys_->update();
	collisionSys_->update();
	immunitySys_->update();
	foodSys_->update();
	gameCtrlSys_->update();
	
}

void RunningState::enter() {
	
}


