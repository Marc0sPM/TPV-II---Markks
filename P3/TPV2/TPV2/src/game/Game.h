// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include <vector>

#include "../utils/Singleton.h"

class Networking;
class LittleWolf;

class Game: public Singleton<Game> {
	friend Singleton<Game> ;
	Game();
public:
	virtual ~Game();
	bool init(char *host, Uint16 port);
	void start();

	LittleWolf& get_littlewolf() {
		return *little_wolf_;
	}

	Networking& get_networking() {
		return *net_;
	}


private:

	LittleWolf* little_wolf_;

	Networking* net_;

};

