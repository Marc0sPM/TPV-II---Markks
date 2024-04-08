// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "../ecs/ecs.h"
#include "GameState.h"
#include "../utils/Singleton.h"

class Game : public Singleton<Game> {
	friend Singleton<Game> ;
	Game();
public:
	virtual ~Game();
	void init();
	void start();
	inline ecs::Manager* getMngr() {
		return mngr_;
	}

	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};

	inline void setState(State s) {
		GameState* new_state = nullptr;
		switch (s) {
		case RUNNING:
			new_state = running_state_;
			break;
		case PAUSED:
			new_state = paused_state_;
			break;
		case NEWGAME:
			new_state = newgame_state_;
			break;
		case NEWROUND:
			new_state = newround_state_;
			break;
		case GAMEOVER:
			new_state = gameover_state_;
			break;
		default:
			break;
		}
		current_state_->leave();
		current_state_ = new_state;
		current_state_->enter();
	}

private:
	ecs::Manager *mngr_;
	ecs::System *pacmanSys_;
	ecs::System *gameCtrlSys_;
	ecs::System *ghostSys_;
	ecs::System *renderSys_;
	ecs::System *collisionSys_;
	ecs::System *foodSys_;
	ecs::System* immunitySys_;

	GameState* current_state_;
	GameState* paused_state_;
	GameState* running_state_;
	GameState* newgame_state_;
	GameState* newround_state_;
	GameState* gameover_state_;

};

