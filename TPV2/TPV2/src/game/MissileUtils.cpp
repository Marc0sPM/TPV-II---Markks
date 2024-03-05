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
	int velSize = rnd_.nextInt(1, 4);
	
	//side
	int x = 0, y = 0;
	int side = rnd_.nextInt(0, 4);
	//La direccion de la velocidad depende de la esquina en la que "spawnee" el misil
	Vector2D v = Vector2D();
	switch (side) {
	case 0:
		x = 15;
		y = sdlutils().height() - 40;
		v = { sqrtf(velSize),-sqrtf(velSize) };
		break;
	case 1:
		x = 0;
		y = 0;
		v = { sqrtf(velSize),sqrtf(velSize) };
		break;
	case 2:
		x = sdlutils().width() - 30 ;
		y = 0;
		v = { -sqrtf(velSize),sqrtf(velSize) };
		break;
	case 3:
		x = sdlutils().width() - 30;
		y = sdlutils().height() - 30;
		v = { -sqrtf(velSize),-sqrtf(velSize)};
		break;
	default:
		break;
	}

	Vector2D p = Vector2D(x, y);


	generateMissile(p, v);
}

void MissileUtils::generateMissile(const Vector2D& p, const Vector2D& v){
	auto mngr = Game::instance()->getMngr();

	auto m = mngr->addEntity(ecs::grp::MISSILES);
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto fighterTr = mngr->getComponent<Transform>(fighter);
	auto mTr = mngr->addComponent<Transform>(m, p, v, 30,30 , 0.0f);

	mngr->addComponent<Follow>(m, fighterTr->getPos());
	mngr->addComponent<Image>(m, &sdlutils().images().at("missile"));

}

void MissileUtils::remove_all_missiles() {
	auto mngr = Game::instance()->getMngr();
	for (auto m : mngr->getEntities(ecs::grp::MISSILES)) {
		mngr->setAlive(m, false);
	}
	mngr->refresh();
}

