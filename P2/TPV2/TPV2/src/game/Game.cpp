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
#include "../game/RunningState.h"
#include "../game/PausedState.h"
#include "../game/NewGameState.h"
#include "../game/NewRoundState.h"
#include "../game/GameOverState.h"

using ecs::Manager;

Game::Game() :
		mngr_(), //
		pacmanSys_(), //
		gameCtrlSys_(), //
		ghostSys_(), //
		renderSys_(), //
		collisionSys_(), //
		immunitySys_(), // 
		foodSys_(), //
		current_state_(nullptr), //
		paused_state_(nullptr), //
		running_state_(nullptr), //
		newgame_state_(nullptr), //
		newround_state_(nullptr), //
		gameover_state_(nullptr) {

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

	// add the states
	running_state_ = new RunningState(pacmanSys_, renderSys_, collisionSys_, ghostSys_, foodSys_, immunitySys_, gameCtrlSys_);
	paused_state_ = new PausedState();
	newgame_state_ = new NewGameState();
	newround_state_ = new NewRoundState();
	gameover_state_ = new GameOverState();

	current_state_ = newgame_state_;
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

		mngr_->refresh();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
		current_state_->update();
	}

}

