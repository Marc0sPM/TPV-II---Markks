#include "Gun.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"

Gun::Gun() : 
	tr_(nullptr),
	lastTimeShoot_(0)
{}

Gun::~Gun() {
}

void Gun::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Gun::update(){
	auto& ihdlr = ih();
	auto time = sdlutils().virtualTimer().currTime();
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_S) && time - lastTimeShoot_ > shootTimeLimit_) {
		//shoot()
		std::cout << "shoot" << std::endl;
		lastTimeShoot_ = time;
	}
}