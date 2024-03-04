#include "MissileUtils.h"

#include "../components/Follow.h"
#include "../components/Generations.h"
#include "../components/Image.h"
#include "../components/ShowAtOpossiteSide.h"
#include "../components/TowardsDestination.h"
#include "../components/Transform.h"
#include "..//components/RotationComponent.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

MissileUtils::MissileUtils() : 
rnd_(sdlutils().rand()), width_(sdlutils().width()), height_(
	sdlutils().height()) {
}

void MissileUtils::create_missile() {
	int velSize = rnd_.nextInt(1, 3);
	
	//side
	int x = 0, y = 0;
	int side = rnd_.nextInt(0, 4);

	switch (side) {
	case 0:
		y = sdlutils().height() - 20;
		x = 20;
		break;
	case 1:
		y = 20;
		x = 20;
		break;
	case 2:
		y = 20;
		x = sdlutils().width() - 20;
		break;
	case 3:
		y = sdlutils().height() - 20;
		x = sdlutils().width() - 20;
		break;
	default:
		break;
	}

	Vector2D p = Vector2D(x, y);
	Vector2D v = p.normalize() * (float)velSize;

	generateMissile(p, v);
}

void MissileUtils::generateMissile(const Vector2D& p, const Vector2D& v){
	auto mngr = Game::instance()->getMngr();

	auto m = mngr->addEntity(ecs::grp::MISSILES);
	mngr->addComponent<Transform>(m, p, v, 
		sdlutils().images().at("missile").width(), 
		sdlutils().images().at("missile").height(), 0.0);
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	mngr->addComponent<Follow>(m, fighterTR->getPos());

	mngr->addComponent<Image>(m, &sdlutils().images().at("missile"));
}

void MissileUtils::remove_all_missiles() {
	auto mngr = Game::instance()->getMngr();
	for (auto m : mngr->getEntities(ecs::grp::MISSILES)) {
		mngr->setAlive(m, false);
	}
	mngr->refresh();
}

