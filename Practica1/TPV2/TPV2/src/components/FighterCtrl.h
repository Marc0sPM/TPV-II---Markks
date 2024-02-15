#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Transform;

class FighterCtrl : public ecs::Component
{
public:
	
	__CMPID_DECL__(ecs::cmp::FIGHTERCTRL);

	FighterCtrl();
	virtual ~FighterCtrl();
	void initComponent() override;
	void update() override;

	inline void setKeys(SDL_Scancode up, SDL_Scancode right, SDL_Scancode left, SDL_Scancode shoot) {
		up_ = up;
		right_ = right;
		left_ = left;
	}

private:
	Transform* tr_;
	const float rotFactor_ = 3.0f;
	SDL_Scancode right_;
	SDL_Scancode left_;
	SDL_Scancode up_;

	void calcVel(float rad);



};

