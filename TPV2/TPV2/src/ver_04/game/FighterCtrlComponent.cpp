#include "FighterCtrlComponent.h"

#include "../../sdlutils/InputHandler.h"
#include "Container.h"

FighterCrtlComponent::FighterCrtlComponent() :
		right_(SDLK_RIGHT),
		left_(SDLK_LEFT),
		up_(SDLK_UP),
		rotation_(5.0f),
		thrust_(0.2f),
		speedLimit_(3.0f)
{
}

FighterCrtlComponent::~FighterCrtlComponent() {
}

void FighterCrtlComponent::handleInput(Container* o) {
	auto &ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(right_)) { // Rotate to right
			o->setRotation(o->getRotation() + rotation_);
		} else if (ihdlr.isKeyDown(left_)) { // Rotate to left
			o->setRotation(o->getRotation() - rotation_);
		}
		//Move towards
		if (ihdlr.isKeyDown(up_)) {
			Vector2D newVel;
			newVel = o->getVel() + Vector2D(0, -1).rotate(rotation_) * thrust_;

			if (newVel.magnitude()< speedLimit_) {
			o->getVel().set(newVel);
			}
			else {
				o->getVel().set(newVel.normalize() * speedLimit_);
			}
		}
	}
	
}