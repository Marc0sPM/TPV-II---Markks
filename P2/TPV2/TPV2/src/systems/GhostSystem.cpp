#include "GhostSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem() :
	ghTR_(nullptr), rnd_(sdlutils().rand()), lastTimeGeneratedGhost_() {

}

GhostSystem::~GhostSystem(){
}

void GhostSystem::initSystem(){

}

void GhostSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_ROUND_START:
		lastTimeGeneratedGhost_ = 0;
	}
	
}

void GhostSystem::update(){
	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedGhost_ + 000) {
		// create ghost
		
		auto ghost = mngr_->getEntities(ecs::grp::GHOST);
		if (ghost.size() < 10) {
			addGhost();
		}
		
		
	}
}

void GhostSystem::addGhost()
{
	//side
	int x = 0, y = 0;
	int side = rnd_.nextInt(0, 4);

	switch (side) {
	case 0:
		x = 15;
		y = sdlutils().height() - 40;
		break;
	case 1:
		x = 0;
		y = 0;
		break;
	case 2:
		x = sdlutils().width() - 30;
		y = 0;
		break;
	case 3:
		x = sdlutils().width() - 30;
		y = sdlutils().height() - 30;
		break;
	default:
		break;
	}
	

	auto g = mngr_->addEntity(ecs::grp::GHOST);
	ghTR_ = mngr_->addComponent<Transform>(g);
	auto s = 50.0f;
	auto x2 = (sdlutils().width() - s) / 2.0f;
	auto y2 = (sdlutils().height() - s) / 2.0f;
	Vector2D p = Vector2D(x2, y2);


	ghTR_->init(p, Vector2D(), s, s, 0.0f);

	mngr_->addComponent<ImageWithFrames>(g, &sdlutils().images().at("pacman"),
		0, 0, //
		0, 0, //
		128, 128, //
		1, 4, //
		1, 1
	);

}
