// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "StarsSystem.h"

CollisionsSystem::CollisionsSystem() {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	// the PacMan's Transform
	//
	auto pm = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pTR = mngr_->getComponent<Transform>(pm);

	auto &gh = mngr_->getEntities(ecs::grp::GHOST);


	auto nG = gh.size();
	for (auto i = 0u; i < nG; i++) {
		auto g = gh[i];
		if (mngr_->isAlive(g)) {
			auto gTR = mngr_->getComponent<Transform>(g);

			if (Collisions::collides(
				pTR->pos_, pTR->width_, pTR->height_, //
				gTR->pos_, gTR->width_, gTR->height_)) {

				Message m;
				m.id = _m_PACMAN_GHOST_COLLISION;
				m.pacman_ghost.ghost = g;
				mngr_->send(m);
			}
		}
	}

	auto &fo = mngr_->getEntities(ecs::grp::FOOD);

	auto nF = fo.size();
	for (auto i = 0u; i < nF; i++) {
		auto f = fo[i];
		if (mngr_->isAlive(f)) {
			auto fTR = mngr_->getComponent<Transform>(f);
			if (Collisions::collides(
				pTR->pos_, pTR->width_, pTR->height_, //
				fTR->pos_, fTR->width_, fTR->height_)) {
				Message m;
				m.id = _m_PACMAN_FOOD_COLLISION;
				m.pacman_food.fruit = f;
				mngr_->send(m);
			}
			
		}
	}

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	//auto &stars = mngr_->getEntities(ecs::grp::STARS);
	//auto n = stars.size();
	//for (auto i = 0u; i < n; i++) {
	//	auto e = stars[i];
	//	if (mngr_->isAlive(e)) { // if the star is active (it might have died in this frame)

	//		// the Star's Transform
	//		//
	//		auto eTR = mngr_->getComponent<Transform>(e);

	//		// check if PacMan collides with the Star (i.e., eat it)
	//		if (Collisions::collides(			//
	//				pTR->pos_, pTR->width_, pTR->height_, //
	//				eTR->pos_, eTR->width_, eTR->height_)) {

	//			Message m;
	//			m.id = _m_STAR_EATEN;
	//			m.star_eaten_data.e = e;
	//			mngr_->send(m);

	//		}
	//	}
	//}
	
}

