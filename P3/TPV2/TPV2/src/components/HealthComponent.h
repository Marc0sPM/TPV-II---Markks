#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

struct HealthComponent : public ecs::Component
{
	__CMPID_DECL__(ecs::cmp::HEALTH)

	int currLifes_;

	HealthComponent(int cLifes = 3) :
		currLifes_(cLifes) 
	{}
	virtual ~HealthComponent() {

	}
	
	void render() override {
		Texture* t = &sdlutils().images().at("heart");

		for (int i = 0; i < currLifes_; ++i) {
			t->render(40 * i, 0, 30, 30);
		}
	}

	void setLifes(int n) {
		currLifes_ = n;
	}
};

