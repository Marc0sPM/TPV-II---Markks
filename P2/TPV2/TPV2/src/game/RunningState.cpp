// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"

#include "Game.h"

RunningState::RunningState( ecs::System* pacmanSys, ecs::System* renderSys, ecs::System* collisionSys, ecs::System* ghostSys, ecs::System* foodSys,
	ecs::System* immunitySys, ecs::System* gameCtrlSys) :
	ihdlr(ih()), //
	mngr_(), //
	pacmanSys_(pacmanSys), //
	gameCtrlSys_(gameCtrlSys), //
	ghostSys_(ghostSys), //
	renderSys_(renderSys), //
	collisionSys_(collisionSys), //
	immunitySys_(immunitySys), // 
	foodSys_(foodSys) {
}

RunningState::~RunningState() {
}

void RunningState::leave() {
	sdlutils().soundEffects().at("pacman_death").play();
}

void RunningState::update() {
	pacmanSys_->update();
	ghostSys_->update();
	collisionSys_->update();
	immunitySys_->update();
	foodSys_->update();
	gameCtrlSys_->update();
	sdlutils().clearRenderer();
	renderSys_->update();
	sdlutils().presentRenderer();

	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
	}
}

void RunningState::enter() {
	sdlutils().musics().at("pacman_chomp").play();
	sdlutils().musics().at("pacman_chomp").pauseMusic();
}