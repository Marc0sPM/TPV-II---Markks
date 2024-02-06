#include "FighterCtrlComponent.h"

#include "../../sdlutils/InputHandler.h"
#include "Container.h"

FighterCrtlComponent::FighterCrtlComponent() :
		right_(SDLK_RIGHT),
		left_(SDLK_LEFT),
		rotation_(5.0f)
{
}

FighterCrtlComponent::~FighterCrtlComponent() {
}

void FighterCrtlComponent::handleInput(Container* o) {
	auto &ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(right_)) {
			o->setRotation(o->getRotation() + rotation_);
		} else if (ihdlr.isKeyDown(left_)) {
			o->setRotation(o->getRotation() - rotation_);
		}
	}
}