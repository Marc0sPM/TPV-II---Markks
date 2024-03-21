#include "GhostSystem.h"

#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem() :
	ghTR_(nullptr) {
}

GhostSystem::~GhostSystem(){
}

void GhostSystem::initSystem(){
}

void GhostSystem::update(){
}
