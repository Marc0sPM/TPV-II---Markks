#include "FoodSystem.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"
#include "../components/MiracleFruit.h"

FoodSystem::FoodSystem(int fRows, int fCols) :
	fRows_(fRows), //
	fCols_(fCols),  //
	rnd_(sdlutils().rand())
{}

void FoodSystem::initSystem()
{

}
 
void FoodSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_NEW_GAME: 
		removeAllFruits();
		setFruits();
		break;
	case _m_ROUND_START:
		resetMiracleFruits();
		break;
	case _m_PACMAN_FOOD_COLLISION:
		checkTypeFruit(m.pacman_food.fruit);
		removeFruit(m.pacman_food.fruit);
		break;
	}
}

void FoodSystem::update()
{
	auto fruits = mngr_->getEntities(ecs::grp::FOOD);

	for (auto& f : fruits) {
		mngr_->update(f);
	}

	if (fruits.size() == 0) {
		Message m;
		m.id = _m_GAME_OVER;
		mngr_->send(m);
	}
}

void FoodSystem::removeFruit(ecs::entity_t f) {
	mngr_->setAlive(f, false);
}

void FoodSystem::removeAllFruits()
{
	for (auto f : mngr_->getEntities(ecs::grp::FOOD)) {
		mngr_->setAlive(f, false);
	}
}

void FoodSystem::checkTypeFruit(ecs::entity_t fruit) {
	auto mirFruit = mngr_->getComponent<MiracleFruit>(fruit);
	Message m;
	m.id = _m_PACMAN_CHECK_INMUNITY;
	m.pacman_check_inmunity.fruit = fruit;

	if (mirFruit != nullptr) {
		m.pacman_check_inmunity.milagrosa = mirFruit->miracle;
	}
	else {
		m.pacman_check_inmunity.milagrosa = false;
	}

	mngr_->send(m);
}

void FoodSystem::resetMiracleFruits()
{
	auto fruits = mngr_->getEntities(ecs::grp::FOOD);
	for (auto& f : fruits) {
		auto mF = mngr_->getComponent<MiracleFruit>(f);
		if (mF != nullptr) {
			mF->resetFruit();
		}
	}
}

void FoodSystem::setFruits() {
	for (int i = 0; i < fCols_; ++i) {
		for (int j = 0; j < fRows_; ++j) {
			auto fruit = mngr_->addEntity(ecs::grp::FOOD);
			auto fTR = mngr_->addComponent<Transform>(fruit);
			int w, h;
			w = h = 30;
			Vector2D pos = Vector2D(sdlutils().width() / fCols_ * i + w, sdlutils().height() / fRows_ * j + h);
			fTR->init(pos, Vector2D(), w, h, 0);

			auto img = mngr_->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("pacman"),
				1, 1, //
				0, 0, //
				128, 128, //
				4, 1, //
				1, 1
			);

			if (rnd_.nextInt(0, 10) == 2) {
				mngr_->addComponent<MiracleFruit>(fruit, rnd_.nextInt(10, 21), rnd_.nextInt(1, 6));
			}
		}
	}

}