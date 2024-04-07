// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/ecs.h"


class GameState {
public:

	GameState() {
	}

	virtual ~GameState() {
	}

	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;
};

