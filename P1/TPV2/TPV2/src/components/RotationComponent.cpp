#include "RotationComponent.h"

#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

RotationComponent::RotationComponent():tr_(nullptr), rand_(sdlutils().rand()), rotation_
(rand_.nextInt(5, 10)) {

}

RotationComponent::~RotationComponent() {
}

void RotationComponent::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void RotationComponent::update() {
	tr_->setRot(tr_->getRot() + rotation_);
}
