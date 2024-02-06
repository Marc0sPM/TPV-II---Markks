#pragma once
#include "InputComponent.h"
#include <SDL.h>
class FighterCrtlComponent : public InputComponent
{
public:
	FighterCrtlComponent();
	virtual ~FighterCrtlComponent();

	void handleInput(Container* o) override;

private:
	SDL_Keycode right_;
	SDL_Keycode left_;
	float rotation_;

};
