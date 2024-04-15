// This file is part of the course TPV2@UCM - Samir Genaim

#include "NewGameState.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

NewGameState::NewGameState() :
		msg_(sdlutils().msgs().at("newgame")), //
		ihdlr(ih()), mngr_() {
	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

NewGameState::~NewGameState() {
}

void NewGameState::leave() {
	
}

void NewGameState::update() {
	auto mngr = Game::instance()->getMngr();
	if (ihdlr.keyDownEvent()) {
		Message m;
		m.id = _m_NEW_GAME;
		mngr->send(m);
		Game::instance()->setState(Game::NEWROUND);
	}
	sdlutils().clearRenderer();
	msg_.render(dest_);
	sdlutils().presentRenderer();
}

void NewGameState::enter() {
	sdlutils().musics().at("pacman_intro").play();
}
