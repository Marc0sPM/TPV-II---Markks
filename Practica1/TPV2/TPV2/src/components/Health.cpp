#include "Health.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
Health::Health() :
	currentLifes_(maxLifes_),
	img_(nullptr){

}

Health::~Health() {

}

void Health::initComponent() {
	initPos_ = new  Vector2D(20.0f, 20.0f);
	img_ = new Image();
}

void Health::update() {
	
}
