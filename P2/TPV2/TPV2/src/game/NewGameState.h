// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;
class NewGameState: public GameState {
public:
	NewGameState(ecs::Manager* mngr);
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
private:
	Texture &msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
	ecs::Manager* mngr_;
};

