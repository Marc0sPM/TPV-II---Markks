// This file is part of the course TPV2@UCM - Samir Genaim

#include "BlackHoleUtils.h"

#include "../components/Follow.h"
#include "../components/Generations.h"
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/ShowAtOpossiteSide.h"
#include "../components/TowardsDestination.h"
#include "../components/Transform.h"
#include "..//components/RotationComponent.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"


BlackHoleUtils::BlackHoleUtils() :
	rand_(sdlutils().rand()), width_(sdlutils().width()), height_(
		sdlutils().height()) {
}

BlackHoleUtils::~BlackHoleUtils() {
}

void BlackHoleUtils::remove_all_blackholes() {
	auto mngr = Game::instance()->getMngr();
	for (auto e : mngr->getEntities(ecs::grp::BLACKHOLES)) {
		mngr->setAlive(e, false);
	}
	mngr->refresh();
}

void BlackHoleUtils::create_blackholes(int n) {

	int radio = rand_.nextInt(100, 300);

	for (int i = 0; i < n; i++) {

		int y = 0, x = 0;
		
		x = cos(rotation_) * radio;
		y = sin(rotation_) * radio;
		
		rotation_ += 360 / 6;
		Vector2D p = Vector2D(x, y);
		
		generateBlackHole(p);

	}

}

void BlackHoleUtils::generateBlackHole(const Vector2D& p) {

	auto mngr = Game::instance()->getMngr();

	int size = rand_.nextInt(30, 60);
	auto b = mngr->addEntity(ecs::grp::BLACKHOLES);

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	Vector2D position = p + fighterTR->getPos();

	mngr->addComponent<Transform>(b, position, Vector2D(0,0), size, size, 0);
	mngr->addComponent<RotationComponent>(b);
	mngr->addComponent<Image>(b, //
		&sdlutils().images().at("black-hole"));
}

