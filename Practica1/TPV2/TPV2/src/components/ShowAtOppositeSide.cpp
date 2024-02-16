#include "ShowAtOppositeSide.h"

#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

ShowAtOppositeSide::ShowAtOppositeSide() :
	tr_(nullptr) {

}

ShowAtOppositeSide::~ShowAtOppositeSide() {

}

void ShowAtOppositeSide::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update() {
	// comprobacion vertical
	auto& pos = tr_->getPos();
	if (pos.getY() < 0 - tr_->getHeight() / 2) {
		pos.setY(sdlutils().height() - tr_->getHeight() / 2);
	} else if(pos.getY() > sdlutils().height()) {
		pos.setY(0);
	}
	// comprobacion horizontal
	if (pos.getX() < 0 - tr_->getWidth() / 2) {
		pos.setX(sdlutils().width() - tr_->getWidth() / 2);
	} else if (pos.getX() > sdlutils().width()) {
		pos.setX(0);
	}
}

