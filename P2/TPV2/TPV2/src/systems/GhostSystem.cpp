#include "GhostSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

GhostSystem::GhostSystem() :
	ghTR_(nullptr), //
	rnd_(sdlutils().rand()), //
	lastTimeGeneratedGhost_(), //
	lastTimeGotPacmanPos_(0) {

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
		lastTimeGotPacmanPos_ = 0;
	}
	
}

void GhostSystem::update(){
	auto ghosts = mngr_->getEntities(ecs::grp::GHOST);
	//cambio de direccion dependiendo del pacmany su posicion
	auto pacmanTr = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN));
	if (sdlutils().virtualTimer().currTime() > lastTimeGotPacmanPos_ + 2000) {
		for (auto g : ghosts) {
			calcVelFromPacman(g);
		}
		lastTimeGotPacmanPos_ = sdlutils().virtualTimer().currTime();
	}
	//cambiar animacion segun el movimiento del fantasma
	if (ghosts.size() > 0) {
		for (auto g : ghosts) {
			calculateAnimDirection(g);
		}
	}
	//generacion de fantasmas
	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedGhost_ + 5000) {
		if (ghosts.size() < 10) {
			addGhost();
		}
		lastTimeGeneratedGhost_ = sdlutils().virtualTimer().currTime();
	}
	// update de fantasmas
	for (auto g : ghosts) {
		mngr_->update(g);
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
	auto ghTR = mngr_->addComponent<Transform>(g);
	auto s = 50.0f;
	auto x2 = (sdlutils().width() - s) / 2.0f;
	auto y2 = (sdlutils().height() - s) / 2.0f;
	Vector2D p = Vector2D(x2, y2);


	ghTR->init(p, Vector2D(1.0f, 1.0f), s, s, 0.0f);

	mngr_->addComponent<ImageWithFrames>(g, &sdlutils().images().at("pacman"),
		0, 0, //
		0, 0, //
		128, 128, //
		0, 4, //
		2, 1,
		400
	);

}

void GhostSystem::calculateAnimDirection(ecs::entity_t g)
{
	auto tr = mngr_->getComponent<Transform>(g);
	auto iF = mngr_->getComponent<ImageWithFrames>(g);

	if (tr->vel_.getX() > 0) {
		iF->changeFrames(2);
	}
	else if (tr->vel_.getX() < 0) {
		iF->changeFrames(6);
	}
	else if (tr->vel_.getY() > 0) {
		iF->changeFrames(4);
	}
	else if (tr->vel_.getY() < 0) {
		iF->changeFrames(0);
	}
}

void GhostSystem::calcVelFromPacman(ecs::entity_t g)
{
	Vector2D endVel;
	auto pmTR = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN));
	auto gTR = mngr_->getComponent<Transform>(g);



	endVel = Vector2D(pmTR->pos_ - gTR->pos_).normalize();
	gTR->vel_ = endVel;
	/*std::cout << "PACMAN POS: " << pmTR->pos_.getX() << " " << pmTR->pos_.getY() << std::endl;
	std::cout << "GHOST VEL: " << gTR->vel_.getX() << " " << gTR->vel_.getY() << std::endl; */
}



