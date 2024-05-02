// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/HealthComponent.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
		pmTR_(nullptr), immunity(false) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	//
	auto pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	//mngr_->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));
	mngr_->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("pacman"),
		4, 1, //
		0, 0, //
		128, 128, //
		0, 0, //
		4, 1
	);

	mngr_->addComponent<HealthComponent>(pacman, 3);
}

void PacManSystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_NEW_GAME:
		mngr_->getComponent<HealthComponent>(mngr_->getHandler(ecs::hdlr::PACMAN))->setLifes(3);
		break;
	case _m_ROUND_START:
		immunity = false;
		resetPos();
		break;
	case _m_IMMUNITY_START:
		immunity = true;
		break;
	case _m_IMMUNITY_END:
		immunity = false;
		break;
	case _m_PACMAN_GHOST_COLLISION:
		if (immunity) {
			Message m;
			m.id = _m_ADD_SCORE;
			m.add_score.score = 200;
			mngr_->send(m);
		}
		else {
			checkDead();
		}
		break;

	default:
		break;
	}
}

void PacManSystem::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			pmTR_->rot_ = pmTR_->rot_ + 90.0f;

			// also rotate the PacMan so it looks in the same
			// direction where it moves
			//
			pmTR_->vel_ = pmTR_->vel_.rotate(90.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			pmTR_->rot_ = pmTR_->rot_ - 90.0f;

			// also rotate the PacMan so it looks in the same
			// direction where it moves
			//
			pmTR_->vel_ = pmTR_->vel_.rotate(-90.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

			pmTR_->vel_ = Vector2D(0.0f, -3.0f).rotate(pmTR_->rot_);
			sdlutils().musics().at("pacman_chomp").resumeMusic();
		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
			
			pmTR_->vel_ = Vector2D(0, 0).rotate(pmTR_->rot_);
			sdlutils().musics().at("pacman_chomp").pauseMusic();
		}

	}

	// move the pacman
	pmTR_->update();
	// check left/right borders
	if (pmTR_->pos_.getX() < 0) {
		pmTR_->pos_.setX(0.1f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getX() + pmTR_->width_ > sdlutils().width()) {
		pmTR_->pos_.setX(sdlutils().width() - pmTR_->width_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pmTR_->pos_.getY() < 0) {
		pmTR_->pos_.setY(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getY() + pmTR_->height_ > sdlutils().height()) {
		pmTR_->pos_.setY(sdlutils().height() - pmTR_->height_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

}

void PacManSystem::checkDead() {
	int &lifes = mngr_->getComponent<HealthComponent>(mngr_->getHandler(ecs::hdlr::PACMAN))->currLifes_;
	lifes--;
 	if (lifes > 0) {
		Message m;
		m.id = _m_ROUND_OVER;
		sdlutils().musics().at("pacman_chomp").pauseMusic();
		mngr_->send(m);
	}
	else {
		Message  m;
		m.id = _m_GAME_OVER;
		sdlutils().musics().at("pacman_chomp").pauseMusic();
		mngr_->send(m);
	}
}

void PacManSystem::resetPos() {
	auto x = (sdlutils().width() - 50) / 2.0f;
	auto y = (sdlutils().height() - 50) / 2.0f;
	pmTR_->pos_.set(x, y);

	pmTR_->vel_ = Vector2D(0.0f, 0.0f);
}