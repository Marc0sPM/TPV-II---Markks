#include "FoodSystem.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/ImageWithFrames.h"

FoodSystem::FoodSystem(int fRows, int fCols) :
	fRows_(fRows), //
	fCols_(fCols),  //
	rnd_(sdlutils().rand())
{}

void FoodSystem::initSystem()
{
	setFruits();
}
 
void FoodSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_ROUND_START:
		setFruits();
	case _m_PACMAN_FOOD_COLLISION:
		removeFruit(m.pacman_food.fruit);
	}
}

void FoodSystem::update()
{
	auto& fruits = mngr_->getEntities(ecs::grp::FOOD);
	if (fruits.size() == 0) {
		Message m;
		m.id = _m_ROUND_OVER;
		mngr_->send(m);
	}
}

void FoodSystem::removeFruit(ecs::entity_t f) {
	mngr_->setAlive(f, false);
}

void FoodSystem::setFruits() {
	for (int i = 0; i < fCols_; ++i) {
		for (int j = 0; j < fRows_; ++j) {
			auto fruit = mngr_->addEntity(ecs::grp::FOOD);
			auto fTR = mngr_->addComponent<Transform>(fruit);

			Vector2D pos = Vector2D(sdlutils().width() / fCols_ * i, sdlutils().height() / fRows_ * j);
			fTR->init(pos, Vector2D(), 50, 50, 0);

			auto img = mngr_->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("pacman"),
				1, 1, //
				0, 0, //
				128, 128, //
				4, 1, //
				1, 1
			);
		}
	}

}