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
	SDL_Keycode up_;
	float rotation_;
	float thrust_;
	float speedLimit_;

};
