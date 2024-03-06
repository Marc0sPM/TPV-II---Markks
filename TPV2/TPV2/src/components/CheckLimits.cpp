#include "CheckLimits.h"

#include "../ecs/ecs.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

CheckLimits::CheckLimits() : 
	tr_(nullptr){
}

void CheckLimits::initComponent(){
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void CheckLimits::update() {
	auto x = tr_->getPos().getX();
	auto y = tr_->getPos().getY();

	if (x > sdlutils().width() + 15 || 
		x < -15 || 
		y > sdlutils().height() + 15 ||
		y < -15) {
		mngr_->setAlive(ent_, false);
		mngr_->refresh();
	} 

}
