#include "Health.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "Transform.h"

#include <cassert>
Health::Health() :
	currentLifes_(maxLifes_){

}

Health::~Health() {
}

void Health::initComponent() {
}

void Health::update() {
}

void Health::render() {
	for (int i = 0; i < currentLifes_; i++) {
		auto& t = sdlutils().images().at("heart");
		t.render(20.0f + i*t.width() * 3/2,
			20.0f);
	}
}
