#include "DeAcceleration.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

DeAcceleration::DeAcceleration() :
	tr_(nullptr) {
}

DeAcceleration::~DeAcceleration() {

}

void DeAcceleration::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void DeAcceleration::update() {
	auto& vel = tr_->getVel();
	if (vel.magnitude() > 0.05f) {
		vel.set(vel * deAcFactor_);
	}
	else vel.set(0.0f, 0.0f);
}