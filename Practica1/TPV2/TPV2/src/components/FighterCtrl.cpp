#include "FighterCtrl.h"

#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"

FighterCtrl::FighterCtrl() :
	tr_(nullptr),
	up_(SDL_SCANCODE_UP),
	right_(SDL_SCANCODE_RIGHT),
	left_(SDL_SCANCODE_LEFT)
{

}

FighterCtrl::~FighterCtrl() {

}

void FighterCtrl::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void FighterCtrl::update(){
	auto& ihdlr = ih();
	
	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(right_)) {
			float rad = rotFactor_ * M_PI / 180;
			tr_->setRot(tr_->getRot() + rotFactor_);
			calcVel(rad);
		}
		else if (ihdlr.isKeyDown(left_)) {
			float rad = rotFactor_ * M_PI / 180;
			tr_->setRot(tr_->getRot() - rotFactor_);
			calcVel(-rad);
		}

		if (ihdlr.isKeyDown(up_)) {

			//acelera

		}
	}
}

void FighterCtrl::calcVel(float rad) {
	auto& vel = tr_->getVel();
	
	vel.setX(vel.getX() * cos(rad) - vel.getY() * sin(rad));
	vel.setY(vel.getX() * sin(rad) + vel.getY() * cos(rad));
}
