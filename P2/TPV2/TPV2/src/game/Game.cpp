// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../systems/FoodSystem.h"

using ecs::Manager;

Game::Game() :
		mngr_(), //
		pacmanSys_(), //
		gameCtrlSys_(), //
		ghostSys_(), //
		renderSys_(), //
		collisionSys_(), //
		immunitySys_(), // 
		foodSys_() {

}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/resources.json");

	// Create the manager
	mngr_ = new Manager();


	// add the systems
	pacmanSys_ = mngr_->addSystem<PacManSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
	collisionSys_ = mngr_->addSystem<CollisionsSystem>();
	ghostSys_ = mngr_->addSystem<GhostSystem>();
	foodSys_ = mngr_->addSystem<FoodSystem>();
	immunitySys_ = mngr_->addSystem<ImmunitySystem>();
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}


		pacmanSys_->update();
		gameCtrlSys_->update();
		collisionSys_->update();
		ghostSys_->update();
		foodSys_->update();
		immunitySys_->update();

		mngr_->refresh();

		sdlutils().clearRenderer();
		renderSys_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

