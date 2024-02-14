// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

//#include "../components/BounceOnBorders.h"
#include "../components/GameInfoMsgs.h"
#include "../components/GameState.h"
#include "../components/Image.h"
//#include "../components/PaddleAICtrl.h"
//#include "../components/PaddleKBCtrl.h"
//#include "../components/PaddleMouseCtrl.h"
//#include "../components/RectangleViewer.h"
//#include "../components/StopOnBorders.h"
#include "../components/DeAcceleration.h"
#include "../components/Health.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using ecs::Manager;

Game::Game() :
		mngr_(nullptr), //
		gameState_(nullptr), //
		fighterTr_(nullptr){
}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// Initialize the SDLUtils singleton
	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json");

	/*-----------------------

		CAMBIAR LA CONFIG DE RESOURCES A ASTEROID

	-----------------------*/

	sdlutils().hideCursor();

	// Create the manager
	mngr_ = new Manager();

	// create the fighter entity
	auto fighter = mngr_->addEntity();


	
	mngr_->setHandler(ecs::hdlr::FIGHTER, fighter);

	fighterTr_ = mngr_->addComponent<Transform>(fighter);

	auto fighterSize = 50.0f;	
	auto fighterX = (sdlutils().width() - fighterSize) / 2.0f;
	auto fighterY = (sdlutils().height() - fighterSize) / 2.0f;
	
	fighterTr_->init(Vector2D(fighterX, fighterY), Vector2D(0.0f, -2.0f), fighterSize, fighterSize, 0.0f);
	mngr_->addComponent<Image>(fighter, &sdlutils().images().at("fighter"));
	mngr_->addComponent<DeAcceleration>(fighter);
	mngr_->addComponent<Health>(fighter);


	
	// create game control entity
	auto gameCtrl = mngr_->addEntity();
	gameState_ = mngr_->addComponent<GameState>(gameCtrl);
	mngr_->addComponent<GameInfoMsgs>(gameCtrl);

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

		mngr_->update();
		mngr_->refresh();

		checkCollisions();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::checkCollisions() {
	//if (gameState_->getState() != GameState::RUNNING)
	//	return;

	//bool ballCollidesWithPaddle = false;

	//auto &ballPos = ballTr_->getPos();
	//auto ballWidth = ballTr_->getWidth();
	//auto ballHeight = ballTr_->getHeight();

	//for (auto e : mngr_->getEntities(ecs::grp::PADDLES)) {
	//	auto paddleTr_ = mngr_->getComponent<Transform>(e);
	//	ballCollidesWithPaddle = Collisions::collides(paddleTr_->getPos(),
	//			paddleTr_->getWidth(), paddleTr_->getHeight(), ballPos,
	//			ballWidth, ballHeight);

	//	if (ballCollidesWithPaddle)
	//		break;
	//}

	//if (ballCollidesWithPaddle) {

	//	// change the direction of the ball, and increment the speed
	//	auto &vel = ballTr_->getVel(); // the use of & is important, so the changes goes directly to the ball
	//	vel.setX(-vel.getX());
	//	vel = vel * 1.2f;

	//	// play some sound
	//	sdlutils().soundEffects().at("paddle_hit").play();
	//} else if (ballTr_->getPos().getX() < 0)
	//	gameState_->onBallExit(GameState::LEFT);
	//else if (ballTr_->getPos().getX() + ballTr_->getWidth()
	//		> sdlutils().width())
	//	gameState_->onBallExit(GameState::RIGHT);

}
