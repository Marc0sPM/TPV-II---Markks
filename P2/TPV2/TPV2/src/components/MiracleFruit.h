#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "ImageWithFrames.h"

struct MiracleFruit : public ecs::Component
{
	__CMPID_DECL__(ecs::cmp::MIRACLEFRUIT)

	int fN_; // frecuencia de aparicion
	int fM_; // duracion en estado milagroso

	int lastTimeMiracled;

	bool miracle = false;

	MiracleFruit(int fN, int fM) : 
		fN_(fN), //
		fM_(fM), //
		lastTimeMiracled(0)
	{}

	void initComponent() override {
	}

	void update() override {

		if (miracle && sdlutils().virtualTimer().currTime() >= lastTimeMiracled + (fM_ * 1000) ) {
			//cambio de img
			mngr_->getComponent<ImageWithFrames>(ent_)->changeFrames(4);
			miracle = false;
			lastTimeMiracled = sdlutils().virtualTimer().currTime();
		}
		else if(!miracle && sdlutils().virtualTimer().currTime() >= lastTimeMiracled + (fN_ * 1000)) {
			//cambio de img
			mngr_->getComponent<ImageWithFrames>(ent_)->changeFrames(7);
			miracle = true;
			lastTimeMiracled = sdlutils().virtualTimer().currTime();
		}
	}
};

