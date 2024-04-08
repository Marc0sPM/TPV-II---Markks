// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameOverState.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
GameOverState::GameOverState() :
		msg_(nullptr), dest_(), ihdlr(ih()), mngr_() {
}

GameOverState::~GameOverState() {
}

void GameOverState::leave() {
}

void GameOverState::update() {
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
		Game::instance()->setState(Game::NEWGAME);
	}
	sdlutils().clearRenderer();
	msg_->render(dest_);
	sdlutils().presentRenderer();
}

void GameOverState::enter() {
	auto mngr_ = Game::instance()->getMngr();
	if (mngr_->getEntities(ecs::grp::FOOD).size() > 0) {
		msg_ = &sdlutils().msgs().at("gameover_lost");
		sdlutils().soundEffects().at("pacman_death").play();
	}
	else {
		msg_ = &sdlutils().msgs().at("gameover_won");
		sdlutils().soundEffects().at("pacman_won").play();
	}

	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());
}
