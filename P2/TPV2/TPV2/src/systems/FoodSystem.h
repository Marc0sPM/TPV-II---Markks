#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
class RandomNumberGenerator;
class FoodSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::FOOD)


	FoodSystem(int fRows = 8, int fCols = 10);
	virtual ~FoodSystem() {}

	void initSystem() override;
	void recieve(const Message& m) override;
	void update() override;
	void removeFruit(ecs::entity_t f);

private:

	void setFruits();
	int fCols_;
	int fRows_;
	RandomNumberGenerator& rnd_;

};

